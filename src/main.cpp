#include "server.hpp"
#include "zeroconf.hpp"

int main ()
{
#if 0
    try
    {
#endif
        vicinibus::zeroconf_resolve z;
        std::cout << z ("mithrandir.local.") << std::endl;

        boost::asio::io_service io;

//        vicinibus::server server (io);
        
        // io.run ();
#if 0
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what () << std::endl;
    }
#endif
    return 0;
}
