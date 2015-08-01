#include "thread.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "../util/Common_Time.h"

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
        pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr); 
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 
		if (pthread_create(&tid,&attr,thread::ThreadFunction,this)!=0) {
			printf("Create thread error!\n");
			return ;
	}
	}

	void thread::Join()
	{
  
	}

	void thread::Stop()
	{

	}

	void thread::Exit()
	{

	}

	void thread::WakeUp()
	{

	}
};
