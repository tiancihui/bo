#ifndef __UTIL__
#define __UTIL__

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

namespace Common
{
	class MutexLock;
	class GuardLock;

	class MutexLock
	{
		public:
			MutexLock();

			~MutexLock();

			pthread_mutex_t* getPthreadMutex();

			void lock();

			void unlock();

		private:
			pthread_mutex_t _mutex;
	};

	class GuardLock
	{
		public:

			GuardLock(MutexLock  *mutexLock);

			~GuardLock();

		private:
			MutexLock*  _mutexLock;
	};

	class Condition
	{
		public:
			Condition(MutexLock &mutex);

			~Condition();

			void wait();

			void notify();

			void notifyAll();

		private:
			pthread_cond_t  _condition;
			MutexLock &  _mutex;
	};
};

#endif
