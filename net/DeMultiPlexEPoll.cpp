#include"DeMultiPlexEPoll.h"

namespace Net
{

	class DeMultiPlexEPoll
	{
		public:
			DeMultiPlexEPoll::DeMultiPlexEPoll(EventLoop* loop)
				:DeMultiPlex(loop)
			{
				_epollFd = epoll_create(MAXEPOLLSIZE);
				assert(_epollFd != -1);
				_fdNum_ = 0;
			}



			bool   DeMultiPlexEPoll::registerEvent(handle_t handle,event_t event)

			{
				epoll_event ev;
				ev.data.fd = handle;

				if(event & EventRead)
				{
					ev.events = EPOLLIN | EPOLLET;
				}

				if(event & EventWrite)
				{
					ev.events = EPOLLOUT | EPOLLET;
				}

				if(event & EventError)
				{
					ev.events = EPOLLERR | EPOLLET;
				}

				if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, handle, &ev) < 0)
				{
					fprintf(stderr, "epoll set insertion error: fd=%d\n",handle);
					return false;
				}

				_fdNum++;
				return true;
			}

			bool  DeMultiPlexEPoll::unRegisterEvent(handle_t handle)
			{
				epoll_event ev;
				if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, handle, &ev) != 0)
				{
					return false;
				}
				--_fdNum;
				return true;
			}

			void DeMultiPlexEPoll::Loop(long timeOut)
			{
				int nfds = epoll_wait(_epollFd, _events, _fdNum, timeOut);
				if (nfds == -1)
				{
					perror("epoll_wait");
					return;
				}

				_loop->NotifyActivity(nfds);

			}

			bool DeMultiPlexEPoll::getActivityEvent(EventMap& activityEvents, int num)
			{
				for (int idx = 0; idx < num; ++idx)
				{
					event_t event;
					handle_t handle = _events[idx].data.fd;

					if ((_events[idx].events & EPOLLERR) ||
							(_events[idx].events & EPOLLHUP))
					{
						event = EventError;
					}
					else
					{
						if (_events[idx].events & EPOLLIN)
						{
							event = EventError;
						}
						if (_events[idx].events & EPOLLOUT)
						{
							event = EventError;
						}
					}

					activityEvents.insert(make_pair(handle,event));
				}

				return true;
			}

			DeMultiPlexEPoll::~DeMultiPlexEPoll()
			{
				close(_epollFd); 
			}
	}

};
#endif
