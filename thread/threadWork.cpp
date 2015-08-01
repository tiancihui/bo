#include "threadWork.h"

namespace Thread
{

	threadWork::threadWork(threadPool* pool)
		: _pool(pool),
		_job(NULL),
		_argv(NULL),
     	_varMutex(),
		_workMutex(),
		_workCond(_workMutex)
	{

	}

	threadWork::~threadWork()
	{
		_argv = NULL;
        if(_job != NULL)
		{
		  delete _job ;
		}
		_pool = NULL;
	}


	void threadWork::Run()
	{
        for(;;)
		{
		  
           _workMutex.lock(__FUNCTION__,__LINE__);
		   while(_job == NULL)
		   {
			   _workCond.wait();
		   }

		   _job->Run(_argv);

		   _job->setWorkThread(NULL);
		   _job = NULL;
		   _pool->__busyMove2Idle(this);

           	_workMutex.unlock(__FUNCTION__,__LINE__);
		}
	}

	void threadWork::setJob(threadJob* job, void* argv)
	{
        _varMutex.lock(__FUNCTION__,__LINE__);
		_job = job;
		_argv = argv;
		_job->setWorkThread(this);
        _varMutex.unlock(__FUNCTION__,__LINE__);
        
		_workCond.notify();
        _workMutex.unlock(__FUNCTION__,__LINE__);

	}

};
