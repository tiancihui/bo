#include"EventLoop.h"
#include"DeMultiPlex.h"

namespace Net
{
	EventLoop::EventLoop()
	{
	    _deMultiPlex = DeMultiPlex::create(this);
	}

	EventLoop::~EventLoop()
	{	
		delete _deMultiPlex;
		_handles.clear();
		_events.clear();
	}

	int EventLoop::registerHandle(EventHandle* handler, event_t event)
	{
		 handle_t handle = handler->getHandle();
         HandleMap::iterator it = _handles.find(handle);
		 if(it == _handles.end())
		 {
		    _handles.insert(make_pair(handle, handler));
		 }

		 return  _deMultiPlex->registerEvent(handle,event);
	}

	int  EventLoop::removeHandle(EventHandle* handle)
	{
		 handle_t handle = handler->getHandle();
         HandleMap::iterator it = _handles.find(handle);
		 if(it != _handles.end())
		 {
		    _handles.erase(it);
		 }
         
		 _deMultiPlex->unRegisterEvent(handle);
	}

	void  EventLoop::handleEvent()
	{
          _deMultiPlex->Loop(-1);
	}

    void EventLoop::NotifyActivity(int num)
	{
		_events.clear();
		_deMultiPlex->getActivityEvent(_events, num);
		EventMap::iteraor it = _events.begin();
		for(;it != _events.end(); it++)
		{
			handle_t handle = it->first; 
			HandleMap::iterator it2 = _handles.find(handle);
			if(it2 != _handles.end())
			{
				switch (it->second)
				{
					case EventError:
						it2->second->handleError();
						break;

					case EventRead:
						it2->second->handleRead);
						break;

					case EventWrite:
						it2->second->handleWrite();
						break;

					default:
						break;

				}

			}

		}

	}
};
