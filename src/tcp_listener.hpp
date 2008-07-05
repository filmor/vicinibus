#ifndef VICINIBUS_TCP_LISTENER_HPP
#define VICINIBUS_TCP_LISTENER_HPP

#include <boost/asio.hpp>
#include "request_handler.hpp"
#include "tcp_connection.hpp"

namespace vicinibus
{

    class tcp_listener
    {
    public:
        tcp_listener (boost::asio::io_service&, boost::asio::ip::tcp::endpoint const&);

    private:
        void handle_accept (boost::system::error_code const&);

        boost::asio::io_service& _io_service;

        boost::asio::ip::tcp::acceptor _acceptor;

        tcp_connection::pointer _new_connection;
    };

}

#endif

