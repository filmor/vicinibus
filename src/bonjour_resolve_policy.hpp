#ifndef VICINIBUS_BONJOUR_RESOLVE_POLICY_HPP
#define VICINIBUS_BONJOUR_RESOLVE_POLICY_HPP

#include <dns_sd.h>
#include <boost/asio/ip/address.hpp>

namespace vicinibus
{

    class bonjour_resolve_policy
    {
    public:
        boost::asio::ip::address resolve (std::string const&);

    private:
        static void _callback ( DNSServiceRef, DNSServiceFlags, uint32_t
                              , DNSServiceErrorType, const char*, uint16_t
                              , uint16_t, uint16_t, const void*, uint32_t
                              , void* );

        std::string _result;

        DNSServiceRef _sd_ref;
    };

}

#endif

