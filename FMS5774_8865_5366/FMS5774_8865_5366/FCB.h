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
	 void read(char *, [unsigned int]);
	 void write(char *);
	 void seek(unsigned int, int);
	 void write(char *);
	 void Delete();
	 void update(char *);
};

