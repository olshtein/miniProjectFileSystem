#pragma once

#include <bitset>
#include "BaseSector.h"

using namespace std;

typedef bitset<1600> DATtype; 

/*************************************************
* STRUCT
*	Dat
* INHERITS
*	BaseSector
* MEANING
*	Struct representing a sector-length DAT in a disk.
* SEE ALSO
*   SectorBase
*	Sector
*   VolumeHeader
*	FileHeader
*	RD_Sector
**************************************************/
struct Dat : BaseSector
{
	DATtype DAT;
	char emptyArea[812];  ///שמור לשימוש עתידי
};
