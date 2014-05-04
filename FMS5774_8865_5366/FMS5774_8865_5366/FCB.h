#pragma once

#include "Disk.h"

using namespace std;

class Disk;

enum IOState
{
<<<<<<< HEAD

=======
>>>>>>> da6510f63494945978b472fe136b62402a2ed510
	I, // Input
	O, // Output
	IO, // Input and Output
	E // Edition.
<<<<<<< HEAD

=======
>>>>>>> da6510f63494945978b472fe136b62402a2ed510
};


class FCB
{
	
public:
	Disk * d;
	DirEntry fileDesc;
	DATtype FAT;
	Sector Buffer;
<<<<<<< HEAD
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int currRecNrInBuff;

	IOState iostate; //האם הפתיחה היא לכתיבה וקריאה
	bool lock;
	bool changeBuf;
	bool changeDir;
	unsigned int placeDir;
=======
	bool change; //האם נעשו שינויים בקובץ
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int currRecNrInBuff;
	IOState iostate; //האם הפתיחה היא לכתיבה וקריאה
	bool change;
>>>>>>> da6510f63494945978b472fe136b62402a2ed510
	FCB();
	FCB(Disk *);
	~FCB(void);
	void closefile();
<<<<<<< HEAD

	void flushfile();
=======
	 void flushfile();
>>>>>>> da6510f63494945978b472fe136b62402a2ed510
	 void readRec(char *, [unsigned int]);
	 void writeRec(char *);
	 void seekRec(unsigned int, int);
	 void writeRec(char *);
	 void deleteRec();
	 void updateRec(char *);
<<<<<<< HEAD

=======
>>>>>>> da6510f63494945978b472fe136b62402a2ed510
};

