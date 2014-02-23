#pragma once
#include "DAT.h"
#include "DirEntry.h"

struct FileHeader
{
unsigned int sectorNr;  //מספר סידורי של הסקטור בדיסק
DirEntry fileDesc ; // העתק של כניסתו של הקובץ בתיקייה (file descriptor)
DATtype FAT; // FAT

char emptyArea[744];  //שמור לשימוש עתידי
};

