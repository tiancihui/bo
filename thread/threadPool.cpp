#include "threadPool.h"
#include "threadJob.h"
#include "threadWork.h"

namespace Thread
{

	threadPool::threadPool(int num)
		:_num(num),
		 _allNum(0),
		 _idleNum(0),
		 _busyNum(0),
	     _busyMutex(),
		 _idleMutex(),
		 _busyCond(_busyMutex),
		 _idleCond(_idleMutex)

	{
		_workBusyVec.clear();
		_workIdleVec.clear();

		for(int i=0; i< _num; i++)
		{
		   threadWork* work = new threadWork(this);
		   __appendIdleThread(work);
		   work->Start();
		}
	}

	threadPool::~threadPool()
	{
       StopAll();
	}

	void threadPool::Run(threadJob* job, void* argv)
	{
		assert(job != NULL);
       
//		_busyMutex.lock(__FUNCTION__,__LINE__);
		if(_busyNum == _allNum)
			_busyCond.wait();

		threadWork *idleThread = __getIdleThread();
		if(idleThread != NULL)
		{
		    idleThread->_workMutex.lock(__FUNCTION__,__LINE__);
			__idleMove2Busy(idleThread);
			job->setWorkThread(idleThread);
			idleThread->setJob(job, argv);
		}
//		_busyMutex.unlock(__FUNCTION__,__LINE__);
	}

	void threadPool::StopAll()
	{
		for(unsigned int i=0; i< _workAllVec.size(); i++)
		{
		   threadWork* work = _workAllVec[i];
		   work->Join();
		}
		
//		_workBusyVec.clear();
//		_workIdleVec.clear();
	}

	void threadPool::__createIdleThread(int num)
	{
		for(int i=0; i< num; i++)
		{
		   threadWork* work = new threadWork(this);
		   __appendIdleThread(work);
		   work->Start();
		}
		_num = _num + num;
	}

	void  threadPool::__deleteIdleThread(int num)
	{
		_idleMutex.lock(__FUNCTION__,__LINE__);
		for(int i=0; i < num; i++)
		{
			if(_workIdleVec.size() > 0)
			{
				threadWork *removeThread = _workIdleVec.front();
				std::vector<threadWork *>::iterator pos;
				pos = std::find(_workIdleVec.begin(), _workIdleVec.end(), removeThread);
				if(pos != _workIdleVec.end())
				{
					_workIdleVec.erase(pos);
					_idleNum--;
				}

				std::vector<threadWork *>::iterator posTemp;
				posTemp = find(_workAllVec.begin(), _workAllVec.end(), removeThread);
				if(posTemp != _workAllVec.end())
				{
					_workAllVec.erase(posTemp);
					_allNum--;
				}

			}
		}
		_idleMutex.unlock(__FUNCTION__,__LINE__);
	}

		void threadPool::__appendIdleThread(threadWork* jobThread)
		{
			_idleMutex.lock(__FUNCTION__,__LINE__);

			_workAllVec.push_back(jobThread);
			_workIdleVec.push_back(jobThread);
			_allNum++;
			_idleNum++;
			_idleMutex.unlock(__FUNCTION__,__LINE__);
		}

		threadWork* threadPool::__getIdleThread()
		{
			_idleMutex.lock(__FUNCTION__,__LINE__);
			while(_workIdleVec.size() == 0)
				_idleCond.wait();

			if(_workIdleVec.size() > 0)
			{
				threadWork *work = _workIdleVec.front();
				_idleMutex.unlock(__FUNCTION__,__LINE__);
				return work;
			}

			_idleMutex.unlock(__FUNCTION__,__LINE__);
			return NULL;
		}

	void threadPool::__busyMove2Idle(threadWork* busyThread)
	{

		_idleMutex.lock(__FUNCTION__,__LINE__);
		_workIdleVec.push_back(busyThread);
		_idleNum++;
		_idleMutex.unlock(__FUNCTION__,__LINE__);


		_busyMutex.lock(__FUNCTION__,__LINE__);
		std::vector<threadWork *>::iterator pos;
		pos = find(_workBusyVec.begin(), _workBusyVec.end(), busyThread);
		if(pos != _workBusyVec.end())
		{
			_workBusyVec.erase(pos);
			_busyNum--;
		}
		_busyMutex.unlock(__FUNCTION__,__LINE__);

        _idleCond.notify();
        _busyCond.notify();
	}

	void threadPool::__idleMove2Busy(threadWork* idleThread)
	{
		_busyMutex.lock(__FUNCTION__,__LINE__);
		_workBusyVec.push_back(idleThread);
		_busyNum++;
		_busyMutex.unlock(__FUNCTION__,__LINE__);


		_idleMutex.lock(__FUNCTION__,__LINE__);
		std::vector<threadWork *>::iterator pos;
		pos = find(_workIdleVec.begin(), _workIdleVec.end(), idleThread);
		if(pos != _workIdleVec.end())
		{
			_workIdleVec.erase(pos);
			_idleNum--;
		}
		_idleMutex.unlock(__FUNCTION__,__LINE__);
	}

};
