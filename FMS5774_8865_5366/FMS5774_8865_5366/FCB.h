#pragma once

#include "Disk.h"

using namespace std;

enum IOState
{
	I, // Input
	O, // Output
	IO, // Input and Output
	E // Edition.
};

class FCB
{
public:
	Disk * d;
	DirEntry fileDesc;
	DATtype FAT;
	Sector Buffer;
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int currRecNrInBuff;
	IOState iostate; //האם הפתיחה היא לכתיבה וקריאה
	bool change;
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

