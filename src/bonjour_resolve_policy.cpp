#include "bonjour_resolve_policy.hpp"

#include <iostream>

using boost::asio::ip::address;

namespace vicinibus
{

    namespace
    {
        void callback (DNSServiceRef ref, DNSServiceFlags flags, uint32_t interface,
                       DNSServiceErrorType error, const char* fullname,
                       uint16_t rrtype, uint16_t rrclass, uint16_t rdlen,
                       const void* rdata, uint32_t ttl, void* p_result)
        {
            std::cout << fullname << std::endl;
            address& result = *static_cast<address*> (p_result);
            result = address::from_string ("192.168.2.1");
        }
    }

    address bonjour_resolve_policy::resolve (std::string const& s)
    {
        address result;

        DNSServiceRef sd_ref;

        DNSServiceErrorType error = 
            DNSServiceQueryRecord (&sd_ref, 0, 0, s.c_str (),
                                  kDNSServiceType_SRV, kDNSServiceClass_IN,
                                  callback, static_cast<void*> (&result)
                    );

        if (error == kDNSServiceErr_NoError)
            DNSServiceProcessResult (sd_ref);
        else
            result = address::from_string ("::1");

        DNSServiceRefDeallocate (sd_ref);
        
        return result;
    }


}
