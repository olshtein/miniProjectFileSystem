#pragma once
#include <bitset>
using namespace std;

typedef bitset<1600> DATtype; 

struct Dat
{
	unsigned int sectorNr; //מספר סידורי של הסקטור בדיסק
	DATtype DAT;
	char emptyArea[820];  ///שמור לשימוש עתידי
};
