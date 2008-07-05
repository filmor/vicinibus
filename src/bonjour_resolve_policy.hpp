#ifndef VICINIBUS_BONJOUR_RESOLVE_POLICY_HPP
#define VICINIBUS_BONJOUR_RESOLVE_POLICY_HPP

#include <dns_sd.h>
#include <string>
#include <boost/asio/ip/address.hpp>

namespace vicinibus
{

    class bonjour_resolve_policy
    {
    public:
        boost::asio::ip::address resolve (std::string const&);
    };

}

#endif

