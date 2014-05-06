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
	unsigned int currRecNr;//���� ������ �� ������ �������, ���� �����
	unsigned int currSecNr;//���� ������ �� ����� �������, ���� �����
	unsigned int currRecNrInBuff;//���� ������ �� ������ �������, ���� ������
	IOState iostate; //��� ������ ��� ������ ������


	FCB();
	FCB(Disk *);
	~FCB(void);
	void closefile();
	void flushfile();
	 void readRec(char *, unsigned int = 0);
	 void writeRec(char *);
	 void seekRec(unsigned int, int);
	 void deleteRec();
	 void updateRec(char *);
	 void readNewSectorToBuffer(unsigned int );

	void updateCancel();


};

