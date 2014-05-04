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
IOState conver(const string & io)
{
	if (io=="I")
		return I;
	if (io=="O")
		return I;
	if (io=="IO")
		return I;
	if (io=="E")
		return I;
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
<<<<<<< HEAD
	 void readRec(char *, unsigned int = 0);
	 void writeRec(char *);
	 void seekRec(unsigned int, int);
	 void deleteRec();
	 void updateRec(char *);
	 void readNewSectorToBuffer();

=======
	void readRec(char *, unsigned int=0);
	void writeRec(char *);
	void seekRec(unsigned int, int);
	void writeRec(char *);
	void updateCancel();
	void deleteRec();
	void updateRec(char *);
>>>>>>> cc4ba045de7c2e665a1edcbcdf9e15e70e62da62

};

