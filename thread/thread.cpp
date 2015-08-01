#include "thread.h"

namespace Thread
{
	thread::thread()
	{
	}

	thread::~thread()
	{
	}

	void* thread::ThreadFunction(void *argv)
	{
		thread *_work = (thread*)argv;
		_work->Run();
		return 0;
	}

	void thread::Start()
	{
		pthread_attr_t attr;
		pthread_attr_init(&attr); 
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 
		if (pthread_create(&_tid,&attr,thread::ThreadFunction,this)!=0) {
			printf("Create thread error!\n");
			return ;
		}
	}

	void thread::Stop()
	{
       pthread_cancel(_tid); 
	   Join();
	}

	void thread::Join()
	{
       pthread_join(_tid,NULL);         
	}

	void thread::Exit()
	{
       pthread_exit(NULL);         
	}

	void thread::WakeUp()
	{

	}
};
