#include"util.h"

namespace Common
{
	MutexLock::MutexLock()
	{
		pthread_mutex_init(&_mutex, NULL);
	}

	MutexLock::~MutexLock()
	{
        pthread_mutex_destroy(&_mutex);
//		pthread_mutex_destory(&_mutex);
	}

	pthread_mutex_t* MutexLock::getPthreadMutex()
	{
		return &_mutex;
	}

	void MutexLock::lock()
	{
		pthread_mutex_lock(&_mutex);
	}

	void MutexLock::unlock()
	{
		pthread_mutex_unlock(&_mutex);
	}



	GuardLock::GuardLock(MutexLock  *mutexLock)
		:_mutexLock(mutexLock)
	{
		_mutexLock->lock();
	}

	GuardLock::~GuardLock()
	{
		_mutexLock->unlock();
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
