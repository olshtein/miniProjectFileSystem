#pragma once

#include "BaseSector.h"
#include "RD_Sector.h"

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

	RD_Sector sector1;
	RD_Sector sector2;

	RootDirectory(void);
	~RootDirectory(void);


	DirEntry &  operator [] (int i)
	{
		
			if(i>=0&&i<MAX_DIR_IN_SECTOR)
			{

				return sector1.dir[i];
			}
			if(i>=MAX_DIR_IN_SECTOR && i<MAX_DIR_IN_SECTOR*2)
			{          
				return sector2.dir[i-MAX_DIR_IN_SECTOR];
			}

			throw string("Invalid Index value"); 
	}
		
	
};

