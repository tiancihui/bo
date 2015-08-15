#include"EventHandle"

namespace Net
{
	class EventHandleTimer : public EventHandle
	{
		public:
			void handleRead(); 
			void handleWrite(); 
			void handleTimeOut(); 
			void handleError); 
			handle_t getHandle(); 

	};


};




