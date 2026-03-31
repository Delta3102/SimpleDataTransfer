#ifndef RELAY_SERVER_HPP
#define RELAY_SERVER_HPP

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
    boost::asio::awaitable<void> send_data(ip::tcp::socket &sock1, ip::tcp::socket &sock2);

    boost::asio::awaitable<void> relay(ip::tcp::acceptor &acpt_inp, ip::tcp::acceptor &acpt_out, ip::tcp::socket &sock_inp, ip::tcp::socket &sock_out);

    boost::asio::awaitable<void> run();
};

#endif
