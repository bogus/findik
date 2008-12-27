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

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include "configuration.hpp"
#include "log_initializer.hpp"
#include "request_filter_factory_impl.hpp"
#if defined(_WIN32)

boost::function0<void> console_ctrl_function;

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("findik"));

BOOL WINAPI console_ctrl_handler(DWORD ctrl_type)
{
  switch (ctrl_type)
  {
  case CTRL_C_EVENT:
  case CTRL_BREAK_EVENT:
  case CTRL_CLOSE_EVENT:
  case CTRL_SHUTDOWN_EVENT:
    console_ctrl_function();
    return TRUE;
  default:
    return FALSE;
  }
}

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

	std::string address("0.0.0.0");
	std::string port("8080");
	std::size_t num_threads(10);

	if (argc == 4) {
		address = argv[1];
		port = argv[2];
		num_threads = boost::lexical_cast<std::size_t>(argv[3]);
	}

	// Initialize log manager
	//todo: fetch file paths, log level and accesslog on|off from conf file
	findik::log_initializer log_init;
	log_init.load_conf("findik_log.conf");

    // Initialise server.
    findik::io::server s(address, port, num_threads);

	LOG4CXX_INFO(findik::log_initializer::user_logger,"findik started to listen " + address + ":" + port);
	LOG4CXX_DEBUG(findik::log_initializer::debug_logger,"listening with " << num_threads << " threads");

	// Set console control handler to allow server to be stopped.
    console_ctrl_function = boost::bind(&findik::io::server::stop, &s);
    SetConsoleCtrlHandler(console_ctrl_handler, TRUE);

    // Run the server until stopped.
    s.run();

	//stop logging
	//todo put this to correct place
	findik::log_initializer::shutdown();

  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}

#endif // defined(_WIN32)
#if !defined(_WIN32)

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
	std::string port("8080");
	std::size_t num_threads(10);

	if (argc == 4) {
		address = argv[1];
		port = argv[2];
		num_threads = boost::lexical_cast<std::size_t>(argv[3]);
	}
    // Initialize request filter
	findik::filter::generate_request_filter_factory_map();
	findik::filter::generate_response_filter_factory_map();

    // Initialise server.
    findik::io::server s(address, port, num_threads);
    boost::thread t(boost::bind(&findik::io::server::run, &s));

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

    // Stop the server.
    s.stop();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}

#endif // !defined(_WIN32)
