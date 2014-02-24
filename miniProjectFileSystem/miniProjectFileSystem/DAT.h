#pragma once

#include <bitset>
#include "BaseSector.h"

using namespace std;

typedef bitset<1600> DATtype; 

struct Dat : BaseSector
{
	DATtype DAT;
	char emptyArea[820];  ///שמור לשימוש עתידי
};
