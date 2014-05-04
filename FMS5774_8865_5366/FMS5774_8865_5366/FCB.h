#pragma once

#include "Disk.h"

using namespace std;

enum IO
{
	I,
	O,
	IandO,
	E
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

	FCB();
	FCB(Disk *);
	~FCB(void);
	void closefile();
	 void flushfile();
	 void readRec(char *, [unsigned int]);
	 void writeRec(char *);
	 void seekRec(unsigned int, int);
	 void writeRec(char *);
	 void deleteRec();
	 void updateRec(char *);
};

