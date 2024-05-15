#pragma once

#include <iostream>
#include <string>
#ifdef __WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#endif
#include <boost/asio.hpp>

class WebserverClient
{
private:
    bool successResponse{};                              /** Response from webserver */
    std::string queryURL{};                              /** the url to query e.g. www.example.com */
    std::string queryProtocol{};                         /** the protocol to follow url query e.g. http*/
    boost::asio::io_context io_context{};                /** provides a context for I/O services e.g. sockets, timers, asynchronous functions */
    boost::asio::ip::tcp::resolver resolver{io_context}; /** resolve string address to endpoints. Same as a DNS/Domain name server */
    boost::asio::ip::tcp::socket socket{io_context};     /** socket for server being queried. Resolver passes the webaddress to use */
public:
    WebserverClient(){};
};