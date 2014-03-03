#pragma once

#include "BaseSector.h"

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
	char rawData [1020];
};

