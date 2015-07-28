#ifndef __THREAD_JOB__
#define __THREAD_JOB__

#include <string.h>

namespace Thread
{
class threadWork;
class threadJob
{
	public:
		threadJob();

        void setJobNum(int jobNum);
        int  getJobNum();
        void setJobName(char* jobName);
        char* getJobName();
		
		virtual ~threadJob();

		void setWorkThread(threadWork* work);

		virtual void Run(void *_argv) = 0;
	private:
      threadWork *_work;
	  int _jobNum;
	  char *_jobName;
     
};
};
#endif
