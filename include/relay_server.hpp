#ifndef RELAY_SERVER_HPP
#define RELAY_SERVER_HPP

#include <boost/asio.hpp>
#include <FL/Fl_Text_Display.H>

using namespace std;
using namespace boost::asio;

class RelayServer
{
private:
    io_context io;
    size_t bt;
    char binBUFF[4096], refBUFF[4096];

    void send_data(ip::tcp::socket &sock_inp, ip::tcp::socket &sock_out, Fl_Text_Buffer* &in, Fl_Text_Display *&di);
    void relay(ip::tcp::acceptor &acpt_inp, ip::tcp::acceptor &acpt_out, ip::tcp::socket &sock_inp, ip::tcp::socket &sock_out, Fl_Text_Buffer* &in, Fl_Text_Display *&di);

public:
    void run(Fl_Text_Buffer* &in, Fl_Text_Display *&di);
};

#endif
