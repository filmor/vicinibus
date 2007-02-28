#include "bonjour_resolve_policy.hpp"

using boost::asio::ip::address;

namespace vicinibus
{
    
    address bonjour_resolve_policy::resolve (std::string const& s)
    {
        address result;

        if (DNSServiceQueryRecord (&_sd_ref, 0, 0, s.c_str (),
                               kDNSServiceType_SRV, kDNSServiceClass_IN,
                               _callback, static_cast<void*> (&_result))
                == kDNSServiceErr_NoError)
        {
            DNSServiceProcessResult (_sd_ref);
            result = address::from_string (_result);
        }
        else result = address::from_string ("::1");

        DNSServiceRefDeallocate (_sd_ref);

    }

    void bonjour_resolve_policy::_callback (
                                            DNSServiceRef ref,
                                            DNSServiceFlags flags,
                                            uint32_t interface,
                                            DNSServiceErrorType error,
                                            const char* fullname,
                                            uint16_t rrtype,
                                            uint16_t rrclass,
                                            uint16_t rdlen,
                                            const void* rdata,
                                            uint32_t ttl,
                                            void* p_result)
    {
        std::string& result = *static_cast<std::string*> (p_result);
        result = "192.168.2.1";
    }

}
