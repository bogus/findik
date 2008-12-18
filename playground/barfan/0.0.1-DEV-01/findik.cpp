#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include "configuration.hpp"

#if defined(_WIN32)

boost::function0<void> console_ctrl_function;

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
      std::cerr << "    findik 0.0.0.0 80 1\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    findik 0::0 80 1\n";
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

    // Initialise server.
    findik::io::server s(address, port, num_threads);

    // Set console control handler to allow server to be stopped.
    console_ctrl_function = boost::bind(&findik::io::server::stop, &s);
    SetConsoleCtrlHandler(console_ctrl_handler, TRUE);

    // Run the server until stopped.
    s.run();
	
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}

#endif // defined(_WIN32)
#if !defined(_WIN32)

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
      std::cerr << "    findik 0.0.0.0 80 1\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    findik 0::0 80 1\n";
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
