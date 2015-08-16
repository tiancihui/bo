#include "NetAddress.h"
namespace Net
{

	NetAddress::NetAddress(int port)
	{
		bzero(&_addr, sizeof(_addr));
		_addr.sin_family = AF_INET;
		_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		_addr.sin_port = htons(port);
	}

	NetAddress::NetAddress(string ip, int port)
	{
		bzero(&_addr, sizeof(_addr));
		_addr.sin_family = AF_INET;
		_addr.sin_addr.s_addr = htonl((char*)(ip.c_str()));
		_addr.sin_port = htons(port);
	}

	NetAddress::NetAddress(NetAdress& addr)
	{
		bzero(&_addr, sizeof(_addr));
		_addr.sin_family = addr.sin_family;
		_addr.sin_addr.s_addr = addr.sin_addr.s_addr;
		_addr.sin_port = addr.sin_port;
	}

	NetAddress::~NetAddress()
	{
		bzero(&_addr, sizeof(_addr));
	}

	int NetAddress::getPort()
	{
       return _addr.sin_port;
	}

	string NetAddress::getIp()
	{
	   char buf[32];
	   sprintf(buf,inet_ntoa(_addr.sin_addr));
	   return buf;
	}



};


#endif
