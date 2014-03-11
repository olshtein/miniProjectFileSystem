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
	char diskName[12]; //שם זיהוי הדיסק
	char diskOwner[12]; //שם בעל הדיסק   
	char prodDate[11]; //תאריך יצור הדיסק (ddmmyyyy)
	unsigned intClusQty; //סה"כ יחידות הקצאה (clusters)  בדיסק
	unsigned int dataClusQty; //מספר יחידות הקצאה לנתונים בלבד
	unsigned int addrDAT; //כתובת הסקטור שמכיל את ה-DAT
	unsigned int addrRootDir; //כתובת ה-cluster שמכיל את התיקייה הראשית (Root Directory)
	unsigned int addrDATcpy; //כתובת הסקטור שמכיל עותק שני של ה-DAT 
	unsigned int addrRootDirCpy; //כתובת ה-cluster שמכיל עותק שני של התיקייה הראשית (Root Directory)  
	unsigned int addrDataStart;  //כתובת ה-cluster הראשון בדיסק המיועד לנתונים.
	char formatDate [11];  //תאריך פירמוט (ddmmyyyy)
	bool isFormated; // האם כבר מפורמט?
	char emptyArea [944]; //שמור לשימוש עתידי
};

