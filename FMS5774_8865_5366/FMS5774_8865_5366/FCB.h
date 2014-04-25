#pragma once

#include "Disk.h"

using namespace std;

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

 FCB *openfile(string &, string &, string &);
	FCB();
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

