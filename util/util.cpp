#include"util.h"
#include <stdio.h>

namespace Common
{
	MutexLock::MutexLock()
	{
//		printf("Construct %p\r\n",this);
		pthread_mutex_init(&_mutex, NULL);
	}

	MutexLock::~MutexLock()
	{
//		printf("destory %p\r\n",this);
        pthread_mutex_destroy(&_mutex);
//		pthread_mutex_destory(&_mutex);
	}

	pthread_mutex_t* MutexLock::getPthreadMutex()
	{
		return &_mutex;
	}

	void MutexLock::lock(const char* debuginfo,int line)
	{
//		printf("lock %p  %s %d\r\n",this,debuginfo,line);
		pthread_mutex_lock(&_mutex);
	}

	void MutexLock::unlock(const char* debuginfo,int line)
	{
//		printf("unlock %p  %s %d\r\n",this,debuginfo,line);
		pthread_mutex_unlock(&_mutex);
	}



	GuardLock::GuardLock(MutexLock  *mutexLock)
		:_mutexLock(mutexLock)
	{
		_mutexLock->lock(__FUNCTION__,__LINE__);
	}

	GuardLock::~GuardLock()
	{
		_mutexLock->unlock(__FUNCTION__,__LINE__);
	}

	Condition::Condition(MutexLock &mutex)
		:_mutex(mutex)
	{
		pthread_cond_init(&_condition, NULL);
	}

	Condition::~Condition()
	{
		pthread_cond_destroy(&_condition);
	}

	void Condition::wait()
	{
		pthread_cond_wait(&_condition, _mutex.getPthreadMutex());
	}

	void Condition::notify()
	{
		pthread_cond_signal(&_condition);
	}

	void Condition::notifyAll()
	{
		pthread_cond_broadcast(&_condition);
	}

};
