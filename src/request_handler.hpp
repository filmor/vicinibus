#ifndef VICINIBUS_REQUEST_HANDLER_HPP
#define VICINIBUS_REQUEST_HANDLER_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/integer.hpp>
#include <utility>

namespace vicinibus
{

    typedef boost::uint_t<8>::least byte;

    class request_handler : private boost::noncopyable
    {
    public:
        typedef boost::array<byte, 512> buffer_type;
        typedef std::pair<bool, unsigned> return_type;

        return_type generate_reply (std::size_t input_bytes);

        buffer_type& request () { return _request; }
        buffer_type const& reply () const { return _reply; }

    private:
        buffer_type _request, _reply;
    };

}

#endif

