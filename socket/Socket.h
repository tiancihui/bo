#ifndef __SOCKET__
#define __SOCKET__

#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <fcntl.h>           /* nonblocking */
#include  "NetAddress.h"

#define MAX_LISTEN_NUM 1024

namespace Net
{

	class Socket
	{
		public:
			Socket();

			Socket(int fd)
				:_fd(fd)
			{ 
			}

			~Socket();

			int getFd()
			{
				return _fd;
			}

			bool bindAddress(const NetAddress& l_addr);

			bool accept(NetAddress& p_addr);

			bool listen();

			bool connect(const NetAddress& r_addr);

			void shutDown();

			void shutDownRead();

			void shutDownWrite();


			// tool function
			void setNoNagle(bool flag);

			void setKeepAlive(bool flag);

			void setAddressReuse(bool flag);

			bool setPortReuse(bool flag);

			bool setNoBlocking();

		private:	
			Socket(const Socket& so)
			{
			}

			Socket& operator=(const Socket& so)
			{
			}


		private:
			const int _fd; 
	};

};


