#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/log/trivial.hpp>
#include "../../include/udp_multicast_reciever/UDPMulticastReciever.h"


int main(int argc, char *argv[]) {
    try {
        if (argc != 4) {
            std::cerr << "Usage: receiver <listen_address> <multicast_address>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 239.255.0.1 34842\n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 ff31::8000:1234 34842\n";
            return 1;
        }
        short port = boost::lexical_cast<unsigned short>(argv[3]);

        boost::asio::io_service io_service;
        UDPMulticastReciever r(io_service,
                               boost::asio::ip::address::from_string(argv[1]),
                               boost::asio::ip::address::from_string(argv[2]),
                               port);
        io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}