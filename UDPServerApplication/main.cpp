#include <cstdlib>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "UDPServer.hpp"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using boost::asio::ip::tcp;

boost::asio::io_service io_context;

//----------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  /*
  pt::ptime current_date_microseconds = pt::microsec_clock::local_time();
  long milliseconds = current_date_microseconds.time_of_day().total_milliseconds();
  pt::time_duration current_time_milliseconds = pt::milliseconds(milliseconds);
  pt::ptime current_date_milliseconds(current_date_microseconds.date(),
                                      current_time_milliseconds);
  std::cout << current_date_microseconds << " Milliseconds: " << current_date_milliseconds.time_of_day().total_microseconds() << std::endl;
*/
  try
  {
    UDPServer server(io_context, 4443);
    io_context.run();
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception:  " << e.what() << "\n";
  }

  return 0;
}