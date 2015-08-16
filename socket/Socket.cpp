#include  "Socket.h"

namespace Net
{

	Socket::Socket()
	{
		_fd = socket(AF_INET,SOCK_STREAM,0);
		if (_fd == -1) {
			perror("can't create socket file");
		}
	}

	Socket::~Socket()
	{
		close(_fd);	
	}


	bool 	Socket::bindAddress(const NetAddress& l_addr) 
	{
		if (bind(_fd, (struct sockaddr *) &(l_addr->getSockAddrIn()), sizeof(struct sockaddr)) == -1)
		{
			perror("bind error");
			return false;
		}

		return true;
	}

	int Socket::accept(NetAddress& p_addr) 
	{
		struct sockaddr_in peerAdd;
		int len;
		int p_fd = accept(_fd, (struct sockaddr *)&peerAdd,&len);
		if (p_fd < 0)
		{
			perror("accept error");
			return -1;
		}

		p_addr.setSockAddrIn(peerAdd);
		return p_fd;
	}

	bool 	Socket::listen() 
	{
		if (listen(_fd, MAX_LISTEN_NUM) == -1)
		{
			perror("listen error");
			return false;
		}
		return true;
	}

	bool 	Socket::connect(const NetAddress& r_addr) 
	{
		if (connect(_fd,(struct sockaddr*)(r_addr->getSockAddrIn()),sizeof(r_addr->getSockAddrIn())) == -1)
		{
			perror("connect error");
			return false;
		}
		return true;
	}

	void 	Socket::shutDownWrite() 
	{
		shutdown(_fd, SHUT_WR);
	}

	void 	Socket::shutDownRead() 
	{
		shutdown(_fd, SHUT_RD);
	}

	void 	Socket::shutDown() 
	{
		shutdown(_fd, SHUT_RDWR);
	}

	// tool function
	void 	Socket::setNoNagle(bool flag) 
	{
		int opt = on ? 0 : 1;
		setsockopt(_fd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
	}

	void 	Socket::setKeepAlive(bool flag) 
	{
		int opt = flag ? 1 : 0;
		setsockopt(_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt));
	}

	void 	Socket::setAddressReuse(bool flag) 
	{
		int opt = flag ? 1 : 0;
		setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	}

	bool 	Socket::setPortReuse(bool flag) 
	{
#if 0		
		int optval = flag ? 1 : 0;
		int ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
				&optval, static_cast<socklen_t>(sizeof optval));
		if (ret < 0 && flag)
		{
			LOG_SYSERR << "SO_REUSEPORT failed.";
		}
#endif
		return 0;
	}

	bool  Socket::setNoBlocking()
	{
		if (fcntl(_fd, F_SETFL, fcntl(_fd, F_GETFD, 0)|O_NONBLOCK) == -1) {
			return false;
		}
		return true;
	}
}; 


