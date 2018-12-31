//
// Created by alok on 15/11/18.
//

#ifndef LEARN_UDPCLIENT_H
#define LEARN_UDPCLIENT_H
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>


class UDPClient {
public:
    UDPClient(
            boost::asio::io_service& io_service,
            const std::string& host,
            const std::string& port
    );

    void send(const std::string& msg);

};


#endif //LEARN_UDPCLIENT_H
