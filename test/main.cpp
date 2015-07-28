#include "../thread/threadJob.h"
#include "../thread/threadManager.h"
#include <unistd.h>

class CYJob : public Thread::threadJob    
{  
	public:  
		CYJob()  
		{  
			i=0;  
		}  

		~CYJob()  
		{
		}  

		void Run(void* jobdata)      
		{  
			printf("The Job comes from CYJob/n");  
		}
	private:
		int i;
};


int main()
{
	Thread::threadManager* manage = new Thread::threadManager(10);  

	for(int i=0;i<40;i++)  
	{  
		CYJob * job = new CYJob();  
		manage->Run(job,NULL);  
	}  

	sleep(2);  

//	CYJob* job = new CYJob();  
//	manage->Run(job,NULL);  

	manage->StopAll(); 

}
