#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace boost::asio;

class Client
{
private:
    io_context io;
    char BUFF[4096];
    string data, ip_serv;
    ifstream i;
    ofstream o;
public:
    void ping(ip::tcp::socket &sock);

    void settings();

    void delivery(string& data);
    void receiving();
};

#endif
