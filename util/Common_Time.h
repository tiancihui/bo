#ifndef __COMMON_Time__
#define __COMMON_Time__

namespace Common
{
#ifdef __cplusplus
	extern "C" 
	{
#endif
		unsigned long getTimeCurSec();


		unsigned long long  getTimeCurUSec();


		void getCurStr(char* timeStr);

#ifdef __cplusplus
	}
#endif

};
#endif