#pragma once

#include "DAT.h"
#include "DirEntry.h"
#include "FileHeader.h"
#include "RootDirectory.h"
#include "Sector.h"
#include "VolumeHeader.h"
#include <fstream>
#include "Functions.h"

using namespace std;

class Disk
{
	VolumeHeader vhd;
	Dat dat;  
	RootDirectory rootdir;
	bool mounted;
	fstream dskfl;
	unsigned int currDiskSectorNr; //המספר הסידורי של הסקטור בדיסק שכרגע בחוצץ של קובץ מסוים

public:
	Disk(void);
	Disk (string &, string &, char);
	~Disk(void);
	void createdisk(string &, string &);
	void createdisk( string &);
	void mountdisk(string &);
	void unmountdisk();
	void recreatedisk(string &);
	fstream* const getdskfl();
	void seekToSector(unsigned int);
	void writeSector(unsigned int, Sector*);
	void writeSector(Sector*);
	void readSector(int, Sector*);
	void readSector(Sector*);
};

