#include "Functions.h"


void Functions::dateNow(char* date)
{
	time_t t = time(0); 
	tm lt;
	localtime_s(&lt,&t);
	strftime(date, 11, "%m/%d/%Y",&lt);

	//sprintf(date, "%02d/%02d/%04d/0", lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
}