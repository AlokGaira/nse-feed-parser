//
// Created by alok on 15/11/18.
//

//#include "UDPServer.h"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;


class UDPServer
{
public:
    UDPServer(boost::asio::io_context& io_context)
            : socket_(io_context, udp::endpoint(udp::v4(), 13))
    {
        std :: cout << udp::endpoint(udp::v4(), 13);
        start_receive();
    }

private:

    std::string make_daytime_string()
    {
        using namespace std; // For time_t, time and ctime;
        time_t now = time(0);
        return ctime(&now);
    }

    void start_receive()
    {

        std :: cout << udp::endpoint(udp::v4(), 13);
        socket_.async_receive_from(
                boost::asio::buffer(recv_buffer_), remote_endpoint_,
                boost::bind(&UDPServer::handle_receive, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code& error,
                        std::size_t /*bytes_transferred*/)
    {
        std :: cout << "Start Recieve " << std :: endl;
        if (!error)
        {
            boost::shared_ptr<std::string> message(
                    new std::string(make_daytime_string()));

            std :: cout << remote_endpoint_ <<std :: endl;

            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                                  boost::bind(&UDPServer::handle_send, this, message,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
                     const boost::system::error_code& /*error*/,
                     std::size_t /*bytes_transferred*/)
    {
        std :: cout << remote_endpoint_ << std :: endl;
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
};
