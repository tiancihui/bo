#ifndef __DE_MULTIPLEX_H__
#define __DE_MULTIPLEX_H__

namespace Net
{

enum EventType
{
   EventRead;
   EventWrite;
   EventError;
};

class DeMultiPlex
{
	private:
     DeMultiPlex(EventLoop * loop)
		 :_loop(loop)
	 {
	 }

     virtual ~DeMultiPlex()
	 {
	    _loop = NULL;
	 }
    

	public:
     static create(EventLoop * loop);


	 virtual bool registerEvent();
	 virtual bool unRegisterEvent();
     
	 virtual  void Loop(long time);

	 virtual bool getActivityEvent(EventMap& activityEvents,int num);

	public:
	 EventLoop*  _loop;
}

};
#endif





