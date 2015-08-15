#include"Reactor.h"
namespace Net
{
	Reactor::Reactor()
	{
	    _loop = new EventLoop(this);
	}

	Reactor::~Reactor()
	{	
		delete _loop;
		_handles.clear();
		_events.clear();
	}

	int Reactor::registerHandle(EventHandle* handler, event_t event)
	{
		 handle_t handle = handler->getHandle();
         HandleMap::iterator it = _handles.find(handle);
		 if(it == _handles.end())
		 {
		    _handles.insert(make_pair(handle, handler));
		 }

		 return _loop->registerEvent(handle,event);
	}

	int  Reactor::removeHandle(EventHandle* handle)
	{
		 handle_t handle = handler->getHandle();
         HandleMap::iterator it = _handles.find(handle);
		 if(it != _handles.end())
		 {
		    _handles.erase(it);
		 }
         
		 _loop->unRegisterEvent(handle);
	}

	void  Reactor::handleEvent()
	{

	}

    void Reactor::NotifyActivity(int num)
	{
		_events.clear();
		_loop->getActivityEvent(_events, num);
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
