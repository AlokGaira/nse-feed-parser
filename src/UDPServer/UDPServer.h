//
// Created by alok on 15/11/18.
//

#ifndef LEARN_UDPSERVER_H
#define LEARN_UDPSERVER_H

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

class UDPServer {
public:
    UDPServer(boost::asio::io_context& io_context);

};


#endif //LEARN_UDPSERVER_H
