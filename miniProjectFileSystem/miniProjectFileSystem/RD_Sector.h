#pragma once

#include "BaseSector.h"
#include "DirEntry.h"

const int MAX_DIR_IN_SECTOR = 14;

struct RD_Sector : BaseSector
{
	DirEntry dir[MAX_DIR_IN_SECTOR];
	char emptyArea[12];
};