#pragma once

/*************************************************
* STRUCT
*	BaseSector
* MEANING
*	Struct representing basic data types used in all sector-type sturcts.
* SEE ALSO
*   Sector
*   VolumeHeader
*	FileHeader
*	DAT
*	RD_Sector
**************************************************/
struct BaseSector
{
	unsigned int sectorNr; // sector's secuational number.
};