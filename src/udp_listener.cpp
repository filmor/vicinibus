#include "udp_listener.hpp"

#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace vicinibus
{

    void udp_listener::start_receive ()
    {
        _socket.async_receive_from (boost::asio::buffer (_handler.request ()), _remote_endpoint
                                   ,boost::bind (&udp_listener::handle_receive, this
                                                ,boost::asio::placeholders::error
                                                ,boost::asio::placeholders::bytes_transferred
                                                )
                                   );
    }

    void udp_listener::handle_receive (boost::asio::error const& e, std::size_t bytes)
    {
        _handler.generate_reply (bytes);
        _socket.async_send_to (boost::asio::buffer(_handler.reply ()), _remote_endpoint
                              ,boost::bind (&udp_listener::handle_send, this
                                           ,boost::asio::placeholders::error
                                           ,boost::asio::placeholders::bytes_transferred 
                                  )
                              );
        start_receive ();
    }

}

