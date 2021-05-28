#ifndef __UDPSERVER_HPP
#define __UDPSERVER_HPP

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
//#include <boost/array.hpp>
#include <chrono>

using boost::asio::ip::udp;

class UDPServer
{
public:
    UDPServer(boost::asio::io_service &io_context, unsigned short port)
        : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), port)), Timer1(io_context, boost::posix_time::millisec(1000))
    {
        std::cout << "Server started.... PORT: " << port << std::endl;
        Timer1.async_wait(boost::bind(&UDPServer::Timer1_Hendle, this, boost::asio::placeholders::error, &Timer1));
        start_receive();
    }

    ~UDPServer()
    {
    }

private:
    void Timer1_Hendle(const boost::system::error_code & /*e*/, boost::asio::deadline_timer *t)
    {
        t->expires_at(t->expires_at() + boost::posix_time::millisec(1));
        t->async_wait(boost::bind(&UDPServer::Timer1_Hendle, this, boost::asio::placeholders::error, t));

        //std::cout << "Send mess" << '\n';
        send_buff[0] = 0x02;

        for (int i = 0; i < 8; i++)
            send_buff[i + 1] = i;

        remote_endpoint_ = udp::endpoint(boost::asio::ip::address::from_string("172.31.1.29"), 1234);

        send_size = 9;
        start_send();
        t1 = boost::posix_time::microsec_clock::local_time();
    }

    void start_receive()
    {
        socket_.async_receive_from(boost::asio::buffer(boost::asio::buffer(recv_buff)), remote_endpoint_,
                                   boost::bind(&UDPServer::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    //-------------------------------------------------------------------------------------------
    void handle_receive(const boost::system::error_code &error, size_t bytes_recvd)
    {
        if (!error && bytes_recvd > 0)
        {
            /*
            std::cout << "Receive mess \nID: " << int(recv_buff[0]) << '\n';
            for (int i = 0; i < bytes_recvd - 1; i++)
                printf("0x%X ", uint8_t(recv_buff[i + 1]));

            std::cout << '\n';
            */

            boost::posix_time::ptime t2 = boost::posix_time::microsec_clock::local_time();
            boost::posix_time::time_duration diff = t2 - t1;
            std::cout << diff.total_milliseconds() << std::endl;
        }
        else
        {
            std::cout << "Could not read UDP message. Error: " << error.message() << " bytes_recvd: " << bytes_recvd << "\n";
        }
        start_receive();
    }
    //-------------------------------------------------------------------------------------------

    void start_send()
    {
        socket_.async_send_to(boost::asio::buffer(send_buff, send_size), remote_endpoint_,
                              boost::bind(&UDPServer::handle_send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    //-------------------------------------------------------------------------------------------

    void handle_send(const boost::system::error_code &error, size_t bytes_sent)
    {
        if (!error)
        {
            // OK
        }
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;

    char recv_buff[9];
    char send_buff[9];
    size_t send_size;

    boost::asio::io_service &io_context_;
    boost::asio::deadline_timer Timer1;

    boost::posix_time::ptime t1;
};

#endif