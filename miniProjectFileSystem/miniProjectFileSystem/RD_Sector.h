#pragma once

#include "BaseSector.h"
#include "DirEntry.h"

const int MAX_DIR_IN_SECTOR = 14;

/*************************************************
* STRUCT
*	RD_Sector (RootDirectory Sector)
* INHERITS
*	BaseSector
* MEANING
*	Struct representing a sector in the root directory of a disk.
* SEE ALSO
*   SectorBase
*	Sector
*   VolumeHeader
*	FileHeader
*	DAT
**************************************************/
struct RD_Sector : BaseSector
{
	DirEntry dir[MAX_DIR_IN_SECTOR];
	char emptyArea[12];
};