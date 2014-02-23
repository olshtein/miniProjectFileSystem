#pragma once
#include "DirEntry.h"

const int MAX_DIR_IN_SECTOR = 14;

struct RootDirectory
{

	unsigned int sectorNr_1; //סקטור של תחילת הקלאסטר
	DirEntry dir_1[MAX_DIR_IN_SECTOR];
	char emptyArea_1[12];

	unsigned int sectorNr_2;
	DirEntry dir_2[MAX_DIR_IN_SECTOR];
	char emptyArea_2[12];

	RootDirectory(void);
	~RootDirectory(void);


	DirEntry &  operator [] (int i)
	{
		
			if(i>=0&&i<MAX_DIR_IN_SECTOR)
			{

				return dir_1[i];
			}
			if(i>=MAX_DIR_IN_SECTOR && i<MAX_DIR_IN_SECTOR*2)
			{          
				return dir_2[i-MAX_DIR_IN_SECTOR];
			}

			throw string("Invalid Index value"); 
	}
		
	
};

