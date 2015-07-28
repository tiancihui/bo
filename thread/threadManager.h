#ifndef __THREAD_MANAGER__
#define __THREAD_MANAGER__

namespace Thread
{

class threadPool;
class threadJob;

class threadManager
{
	public:	
		threadManager();

		threadManager(int num);
		virtual ~threadManager();

		void Run(threadJob* job, void *argv);
		void StopAll();

	private:
		threadPool* _poll;
		int _num;
};
};
#endif
