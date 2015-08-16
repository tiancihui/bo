#ifndef __NET_ADDRESS__
#define __NET_ADDRESS__
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
namespace Net
{

   class NetAddress
   {
        public:
			NetAddress(int port);
			NetAddress(string ip, int port);
			NetAddress(NetAdress& addr);
			~NetAddress();


	        void  setSockAddrIn(const struct sockaddr_in addr)
			{
			     _addr = addr;
			}

			const struct sockaddr_in& getSockAddrIn()
			{
			  return _addr;
			}
			
			int getPort();
			string  getIp();


		private:
        struct sockaddr_in _addr;
   
   };

};


#endif
