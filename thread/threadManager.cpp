#include "threadManager.h"
#include "threadJob.h"
#include "threadPool.h"

namespace Thread
{
	threadManager::threadManager()
		:_num(16)
	{
	    _poll = new threadPool(_num);
	}

	threadManager::threadManager(int num)
		:_num(num)
	{
	
	    _poll = new threadPool(_num);
	}

    threadManager::~threadManager()
	{
		if(_poll)
		{
		  delete _poll;
		}
	}

	void threadManager::Run(threadJob* job, void *argv)
	{
		if(_poll)
		{
		  _poll->Run(job, argv);
		}
	}

	void threadManager::StopAll()
	{
		if(_poll)
		{
			_poll->StopAll();
		}
	}

};
