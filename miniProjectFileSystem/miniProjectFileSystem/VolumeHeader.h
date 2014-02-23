#pragma once
struct VolumeHeader
{
	unsigned int sectorNr; // מספר סידורי של הסקטור בדיסק 
	char diskName[12]; //שם זיהוי הדיסק
	char diskOwner[12]; //שם בעל הדיסק   
	char prodDate[10]; //תאריך יצור הדיסק (ddmmyyyy)
	unsigned intClusQty; //סה"כ יחידות הקצאה (clusters)  בדיסק
	unsigned int dataClusQty; //מספר יחידות הקצאה לנתונים בלבד
	unsigned int addrDAT; //כתובת הסקטור שמכיל את ה-DAT
	unsigned int addrRootDir; //כתובת ה-cluster שמכיל את התיקייה הראשית (Root Directory)
	unsigned int addrDATcpy; //כתובת הסקטור שמכיל עותק שני של ה-DAT 
	unsigned int addrRootDirCpy; //כתובת ה-cluster שמכיל עותק שני של התיקייה הראשית (Root Directory)  
	unsigned int addrDataStart;  //כתובת ה-cluster הראשון בדיסק המיועד לנתונים.
	char formatDate [10];  //תאריך פירמוט (ddmmyyyy)
	bool isFormated; // האם כבר מפורמט?
	char emptyArea [944]; //שמור לשימוש עתידי
};

