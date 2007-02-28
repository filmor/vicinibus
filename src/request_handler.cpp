#include "request_handler.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <utility>

namespace vicinibus
{

    /// dns-header, according to rfc1035.4.1.1
    struct header
    {
        /// IDentifier
        unsigned ID : 16;
        /// Query (0) or Response (1)
        unsigned QR : 1;
        /// 0 -> standard query
        /// 1 -> inverse query
        /// 2 -> status request
        /// (3-15 unspecified)
        unsigned OPCODE : 4;
        /// Authoritative Answer
        unsigned AA : 1;
        /// TrunCation
        unsigned TC : 1;
        /// Recursion Desired
        unsigned RD : 1;
        /// Recursion Available
        unsigned RA : 1;
        /// Must be zero!
        unsigned Z : 3;
        /// Response CODE:
        /// 0 -> no error
        /// 1 -> format error, query could not be interpreted
        /// 2 -> server failure
        /// 3 -> name error, domain name does not exist (only authoritative)
        /// 4 -> not implemented, will be used frequently in here ;)
        /// 5 -> refused, aka "du kummst hier net rein!"
        /// (6-15 unspecified)
        unsigned RCODE : 4;
        /// number of questions
        unsigned QDCOUNT : 16;
        /// number of answers
        unsigned ANCOUNT : 16;
        /// number of resource records in authoritative records
        unsigned NSCOUNT : 16;
        /// number of resource records in additional records
        unsigned ARCOUNT : 16;
    };

    std::string get_question (const unsigned char* begin, const unsigned char* end)
    {
        std::string res;
        while (begin != end && *begin != 0)
            res += *reinterpret_cast<const char*> (begin++);
        return res;
    }

    request_handler::return_type request_handler::generate_reply (std::size_t input)
    {
        header const& in = *reinterpret_cast<header*> (_request.begin ());

        std::cout << input;
        std::cout << "ID: " << in.ID << "\n";
        std::cout << in.QR << ' ' << in.RD << std::endl;
        std::cout << "Count: " << in.QDCOUNT << std::endl;
        std::cout << "\n================\n" << std::endl;

        header& out = *reinterpret_cast<header*> (_reply.begin ());

        int qdcount = in.QDCOUNT;
        unsigned char* pos = _request.begin () + 96;

        while (qdcount--)
        {
            std::string q = get_question (pos, _request.begin () + input);
            // std::cout << q << std::endl;
            pos += q.length () + 4;
        }

        out.ID = in.ID;
        out.QR = 1;
        out.OPCODE = 0;
        out.TC = 0;
        out.RD = 0;
        out.RA = 0;
        out.AA = 1;
        out.Z = 0;
        out.RCODE = 0;
        out.QDCOUNT = 0;
        out.ANCOUNT = 0;
        out.NSCOUNT = 0;
        out.ARCOUNT = 0;

        return std::make_pair (true, 96 /*pos - _request.begin ()*/);
    }

}

