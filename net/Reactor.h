#ifndef __REACTOR_H__
#define __REACTOR_H__
#include<vector>
#include<EventHandle.h>
using namespace std;

namespace Net
{
	typedef unsigned int event_t;
	typedef std::map<handle_t,EventHandle*> HandleMap;
	typedef std::map<handle_t,event_t> EventMap;


	class EventLoop;

	class Reactor
	{
		public:
			Reactor();
			virtual ~Reactor();

			int registerHandle(EventHandle* handle, event_t event);
			int removeHandle(EventHandle* handle);
			void handleEvent();

			void NotifyActivity(int num);

		private:
        
		EventLoop *_loop;
        HandleMap  _handles;
		EventMap   _events;

	};

};


#endif
