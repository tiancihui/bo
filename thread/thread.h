#ifndef __THREAD__
#define __THREAD__

namespace Thread
{

class thread
{
	public:

		thread();
		virtual ~thread();

		virtual void  Run(void)=0;
        static  void* ThreadFunction(void *argv);
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
