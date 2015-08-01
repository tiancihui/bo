#ifndef __THREAD__
#define __THREAD__

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "../util/Common_Time.h"

namespace Thread
{

class thread
{
	public:

		thread();
		virtual ~thread();

		virtual void  Run(void)=0;
        static  void* ThreadFunction(void *argv);
		void setErrorCode(int error)
		{
		   _error = error;
		}

		int getErrorCode(void)
		{
		   return _error;
		}


		void Start();
		void Join();
		void Stop();
		void Exit();
		void WakeUp();

	private:
		pthread_t _tid;
		int _error;

};
};
#endif
