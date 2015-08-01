#include "../thread/threadJob.h"
#include "../thread/threadManager.h"
#include <unistd.h>
#include <stdio.h>

#include "../util/Common_Time.h"
typedef struct JobData
{
    char message[1024];
}JobData;

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
		    JobData *data = (struct JobData*)jobdata;
			printf("%s\n", data->message); 
			delete data;
		}
	private:
		int i;
};


int main(int argc, char* argv[])
{


	Thread::threadManager* manage = new Thread::threadManager(10);  

	sleep(2);  
	for(int i=0;i<10000;i++)  
	{  
/*		
		usleep(10);
		JobData *data = new JobData();
		memset(data->message,'0',1024);
        sprintf(data->message,"message %d",i);		
		CYJob * job = new CYJob();  
		manage->Run(job,data);  
*/
		sleep(1);
		char buffer[1024];
		Common::getCurStr(buffer);
		printf("%s\r\n",buffer);
	}  

    while(1)
	{
	   sleep(1);
	}

	manage->StopAll(); 
	return 0;
}
