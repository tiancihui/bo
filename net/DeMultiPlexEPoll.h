#ifndef __DE_MULTIPLEX_EPOLL_H__
#define __DE_MULTIPLEX_EPOLL_H__
#include "DeMultiPlex.h"

#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include  <arpa/inet.h>       /* inet(3) functions */
#include <sys/epoll.h> /* epoll function */
#include <fcntl.h>     /* nonblocking */
#include <sys/resource.h> /*setrlimit */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAXEPOLLSIZE 10000

namespace Net
{

class DeMultiPlexEPoll : public DeMultiPlex
{
	public:
     DeMultiPlexEPoll(EventLoop* loop);
     virtual ~DeMultiPlexEPoll();
    

	 bool registerEvent();
	 bool unRegisterEvent();
     
	 void Loop(long time);

	 bool getActivityEvent(EventMap& activityEvents,int num);
	private:

	 int    _epollFd;
	 int    _fdNum;
     struct epoll_event _ev;
     struct epoll_event _events[MAXEPOLLSIZE];
}

};
#endif





