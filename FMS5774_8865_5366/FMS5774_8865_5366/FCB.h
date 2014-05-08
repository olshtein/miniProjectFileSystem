#pragma once

#include "Disk.h"

using namespace std;

class Disk;

enum IOState
{

	I, // Input
	O, // Output
	IO, // Input and Output
	E // Edition.


};

IOState static conver(const string & io)
{
	if (io=="I")
		return I;
	if (io=="O")
		return O;
	if (io=="IO")
		return IO;
	if (io=="E")
		return E;
	throw exception("ERROR: Bad I/O value");
};

class FCB
{
	
public:
	Disk * d;
	DirEntry fileDesc;
	DATtype FAT;
	Sector Buffer;

	bool lock;
	bool changeBuf;
	bool changeDir;
	unsigned int placeDir;
	unsigned int currRecNr;//מספר סידורי של הרשומה הנוכחית, בתוך הקובץ
	unsigned int currSecNr;//מספר סידורי של סקטור הנוכחית, בתוך הקובץ
	unsigned int currRecNrInBuff;//מספר סידורי של הרשומה הנוכחית, בתוך הסקטור
	IOState iostate; //האם הפתיחה היא לכתיבה וקריאה



	FCB();
	FCB(Disk *);
	~FCB(void);
	void closefile();
	void flushfile();
	 void readRec(char *, unsigned int = 0);
	 void writeRec(char *);
	 void writeUpdateRec(char *);
	 void seekRec(unsigned int, int);
	 void deleteRec();
	 void updateRec(char *);
	 void readNewSectorToBuffer(unsigned int );
	 bool isClose(){ return d != NULL ?  true : throw exception("File closed! You can not access the file.");}
	void updateCancel();


};

