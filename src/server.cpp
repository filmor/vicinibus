#include "server.hpp"
#include "tcp_connection.hpp"
#include <boost/bind.hpp>

namespace vicinibus
{
    using boost::asio::ip::udp;
    using boost::asio::ip::tcp;

    server::server (boost::asio::io_service& io_service)
        : _io_service (io_service)
        , _tcp_listener (io_service, tcp::endpoint (tcp::v4 (), 53))
        , _udp_listener (io_service, udp::endpoint (udp::v4 (), 53))
    {
    }

    server::~server ()
    {
    }

} // namespace vicinibus

