#include "tcp_connection.hpp"

#include <boost/bind.hpp>

namespace vicinibus
{

    void tcp_connection::start ()
    {
        _socket.async_read_some (boost::asio::buffer (_handler.request ())
                                ,boost::bind (&tcp_connection::handle_read
                                             ,shared_from_this ()
                                             ,boost::asio::placeholders::error
                                             ,boost::asio::placeholders::bytes_transferred
                                             )
                                );
    }

    void tcp_connection::handle_read (boost::system::error_code const& e, std::size_t bytes)
    {
        if (!e)
        {
            request_handler::return_type r = _handler.generate_reply (bytes);

            if (r.first)
                boost::asio::async_write (_socket, boost::asio::buffer (_handler.reply (), r.second)
                    ,boost::bind (&tcp_connection::handle_write, shared_from_this ()
                                 ,boost::asio::placeholders::error)
                                  );
        }
    }

} // namespace vicinibus

