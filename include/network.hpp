#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <boost/asio.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace boost::asio;

class Core;

class NetWork
{
private:
    Core *contr;
    io_context io;
    // Сокеты
    ip::tcp::socket *sock_inp = new ip::tcp::socket(io);
    ip::tcp::socket *sock_out = new ip::tcp::socket(io);
    ip::tcp::socket *sock = new ip::tcp::socket(io);
    ip::tcp::resolver *rsl = new ip::tcp::resolver(io);
    // Асепторы
    ip::tcp::acceptor *acpt_inp = new ip::tcp::acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 12090)); // порт входа
    ip::tcp::acceptor *acpt_out = new ip::tcp::acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 12091)); // порт выхода
    size_t bt, wbt;
    ifstream i;
    ofstream o;
    string data_name = "file.txt", ip_serv = "127.0.0.1";
    long long local_kb = 0, all_kb = 0;
    char binBUFF[1400], refBUFF[1400], servBUFF[1400], name[255];

public:
    NetWork(Core *c){
        contr = c;
    }
    void set_ip(string text);
    void set_data_name(string text);
    void transmissons();
    void receiving();
    void server_run();
};

#endif