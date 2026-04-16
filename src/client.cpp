#include "client.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <fstream>
#include <FL/Fl_Text_Display.H>

using namespace std;
using namespace boost::asio;

void Client::transmissons(Fl_Text_Buffer* &in, Fl_Text_Display *&di){
    // инициализация
    ip::tcp::socket sock(io);
    ip::tcp::resolver rsl(io);
    char tbuf[30];

    // отправка названия
    write(sock, buffer(data_name.c_str(), data_name.size()));

    // отправка файла
    i.open(data_name, ios::binary);
    if (!i) return;

    async_connect(sock, rsl.resolve(ip_serv, "12090"), [this, &sock, &in, &tbuf, &di](const boost::system::error_code& ec, const ip::tcp::endpoint& endpoint){
        snprintf(tbuf, sizeof(tbuf), "connect to \n", ip_serv);
        in->append(tbuf);
        di->redraw();

        while(i){
            i.read(BUFF, 4096);
            in->append("reading file\n");
            di->redraw();

            write(sock, buffer(BUFF, i.gcount()));
        }
        i.close();
        in->append("send file success\n");
        di->redraw();
        });

    io.run();

}

void Client::receiving(Fl_Text_Buffer* &in, Fl_Text_Display *&di){
    // инициализация
    ip::tcp::socket sock(io);
    ip::tcp::resolver rsl(io);
    char tbuf[30];

    // получение названия
    char name[255];
    size_t len = sock.read_some(buffer(name));
    data_name = string(name, len);

    // получение файла
    o.open(data_name, ios::binary);

    async_connect(sock, rsl.resolve(ip_serv, "12091"), [this, &sock, &in, &tbuf, &di](const boost::system::error_code& ec, const ip::tcp::endpoint &endpoint){
        snprintf(tbuf, sizeof(tbuf), "connect to \n", ip_serv);
        in->append(tbuf);
        di->redraw();

        bt = sock.read_some(buffer(BUFF));
        in->append("receiving\n");
        di->redraw();

        o.write(BUFF, bt);
        o.close();

        in->append("receive file success\n");
        di->redraw();
        });

    io.run();
}

