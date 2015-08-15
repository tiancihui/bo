#ifndef __EVENT_HANDLE_H__
#define __EVENT_HANDLE_H__
namespace Net
{
    typedef unsigned int handle_t;
	class EventHandle
	{
		public:
			virtual void handleRead(); 
			virtual void handleWrite(); 
			virtual void handleTimeOut(); 
			virtual void handleError(); 
			virtual handle_t getHandle(); 
		private:
			EventHandle()
			{
			
			}

			virtual EventHandle()
			{

			}


	};


};




#endif
