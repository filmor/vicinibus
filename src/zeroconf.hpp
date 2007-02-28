#ifndef VICINIBUS_ZEROCONF_HPP
#define VICINIBUS_ZEROCONF_HPP

#include <string>
#include <boost/asio/ip/address.hpp>

#ifdef VICINIBUS_USE_AVAHI
#include "avahi_resolve_policy.hpp"
#define RESOLVE_POLICY avahi_resolve_policy
#else
#include "bonjour_resolve_policy.hpp"
#define RESOLVE_POLICY bonjour_resolve_policy
#endif

namespace vicinibus
{

    template <class ResolvePolicy>
    class resolver : private ResolvePolicy
                   , private boost::noncopyable
    {
    public:
        // Not threadsafe!
        boost::asio::ip::address operator () (std::string const& hostname)
        {
            return ResolvePolicy::resolve (hostname);
        }
    };

    typedef resolver<RESOLVE_POLICY> zeroconf_resolve;

}

#undef RESOLVE_POLICY

#endif

