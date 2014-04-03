#pragma once

#include "BaseSector.h"
#include "DAT.h"
#include "DirEntry.h"

/*************************************************
* STRUCT
*	FileHeader
* INHERITS
*	BaseSector
* MEANING
*	Struct representing a sector-legth file header in a disk.
* SEE ALSO
*   SectorBase
*	Sector
*   VolumeHeader
*	DAT
*	RD_Sector
**************************************************/
struct FileHeader : BaseSector
{
DirEntry fileDesc ; // file description - a DirEntry containing the file data.
DATtype FAT; // FAT
char emptyArea[744];
};

