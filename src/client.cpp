#include <iostream>
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
    void ping(ip::tcp::socket &sock){

    }

    void settings(){
        cout << "IP Сервера: ";
        cin >> ip_serv;
        cout << endl;

        cout << "Поместите файл в ту же папку что и приложение и напишите его имя" << endl;
        cout << "Имя: ";
        cin >> data;
        cout << endl;
    }

    void delivery(string& data){
        ip::tcp::socket sock(io); // создание сокета и ресолвера
        ip::tcp::resolver rsl(io);

        i.open(data, ios::binary); // открытие файла
        if (!i) return;

        while(i){
            i.read(BUFF, 4096);
            cout << "Чтение" << endl;
            cout << BUFF << endl;

            connect(sock, rsl.resolve(ip_serv, "12090")); // установка соединения (оч красивый порт)
            cout << "Установка соединения" << endl;

            write(sock, buffer(BUFF, i.gcount()));
            cout << "Отправка данных" << endl;
        }

        sock.close();
    }

    void receiving(){
        ip::tcp::socket sock(io); // создание сокета и ресолвера
        ip::tcp::resolver rsl(io);
        size_t size = 1;

        o.open(data, ios::binary); // открытие файла

        while(size != 0){
            connect(sock, rsl.resolve(ip_serv, "12091")); // установка соединения (оч красивый порт)
            cout << "Установка соединения" << endl;

            size = sock.read_some(buffer(BUFF));
            if(size == 0) {
                break;
            }
            cout << "Получение данных" << endl;
            cout << BUFF << endl;

            o.write(BUFF, size);
            cout << "Запись данных" << endl;
            size = 0;
        }
        o.close();

        sock.close();
    }
};
