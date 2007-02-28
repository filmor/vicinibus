#ifndef VICINIBUS_SERVER_HPP
#define VICINIBUS_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include "tcp_listener.hpp"
#include "udp_listener.hpp"

namespace vicinibus
{

    class server : boost::noncopyable
    {
    public:
        explicit server (boost::asio::io_service&);
        ~server ();

    private:
        /// Handle completion of an asynchronous accept operation.
        void handle_accept (boost::asio::error const& e);

        /// The io_service used to perform asynchronous operations.
        boost::asio::io_service& _io_service;

        /// Acceptor used to listen for incoming connections.
        tcp_listener _tcp_listener;
        udp_listener _udp_listener;
    };

} // namespace vicinibus

#endif // VICINIBUS_SERVER_HPP

