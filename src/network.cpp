#include "core.hpp"
#include "network.hpp"
#include <string>
#include <fstream>
#include <boost/asio.hpp>
#include <filesystem>

using namespace std;
using namespace boost::asio;

void NetWork::set_ip(string text){
    this->ip_serv = text;
}

void NetWork::set_data_name(string text){
    this->data_name = text;
}

void NetWork::transmissons(){
    async_connect(*sock, rsl->resolve(ip_serv, "12090"), [this](const boost::system::error_code& ec, const ip::tcp::endpoint& endpoint){
        contr->loge("connect");
        
        // отправка названия
        write(*sock, buffer(data_name.c_str(), data_name.size()));
        wbt = sock->read_some(buffer(refBUFF));
        
        //отправка размера
        uintmax_t size = filesystem::file_size(data_name);
        all_kb = size;
        write(*sock, buffer(&all_kb, sizeof(size)));
        wbt = sock->read_some(buffer(refBUFF));
        contr->loge("File size: " + to_string(all_kb / 1024)+"KB");
        
        // отправка файла
        i.open(data_name, ios::binary);
        if (!i) return;
        
        while(i){
            i.read(binBUFF, 1400);
            write(*sock, buffer(binBUFF, i.gcount()));
            local_kb += 1400;
            contr->dele();
            contr->loge(to_string(local_kb / 1024) + "KB | " + to_string(all_kb / 1024) +"KB");
            wbt = sock->read_some(buffer(refBUFF));
        }
        i.close();
        contr->loge("file successfully sent");
        local_kb = 0;
        });
    io.run();

}

void NetWork::receiving(){
    async_connect(*sock, rsl->resolve(ip_serv, "12091"), [this](const boost::system::error_code& ec, const ip::tcp::endpoint &endpoint){
        contr->loge("connect");

        // получение названия
        size_t len = sock->read_some(buffer(name));
        write(*sock, buffer(refBUFF));
        data_name = string(name, len);
        
        //получение размера
        bt = sock->read_some(buffer(&all_kb, sizeof(all_kb)));
        write(*sock, buffer(refBUFF));

        // получение файла
        o.open(data_name, ios::binary);
        do{
            bt = sock->read_some(buffer(binBUFF));
            o.write(binBUFF, bt);
            local_kb += 1400;
            contr->dele();
            contr->loge(to_string(local_kb / 1024) + "KB | " + to_string(all_kb / 1024) +"KB");
            write(*sock, buffer(refBUFF));
        }
        while(bt == 1400);
        o.close();
        contr->loge("file successfully receive");
        local_kb = 0;
        });
    io.run();
}

void NetWork::server_run(){
    contr->loge("server run");

    acpt_inp->async_accept(*sock_inp, [this](boost::system::error_code er){
        contr->loge("accept input");
        acpt_out->async_accept(*sock_out, [this](boost::system::error_code er){
            contr->loge("accept out");
            contr->loge("start_relay");
            while(true){
                //Туда
                bt = sock_inp->read_some(buffer(binBUFF));
                write(*sock_out, buffer(binBUFF, bt));
                //Обратно
                bt = sock_out->read_some(buffer(binBUFF));
                write(*sock_inp, buffer(binBUFF, bt));
            }
        });
    });
    io.run();
}