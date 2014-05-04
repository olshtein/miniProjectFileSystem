#pragma once

#include "BaseSector.h"
#include "RD_Sector.h"

// root dir length
const int ROOT_DIR_LENGTH = MAX_DIR_IN_SECTOR * 2;

/*************************************************
* STRUCT
*	RootDirectory
* MEANING
*	Struct representing a 2 sector-length long root directory in a disk.
* SEE ALSO
*	Sector
*	RD_Sector
**************************************************/
struct RootDirectory
{
	// sectors of entries in the directory
	RD_Sector sector1;
	RD_Sector sector2;

/*************************************************
* FUNCTION
*	operator[]
* PARAMETERS
*	int - index
* RETURN VALUE
*	pointer to DirEntry
* MEANING
*	returns value at index i as if both sector's array was one.
**************************************************/
	DirEntry* operator [] (int i)
	{
		
			if(i>=0&&i<MAX_DIR_IN_SECTOR)
			{

				return &sector1.dir[i];
			}
			if(i>=MAX_DIR_IN_SECTOR && i<ROOT_DIR_LENGTH)
			{          
				return &sector2.dir[i-MAX_DIR_IN_SECTOR];
			}

			throw exception("ERROR: Invalid Index value (at RootDirectory::operator[](int))"); 
	}
DirEntry* fondFile(string & fileOwner)
{
	for(int i=0;i<ROOT_DIR_LENGTH;i++)
		if (operator[](i)->fileOwner == fileOwner)
			return &sector1.dir[i];
	return NULL;
}
};

