#include "threadWork.h"

namespace Thread
{

	threadWork::threadWork(threadPool* pool)
		: _pool(NULL),
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
		   while(_job == NULL)
			   _workCond.wait();

		   _job->Run(_argv);

		   _job->setWorkThread(NULL);
		   _job = NULL;
		   _pool->__busyMove2Idle(this);

           _workMutex.unlock();
		}
	}

	void threadWork::setJob(threadJob* job, void* argv)
	{
        _varMutex.lock();
		_job = job;
		_argv = argv;
		_job->setWorkThread(this);
        _varMutex.unlock();
        
		_workCond.notify();

	}

};
