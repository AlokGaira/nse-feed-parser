#include <iostream>
#include <boost/lambda/lambda.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <ctime>

#include "src/UDPClient/UDPClient.cpp"
#include "src/UDPServer/UDPServer.cpp"

using namespace std;

//int main() {
//    cout << "Hello, World!" << endl;
//    return 0;

//    using namespace boost::lambda;
//    typedef std::istream_iterator<int> in;
//
//    std::for_each(
//            in(std::cin), in(), std::cout << (_1 * 3) << " " );
//
//    return 0;
//}

//using namespace boost::asio;
//using namespace boost::asio::ip;
//
//io_service ioservice;
//tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
//tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
//tcp::socket tcp_socket{ioservice};
//std::string data;
//
//void write_handler(const boost::system::error_code &ec,
//                   std::size_t bytes_transferred)
//{
//    if (!ec)
//        tcp_socket.shutdown(tcp::socket::shutdown_send);
//}
//
//void accept_handler(const boost::system::error_code &ec)
//{
//    if (!ec)
//    {
//        std::time_t now = std::time(nullptr);
//        data = std::ctime(&now);
//        async_write(tcp_socket, buffer(data), write_handler);
//    }
//}
//
//int main()
//{
//    tcp_acceptor.listen();
//    tcp_acceptor.async_accept(tcp_socket, accept_handler);
//    ioservice.run();
//}

int main()
{
//    boost::asio::io_service io_service;
//    UDPClient client(io_service, "localhost", "1337");
//    client.send("Hello, World!");

    try
    {
        boost::asio::io_context io_context;
        UDPServer server(io_context);
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}