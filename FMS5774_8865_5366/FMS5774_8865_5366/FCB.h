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
	bool change; //��� ���� ������� �����
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int currRecNrInBuff;
	IOState iostate; //��� ������ ��� ������ ������
	bool change;
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

