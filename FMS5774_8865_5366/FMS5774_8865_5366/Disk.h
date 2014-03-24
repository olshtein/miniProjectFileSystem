#pragma once

#include "DAT.h"
#include "DirEntry.h"
#include "FileHeader.h"
#include "RootDirectory.h"
#include "Sector.h"
#include "VolumeHeader.h"
#include <fstream>
#include "Functions.h"
#include <Tuple>
#include <vector>
#include <map>

using namespace std;

typedef  map<int,int> intmap;
typedef  map<int,int>::iterator it_intmap;

/*************************************************
* CLASS
*	Disk
* MEANING
*	Class representing a virtual disk.
* SEE ALSO
*	Sector
*   VolumeHeader
*	FileHeader
*	DAT
*	RoodDirectory
**************************************************/
class Disk
{
	friend class  TestLevel_0;
private:

	VolumeHeader vhd;
	Dat dat;  
	RootDirectory rootdir;
	bool mounted;
	fstream dskfl;
	unsigned int currDiskSectorNr; //המספר הסידורי של הסקטור בדיסק שכרגע בחוצץ של קובץ מסוים

public:
	
/*************************************************
* FUNCTION
*	ctor
* MEANING
*	constructs a disk with all fields with default values, w/o saving file.
* SEE ALSO
*   Disk(string&, string&, char)
*	~Disk(void)
**************************************************/
	Disk(void);

	
/*************************************************
* FUNCTION
*	ctor
* PARAMETERS
*	stirng&- Disk file path
*	string&- Disk owner
*	char-	[c]reate and mount new disk OR
			[m]ount existing disk.
* MEANING
*   Constructs a disk according to the given parameters.
* SEE ALSO
*   Disk(void)
*	~Disk(void)
*	createdisk(string&, string&)
*	createdisk(string&)
*	mountdisk(string&)
**************************************************/
	Disk (string &, string &, char);

	
/*************************************************
* FUNCTION
*	dtor
* MEANING
*	deconstructs the disk.
* SEE ALSO
*	Disk(void)
*	Disk(string&, string&, char)
**************************************************/
	~Disk(void);
	
/*************************************************
* FUNCTION
*	createdisk
* PARAMETERS
*	string&- Disk file path
*	string&- Disk owner name
* MEANING
*	creates a new disk, and saves to file.
* SEE ALSO
*   createdisk(string&)
*	mountdisk(string&)
**************************************************/
	void createdisk(string &, string &);

/*************************************************
* FUNCTION
*	createdisk
* PARAMETERS
*	string&- Owner name
* MEANING
*	creates a new disk, and saves to file. Does not init file.
* SEE ALSO
*   createdisk(string&, string&)
*	mountdisk(string&)
**************************************************/
	void createdisk( string &);

/*************************************************
* FUNCTION
*	mountdisk
* PARAMETERS
*	string&- Disk file path
* MEANING
*	mounts disk from file.
* SEE ALSO
*   createdisk(string&, string&)
*	createdisk(string&)
*	unmountdisk()
*	savechanges()
**************************************************/
	void mountdisk(string &);

/*************************************************
* FUNCTION
*	unmountdisk
* MEANING
*	unmounts a disk - saves data to file.
* SEE ALSO
*   createdisk(string&, string&)
*	createdisk(string&)
*	mountdisk(string&)
**************************************************/
	void unmountdisk();

	/*************************************************
* FUNCTION
*	recreatedisk
* PARAMETERS
*	string&- Disk file path
* MEANING
*	returns disk back to last save.
* SEE ALSO
*   createdisk(string&, string&)
*	createdisk(string&)
*	savechanges()
**************************************************/
	void recreatedisk(string &);

/*************************************************
* FUNCTION
*	getdskfl
* RETURN VALUE
*	copy of disk fstream.
**************************************************/
	fstream* const getdskfl();

/*************************************************
* FUNCTION
*	seekToSector
* PARAMETERS
*	unsigned int- sector to seek to.
* MEANING
*	moves disk current sector number to desired sector.
* SEE ALSO
*	writeSector(unsigned int, Sector*)
*	writeSector(Sector*)
*	readSector(int, Sector*)
*	readSector(Sector*)
**************************************************/
	void seekToSector(unsigned int);

/*************************************************
* FUNCTION
*	writeSector
* PARAMETERS
*	unsigned int- sector to write
*	Sector*- pointer to sector data to write
* MEANING
*	writes the data sector, into the requested sector.
* SEE ALSO
*	seekToSector(unsigned int)
*	writeSector(Sector*)
*	readSector(int, Sector*)
*	readSector(Sector*)
**************************************************/
	void writeSector(unsigned int, Sector*);

/*************************************************
* FUNCTION
*	writeSector
* PARAMETERS
*	Sector*- pointer to sector data to write 
* MEANING
*	writes the data sector, into the current sector on the disk.
* SEE ALSO
*	seekToSector(unsigned int)
*	writeSector(unsigned int, Sector*)
*	readSector(int, Sector*)
*	readSector(Sector*)
**************************************************/
	void writeSector(Sector*);

/*************************************************
* FUNCTION
*	readSector
* PARAMETERS
*	int- position of requested sector
*	Sector*- sector to read from
* MEANING
*	reads a sector in the requested postion to the data sector
* SEE ALSO
*	seekToSector(unsigned int)
*	writeSector(Sector*)
*	writeSector(unsigned int, Sector*)
*	readSector(Sector*)
**************************************************/
	void readSector(int, Sector*);

/*************************************************
* FUNCTION
*	readSector
* PARAMETERS
*	Sector*- sector to read from
* MEANING
*	reads the current sector the data sector
* SEE ALSO
*	seekToSector(unsigned int)
*	writeSector(Sector*)
*	writeSector(unsigned int, Sector*)
*	readSector(int, Sector*)
**************************************************/
	void readSector(Sector*);

private:
/*************************************************
* FUNCTION
*	savechanges
* MEANING
*	writes to file all changes in disk
* SEE ALSO
*	createdisk(string&)
*	unmountdisk()
**************************************************/
	void savechanges();

	/*************************************************
* FUNCTION
*	checkchanges
* PARAMETERS
*	Sector*- sector to check changes in
* RETURN VALUE
*	true if changes where made, false otherwise.
* MEANING
*	check if data in sector is diffrent then data on file
* SEE ALSO
*	savechanges()
**************************************************/
	bool checkchanges(Sector*);

/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/
	void format(string &);
	/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/
	int howmuchempty( );
/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/
	void alloc(DATtype &, unsigned int, unsigned int);
	/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/
	void allocextend(DATtype &, unsigned int, unsigned int);
	/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/
void dealloc(DATtype &);

/*************************************************
* FUNCTION
*	resetDat	
* MEANING
*  Reset the initial values ​​DAT	
* SEE ALSO
*	
**************************************************/
void resetDat();
	/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/
intmap* DiskMapping(DATtype&);
	/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/
//void createfile (string &,  string &, string &, unsigned int, unsigned int, string &, unsigned int, [unsigned int]) ;

/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/

/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/

	/*************************************************
* FUNCTION
*	
* PARAMETERS
*	
* RETURN VALUE
*
* MEANING
*	
* SEE ALSO
*	
**************************************************/

};

