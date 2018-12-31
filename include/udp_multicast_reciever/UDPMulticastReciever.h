//
// Created by alok on 16/11/18.
//

#ifndef LEARN_UDPMULTICASTRECIEVER_H
#define LEARN_UDPMULTICASTRECIEVER_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
//#include <boost/log/trivial.hpp>

#include "../process/Snapshot.h"

//const short multicast_port = 34842;

class UDPMulticastReciever
{
public:
    UDPMulticastReciever(boost::asio::io_service& io_service,
                         const boost::asio::ip::address& listen_address,
                         const boost::asio::ip::address& multicast_address,
                         const unsigned short multicast_port)
            : socket_(io_service)
    {
        // Create the socket so that multiple may be bound to the same address.
        boost::asio::ip::udp::endpoint listen_endpoint(
                listen_address, multicast_port);
        socket_.open(listen_endpoint.protocol());
        socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        socket_.bind(listen_endpoint);

        // Join the multicast group.
        socket_.set_option(
                boost::asio::ip::multicast::join_group(multicast_address));

        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&UDPMulticastReciever::handle_receive_from, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive_from(const boost::system::error_code& error,
                             size_t bytes_recvd)
    {
        if (!error)
        {
//          std::cout.write(data_, bytes_recvd);

            std::cout << "bytes_recvd " << bytes_recvd << std::endl;
            for(int i = 0; i < bytes_recvd; i++){
                printf("%02x ", data_[i]);
            }
            int16_t test = 1;
            std::cout << std::hex << test << std::endl;
            std::cout << std::endl;
            Snapshot::process(data_, bytes_recvd);

            socket_.async_receive_from(
                    boost::asio::buffer(data_, max_length), sender_endpoint_,
                    boost::bind(&UDPMulticastReciever::handle_receive_from, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
        }
    }

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    enum { max_length = 2048 };
    unsigned char *data_ = new unsigned char[max_length];
};


#endif //LEARN_UDPMULTICASTRECIEVER_H
