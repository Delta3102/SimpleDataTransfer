#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <string>
#include <fstream>
#include <FL/Fl_Text_Display.H>

using namespace std;
using namespace boost::asio;

class Client
{
private:
    io_context io;
    size_t bt;

    char BUFF[4096];
    ifstream i;
    ofstream o;


public:
    string data_name = "a.txt", ip_serv = "127.0.0.1";

    void transmissons(Fl_Text_Buffer* &in, Fl_Text_Display *&di);
    void receiving(Fl_Text_Buffer* &in, Fl_Text_Display *&di);
};

#endif
