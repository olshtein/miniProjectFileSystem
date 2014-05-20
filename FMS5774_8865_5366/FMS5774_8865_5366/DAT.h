#pragma once

#include <bitset>
#include "BaseSector.h"

using namespace std;

unsigned int const BIT_SET_SIZE = 1600;

//a set of 1600 bits representing a DAT like structure.
typedef bitset<BIT_SET_SIZE> DATtype; 

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
	DATtype DAT; // the DAT
	char emptyArea[812];  ///שמור לשימוש עתידי

	// operator <<
	friend void operator<< (std::stringstream ss, const Dat dat)
	{
		ss << dat.sectorNr;
		ss << dat.DAT;
		ss << dat.emptyArea;
	}
};