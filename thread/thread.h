#ifndef __THREAD__
#define __THREAD__

namespace Thread
{

class thread
{
	public:

		thread();
		virtual ~thread();

		static void* ThreadFunction(void *argv);

		virtual void  Run(void)=0;

		void setErrorCode(int error)
		{
		   _error = error;
		}

		int getErrorCode(void)
		{
		   return _error;
		}


		void Start();
		void Join();
		void Stop();
		void Exit();
		void WakeUp();

	private:
		int _error;

};
};
#endif
