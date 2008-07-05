#include "tcp_listener.hpp"
#include <boost/bind.hpp>

namespace vicinibus
{
    using boost::asio::ip::tcp;

    tcp_listener::tcp_listener (boost::asio::io_service& io_service,
                                tcp::endpoint const& ep)
        : _io_service (io_service)
        , _acceptor (io_service, ep)
        , _new_connection (new tcp_connection (io_service))
    {
        /*_acceptor.async_accept (_new_connection->socket ()
                               ,boost::bind (&tcp_listener::handle_accept, this
                                            ,boost::asio::placeholders::error)
                               );*/
    }

    void tcp_listener::handle_accept (const boost::system::error_code& e)
    {
        if (!e)
        {
            _new_connection->start ();
            _new_connection.reset (new tcp_connection (_io_service));
            _acceptor.async_accept (_new_connection->socket ()
                                   ,boost::bind (&tcp_listener::handle_accept, this
                                                ,boost::asio::placeholders::error)
                                   );
        }
    }


} // namespace vicinibus

