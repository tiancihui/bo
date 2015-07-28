#ifndef __THREAD_WORK__
#define __THREAD_WORK__

#include "thread.h"
#include "threadJob.h"
#include "threadPool.h"
#include "../util/util.h"

namespace Thread
{
	class threadPool;
	class threadJob;
	

    class threadWork : public thread
	{
		public:

		threadWork(threadPool* pool);

		virtual ~threadWork();
		
		void Run();

		void setJob(threadJob* job, void* argv);

		private:
		threadPool* _pool;
		threadJob * _job;
		void * _argv;
		Common::MutexLock _varMutex;
		Common::MutexLock _workMutex;
        Common::Condition _workCond;
	friend class threadPool;
	};
};
#endif
