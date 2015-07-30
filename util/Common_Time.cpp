#include "Common_Time.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

namespace Common
{

	unsigned long getTimeCurSec()
	{
		struct timeval tv;
		unsigned long  timeSe = 0;
		int result = gettimeofday(&tv, NULL);
		timeSe = tv.tv_sec;
		return timeSe;
	}

	unsigned long long  getTimeCurUSec()
	{
		struct tm *t;
		struct timeval tv;
		unsigned long long timeUse = 0;
		int result = gettimeofday(&tv, NULL);
		timeUse = tv.tv_sec;
		timeUse = timeUse*1000 + tv.tv_usec/1000;
		return timeUse;
	}

	void getCurStr(char* timeStr)
	{
		struct tm *t;
		struct timeval tv;
		int result = gettimeofday(&tv, NULL);
		t=localtime(&(tv.tv_sec));
		sprintf(timeStr,"%4dÄê%02dÔÂ%02dÈÕ %02d:%02d:%02d:%06d\n\0",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec,tv.tv_usec);
	}

};