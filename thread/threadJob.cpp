#include "threadJob.h"
#include "threadWork.h"

namespace Thread
{
	threadJob::threadJob()
	{
	}

	void threadJob::setJobNum(int jobNum)
	{
       _jobNum = jobNum;
	}

	int  threadJob::getJobNum()
	{
      return _jobNum;
	}

	void threadJob::setJobName(char* jobName)
	{
         if(_jobName != NULL)
		 {
		    free(_jobName);
			_jobName = NULL;
		 }

		 if(jobName != NULL)
		 {
		      _jobName = (char*)malloc(strlen(jobName)+1);
			  strcpy(_jobName,jobName);
		 }
	}


	char* threadJob::getJobName()
	{
        return _jobName;
	}

    threadJob::~threadJob()
	{
      if(_jobName != NULL)
		  free(_jobName);
	}

	void threadJob::setWorkThread(threadWork* work)
	{
		_work = work;
	}
};
