#pragma once

#include "BaseSector.h"
 
const int SIZE_DATA_IN_SECTOR = 1024-sizeof(unsigned int);
/*************************************************
* STRUCT
*	Sector
* INHERITS
*	BaseSector
* MEANING
*	Struct representing a sector in a disk.
* SEE ALSO
*   SectorBase
*   VolumeHeader
*	FileHeader
*	DAT
*	RD_Sector
**************************************************/
struct Sector : BaseSector
{
	char rawData [SIZE_DATA_IN_SECTOR];
};

