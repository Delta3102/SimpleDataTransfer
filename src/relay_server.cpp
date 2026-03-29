#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/co_spawn.hpp>

using namespace std;
using namespace boost::asio;
using boost::asio::awaitable;
using boost::asio::use_awaitable;

class RelayServer
{
private:
    io_context io;

    char binBUFF[4096], refBUFF[4096];

public:
    boost::asio::awaitable<void> send_data(ip::tcp::socket &sock1, ip::tcp::socket &sock2){
        // чтение
        size_t byte_d = co_await sock1.async_read_some(buffer(binBUFF), boost::asio::use_awaitable);
        // запись
        co_await async_write(sock2, buffer(binBUFF, byte_d), boost::asio::use_awaitable);
    }

    boost::asio::awaitable<void> relay(ip::tcp::acceptor &acpt_inp, ip::tcp::acceptor &acpt_out, ip::tcp::socket &sock_inp, ip::tcp::socket &sock_out){
        co_await acpt_inp.async_accept(sock_inp, boost::asio::use_awaitable);
        co_await acpt_out.async_accept(sock_out, boost::asio::use_awaitable);

        send_data(sock_inp, sock_out);
    }

    boost::asio::awaitable<void> run(){
        // Асепторы
        ip::tcp::acceptor acpt_inp(io, ip::tcp::endpoint(ip::tcp::v4(), 12090)); // порт входа
        ip::tcp::acceptor acpt_out(io, ip::tcp::endpoint(ip::tcp::v4(), 12091)); // порт выхода

        // Сокеты
        ip::tcp::socket sock_inp(io);
        ip::tcp::socket sock_out(io);
        ip::tcp::socket sock_ref(io);

        relay(acpt_inp, acpt_out, sock_inp, sock_out);
    }
};
