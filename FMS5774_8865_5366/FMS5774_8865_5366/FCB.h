#pragma once

#include "Disk.h"

using namespace std;

enum IOState
{
<<<<<<< HEAD
	I,
	O,
	IandO,
	E
=======
	I, // Input
	O, // Output
	IO, // Input and Output
	E // Edition.
>>>>>>> 67792b9121b4b2b2e8895a71ab1c115dfb27fb67
};

class FCB
{
	
public:
	Disk * d;
	DirEntry fileDesc;
	DATtype FAT;
	Sector Buffer;
	IO io; //האם הפתיחה היא לכתיבה וקריאה
	bool change; //האם נעשו שינויים בקובץ
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int currRecNrInBuff;
<<<<<<< HEAD

=======
	IOState iostate; //האם הפתיחה היא לכתיבה וקריאה
	bool change;
>>>>>>> 67792b9121b4b2b2e8895a71ab1c115dfb27fb67
	FCB();
	FCB(Disk *);
	~FCB(void);
	void closefile();
<<<<<<< HEAD
	 void flushfile();
	 void readRec(char *, [unsigned int]);
	 void writeRec(char *);
	 void seekRec(unsigned int, int);
	 void writeRec(char *);
	 void deleteRec();
	 void updateRec(char *);
=======
	void flushfile();
	void read(char *, [unsigned int]);
	void write(char *);
	void seek(unsigned int, int);
	void write(char *);
	void Delete();
	void update(char *);
>>>>>>> 67792b9121b4b2b2e8895a71ab1c115dfb27fb67
};

