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
	unsigned int static const NAME_STRING_SIZE = 12;
	unsigned int static const DATE_STRING_SIZE = 11;  

	char diskName[NAME_STRING_SIZE]; //disk name
	char diskOwner[NAME_STRING_SIZE]; //disk owner name   
	char prodDate[DATE_STRING_SIZE]; //file creation date in dd/mm/yyyy format
	unsigned intClusQty; //sum of clusters in disk
	unsigned int dataClusQty; //sum of data only clusters in disk
	unsigned int addrDAT; //address in disk containing the DAT
	unsigned int addrRootDir; //address in disk containing the first sector of the Root Directory
	unsigned int addrDATcpy; //address in disk containing the copy of the DAT
	unsigned int addrRootDirCpy; //address in disk containing the first sector of the copy of the Root  Directory
	unsigned int addrDataStart;  //first cluster in the disk dedicated for data
	char formatDate [DATE_STRING_SIZE];  //last format date in dd/mm/yyyy format
	bool isFormated; // is the disk formated
	char emptyArea [944];
};