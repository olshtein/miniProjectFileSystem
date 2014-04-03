#pragma once

#include "BaseSector.h"

/*************************************************
* STRUCT
*	VolumeHeader
* INHERITS
*	BaseSector
* MEANING
*	Struct representing a sector-length volume header of a disk.
* SEE ALSO
*   SectorBase
*	Sector
*   DAT
*	FileHeader
*	RD_Sector
**************************************************/
struct VolumeHeader : BaseSector
{
	char diskName[12]; //disk name
	char diskOwner[12]; //disk owner name   
	char prodDate[11]; //file creation date in dd/mm/yyyy format
	unsigned intClusQty; //sum of clusters in disk
	unsigned int dataClusQty; //sum of data only clusters in disk
	unsigned int addrDAT; //address in disk containing the DAT
	unsigned int addrRootDir; //address in disk containing the first sector of the Root Directory
	unsigned int addrDATcpy; //address in disk containing the copy of the DAT
	unsigned int addrRootDirCpy; //address in disk containing the first sector of the copy of the Root  Directory
	unsigned int addrDataStart;  //first cluster in the disk dedicated for data
	char formatDate [11];  //last format date in dd/mm/yyyy format
	bool isFormated; // is the disk formated
	char emptyArea [944];
};