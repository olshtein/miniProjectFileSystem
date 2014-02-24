#pragma once

#include "BaseSector.h"
#include "DAT.h"
#include "DirEntry.h"

struct FileHeader : BaseSector
{
DirEntry fileDesc ; // העתק של כניסתו של הקובץ בתיקייה (file descriptor)
DATtype FAT; // FAT

char emptyArea[744];  //שמור לשימוש עתידי
};

