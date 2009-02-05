/*
  Copyright (C) 2008 H. Kerem Cevahir (shelta) <findikmail@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "server.hpp"
#include "service_container.hpp"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/thread.hpp>
#include <pthread.h>
#include <signal.h>

int main(int argc, char* argv[])
{
	try
	{
		// Check command line arguments.
		if (argc != 4 && argc != 1)
		{
			std::cerr << "Usage: findik <address> <port> <threads>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "	findik 0.0.0.0 80 1\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "	findik 0::0 80 1\n";
			return 1;
		}

		// Block all signals for background thread.
		sigset_t new_mask;
		sigfillset(&new_mask);
		sigset_t old_mask;
		pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);

		// Run server in background thread.
		std::string address("0.0.0.0");
		unsigned int port = 8080;
		std::size_t num_threads(100);

		if (argc == 4) {
			address = argv[1];
			port = boost::lexical_cast<unsigned int>(argv[2]);
			num_threads = boost::lexical_cast<std::size_t>(argv[3]);
		}
		// Initialize request filter
		//findik::filter::generate_request_filter_factory_map();
		//findik::filter::generate_response_filter_factory_map();

		findik::logging::log_initializer log_init;
		log_init.load_conf("/etc/findik_log.conf");
		
		//First accesto FI_SERVICES must be under log init.
		if (! FI_SERVICES->config_srv().check())
			exit(1);

		// Initialise server.
		findik::io::server s(findik::io::http, address, port);

		// LOG4CXX_INFO(findik::log_initializer::user_logger,"findik started to listen " + address + ":" + port);

		// Create a pool of threads to run all of the io_services.
		std::vector<boost::shared_ptr<boost::thread> > threads;
		for (std::size_t i = 0; i < num_threads; ++i)
		{
			boost::shared_ptr<boost::thread> thread(new boost::thread(
			boost::bind(&boost::asio::io_service::run, &(FI_SERVICES->io_srv()))));
			threads.push_back(thread);
		}

		// LOG4CXX_DEBUG(findik::logging::log_initializer::debug_logger,"listening with " << num_threads << " threads");

		// Restore previous signals.
		pthread_sigmask(SIG_SETMASK, &old_mask, 0);

		// Wait for signal indicating time to shut down.
		sigset_t wait_mask;
		sigemptyset(&wait_mask);
		sigaddset(&wait_mask, SIGINT);
		sigaddset(&wait_mask, SIGQUIT);
		sigaddset(&wait_mask, SIGTERM);
		pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
		int sig = 0;
		sigwait(&wait_mask, &sig);

		FI_SERVICES->io_srv().stop(); // stop IO service
		// Wait for all threads in the pool to exit.
		for (std::size_t i = 0; i < threads.size(); ++i)
			threads[i]->join();

		//t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}

