#ifndef VICINIBUS_UDP_LISTENER_HPP
#define VICINIBUS_UDP_LISTENER_HPP

#include <boost/asio.hpp>
#include "request_handler.hpp"

namespace vicinibus
{

    class udp_listener
    {
    public:
        typedef boost::asio::ip::udp::socket socket_type;

        udp_listener (boost::asio::io_service& io,
                      boost::asio::ip::udp::endpoint const& ep)
            : _socket (io, ep)
        {
            start_receive ();
        }

    private:
        void start_receive ();

        void handle_receive (boost::system::error_code const&, std::size_t);
        void handle_send (boost::system::error_code const&, std::size_t) {}

        request_handler _handler;

        socket_type _socket;

        boost::asio::ip::udp::endpoint _remote_endpoint;
    };

}

#endif

