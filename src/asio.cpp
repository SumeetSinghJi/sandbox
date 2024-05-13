#include <iostream>
#include <string>
#include <boost/asio.hpp>

class WebserverClient
{
private:
    boost::asio::io_context io_context{};
    boost::asio::ip::tcp::resolver resolver{io_context};
public:
    WebserverClient(){}
};

WebserverClient ws{};

int main()
{
	std::cout << "Hello world" << std::endl;
	return 0;
}
