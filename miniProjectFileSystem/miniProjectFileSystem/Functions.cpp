#include "Functions.h"


void Functions::dateNow(char* date)
{
	time_t t = time(0); 
	tm* lt = localtime(&t);
	sprintf(date, "%02d/%02d/%04d/0", lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
}