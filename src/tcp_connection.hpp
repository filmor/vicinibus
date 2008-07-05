#ifndef VICINIBUS_TCP_CONNECTION_HPP
#define VICINIBUS_TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "request_handler.hpp"

namespace vicinibus
{

    ///
    class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
    {
    public:
        typedef boost::asio::ip::tcp::socket socket_type;
        typedef boost::shared_ptr<tcp_connection> pointer;

        tcp_connection (boost::asio::io_service& io)
            : _socket (io)
        {}

        socket_type& socket () { return _socket; }

        /// Start the first asynchronous operation for the connection.
        void start ();

    private:
        /// Handle completion of a read operation. \todo -> request_handler
        void handle_read (const boost::system::error_code& e,
                          std::size_t bytes_transferred);
        /// Handle completion of a write operation.
        void handle_write (const boost::system::error_code& e) {}

        socket_type _socket;

        request_handler _handler;
    };

} // namespace vicinibus

#endif // VICINIBUS_TCP_CONNECTION_HPP

