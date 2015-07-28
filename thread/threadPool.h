#ifndef __THREAD_POOL_
#define __THREAD_POOL_

#include "../util/util.h"
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

namespace Thread
{
	class threadJob;
	class threadWork;

	class threadPool :public Common::MutexLock
	{
		public:
			threadPool(int num);

			virtual ~threadPool();


			void Run(threadJob* job, void* argv);
            void StopAll();

		protected:
			void __createIdleThread(int num);
			void __deleteIdleThread(int num);
			void __appendIdleThread(threadWork* jobThread);

			threadWork*  __getIdleThread();

			void __busyMove2Idle(threadWork* busyThread);
			void __idleMove2Busy(threadWork* idleThread);


		private:
			int _num;
			int _allNum,_idleNum,_busyNum;

			Common::MutexLock _busyMutex;
			Common::MutexLock _idleMutex;

			Common::Condition _busyCond;  
			Common::Condition _idleCond;  

			std::vector<threadWork *> _workAllVec;
			std::vector<threadWork *> _workBusyVec;
			std::vector<threadWork *> _workIdleVec;

	   friend class threadWork;
};
};
#endif
