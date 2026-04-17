#include "client.hpp"

#include <string>
#include <fstream>
#include <boost/asio.hpp>
#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>

using namespace std;
using namespace boost::asio;

void Client::transmissons(Fl_Text_Buffer* &in, Fl_Text_Display *&di){
    // инициализация
    ip::tcp::socket sock(io);
    ip::tcp::resolver rsl(io);
    char tbuf[30];

    // установка соединения
    async_connect(sock, rsl.resolve(ip_serv, "12090"), [this, &sock, &in, &tbuf, &di](const boost::system::error_code& ec, const ip::tcp::endpoint& endpoint){
        in->append("connect\n");
        di->redraw();
        Fl::check();

        // отправка названия
        write(sock, buffer(data_name.c_str(), data_name.size()));
        size_t lb = sock.read_some(buffer(refBUFF));

        // отправка файла
        i.open(data_name, ios::binary);
        if (!i) return;

        while(i){
            i.read(BUFF, 4096);
            in->append("reading file\n");
            di->redraw();
            Fl::check();

            write(sock, buffer(BUFF, i.gcount()));
            size_t lb = sock.read_some(buffer(refBUFF));
        }
        i.close();
        in->append("send file success\n");
        di->redraw();
        Fl::check();
        });

    io.run();

}

void Client::receiving(Fl_Text_Buffer* &in, Fl_Text_Display *&di){
    // инициализация
    ip::tcp::socket sock(io);
    ip::tcp::resolver rsl(io);
    char tbuf[30];

    // установка соединения
    async_connect(sock, rsl.resolve(ip_serv, "12091"), [this, &sock, &in, &tbuf, &di](const boost::system::error_code& ec, const ip::tcp::endpoint &endpoint){
        in->append("connect\n");
        di->redraw();
        Fl::check();

        // получение названия
        char name[255];

        size_t len = sock.read_some(buffer(name));
        write(sock, buffer(refBUFF));
        data_name = string(name, len);

        // получение файла
        o.open(data_name, ios::binary);

        do{
            bt = sock.read_some(buffer(BUFF));

            in->append("receiving\n");
            di->redraw();
            Fl::check();

            o.write(BUFF, bt);

            in->append("receive file success\n");
            di->redraw();
            Fl::check();
            
            write(sock, buffer(refBUFF));

        }
        while(bt == 4096);
        o.close();
        });

    io.run();
}

