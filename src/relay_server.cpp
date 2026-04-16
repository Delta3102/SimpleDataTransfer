#include "relay_server.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <FL/Fl_Text_Display.H>

using namespace std;
using namespace boost::asio;

void RelayServer::send_data(ip::tcp::socket &sock_inp, ip::tcp::socket &sock_out, Fl_Text_Buffer* &in, Fl_Text_Display *&di){
    // Чтение
    bt = sock_inp.read_some(buffer(binBUFF));
    in->append("Reading 4096 byte\n");
    di->redraw();
    // Запись
    write(sock_out, buffer(binBUFF, bt));
    in->append("Writing 4096 byte\n");
    di->redraw();
}

void RelayServer::relay(ip::tcp::acceptor &acpt_inp,
                        ip::tcp::acceptor &acpt_out,
                        ip::tcp::socket &sock_inp,
                        ip::tcp::socket &sock_out,
                        Fl_Text_Buffer* &in,
                        Fl_Text_Display *&di)
{
    acpt_inp.async_accept(sock_inp, [this, &acpt_out, &sock_out, &sock_inp, &in, &di](boost::system::error_code er){
        in->append("Accept input\n");
        di->redraw();
        acpt_out.async_accept(sock_out, [this, &sock_out, &sock_inp, &in, &di](boost::system::error_code er){
            in->append("Accept output\n");
            di->redraw();
            send_data(sock_inp, sock_out, in, di);
        });
    });
}

// Запуск
void RelayServer::run(Fl_Text_Buffer* &in, Fl_Text_Display *&di){
    // Асепторы
    ip::tcp::acceptor acpt_inp(io,
                               ip::tcp::endpoint(ip::tcp::v4(), 12090)); // порт входа
    ip::tcp::acceptor acpt_out(io,
                               ip::tcp::endpoint(ip::tcp::v4(), 12091)); // порт выхода

    // Сокеты
    ip::tcp::socket sock_inp(io);
    ip::tcp::socket sock_out(io);
    ip::tcp::socket sock_ref(io);

    relay(acpt_inp, acpt_out, sock_inp, sock_out, in, di);

    io.run();
}
