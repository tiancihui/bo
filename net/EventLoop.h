#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include<vector>
#include<EventHandle.h>
using namespace std;

namespace Net
{
	typedef unsigned int event_t;
	typedef std::map<handle_t,EventHandle*> HandleMap;
	typedef std::map<handle_t,event_t> EventMap;


	class DeMultiPlex;

	class EventLoop
	{
		public:
			EventLoop();
			virtual ~EventLoop();

			int registerHandle(EventHandle* handle, event_t event);
			int removeHandle(EventHandle* handle);
			void handleEvent();

			void NotifyActivity(int num);

		private:
        
	    DeMultiPlex *_deMultiPlex;
        HandleMap  _handles;
		EventMap   _events;

	};

};


#endif
