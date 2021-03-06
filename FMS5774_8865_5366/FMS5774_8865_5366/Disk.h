﻿#pragma once

#include <iostream>
#include <map>

#include "FileHeader.h"
#include "RootDirectory.h"
#include "Sector.h"
#include "VolumeHeader.h"
#include "Functions.h"
#include "FCB.h"

using namespace std;

// a map containing sets of indecies and sizes of empty DAT clusters, and an iterator for it. (<location in disk,num of clasters>
typedef  map<unsigned int,unsigned int> diskmap;
typedef  map<unsigned int,unsigned int>::iterator it_diskmap;

//disks path
string const DISK_PATH = "../../../Disks/";

class FCB;

/*************************************************
* ENUM
*	DiskConstractType
* MEANING
*	represents the different ways to constract a disk
* SEE ALSO
*   Disk
**************************************************/
enum DiskConstractType
{
	create = 'c',
	mount = 'm'
};

/*************************************************
* ENUM
*	FitType
* MEANING
*	represents the different algoritims to use in allocating DAT for file.
* SEE ALSO
*   Disk
**************************************************/
enum FitType
{
	firstFit,
	bestFit,
	worstFit
};

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

		VolumeHeader vhd; // disk volume header
		bool mounted; // is the disk mounted
		fstream dskfl; // the file stream to the disk
		unsigned int currDiskSectorNr; //corrent sector pointed at in the disk.
	public:
		RootDirectory rootdir; // the disk's Root Directory
		Dat dat;  // the disk's DAT

		string lastErrorMessage;//Stores message exception in case of error

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
		*	DiskConstractType-	[c]reate and mount new disk OR
		*						[m]ount existing disk.
		* MEANING
		*   Constructs a disk according to the given parameters.
		* SEE ALSO
		*   Disk(void)
		*	~Disk(void)
		*	createdisk(string&, string&)
		*	createdisk(string&)
		*	mountdisk(string&)
		**************************************************/
		 Disk (string &, string &, DiskConstractType);


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
		*	ismounted
		* MEANING
		*	checks if disk is mounted
		* RETURN VALUE
		*	bool
		* SEE ALSO
		*	mountdisk(string&)
		*	unmountdisk()
		**************************************************/
		bool ismounted();

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

		/*************************************************
		* FUNCTION
		*	format
		* PARAMETERS
		*	string & - Owner Name of the disk
		* MEANING
		*	Logically formatted disk (reset DAT)
		* SEE ALSO
		*
		**************************************************/
		void format(string &);

		/*************************************************
		* FUNCTION
		*	howmuchempty
		* RETURN VALUE
		*	number of empty clusters
		* MEANING
		*	checks how many empty clusters there are
		* SEE ALSO
		*	void alloc(DATtype &, unsigned int, unsigned int)
		*	void alloc(DATtype &, unsigned int , unsigned int , unsigned int)
		*	void allocextend(DATtype &, unsigned int, unsigned int)
		*	void dealloc(DATtype &)
		**************************************************/
		 unsigned int howmuchempty( );

		/*************************************************
		* FUNCTION
		*	alloc
		* PARAMETERS
		*	DATtype& - FAT
		*	unsigned int - number of sectors to allocate
		*	FitType - allgoritem type:
		*		0 - first fit
		*		1 - best fit
		*		2 - worst fit
		* MEANING
		*	allocates sectors and update the file's FAT
		* SEE ALSO
		*	void howmuchempty()
		*	void alloc(DATtype &, unsigned int , unsigned int , unsigned int)
		*	void allocextend(DATtype &, unsigned int, unsigned int)
		*	void dealloc(DATtype &)
		**************************************************/
		void alloc(DATtype &, unsigned int, FitType);

		/*************************************************
		* FUNCTION
		*	allocextend
		* PARAMETERS
		*	DATtype& - FAT
		*	unsigned int - number of sectors to allocate
		*	FitType - allgoritem type:
		*		0 - first fit
		*		1 - best fit
		*		2 - worst fit
		* MEANING
		*	allocates more sectors and update the file's FAT
		* SEE ALSO
		*	void howmuchempty()
		*	void alloc(DATtype &, unsigned int , unsigned int)
		*	void alloc(DATtype &, unsigned int , unsigned int , unsigned int)
		*	void dealloc(DATtype &)
		**************************************************/
		void allocextend(DATtype &, unsigned int, FitType);

		/*************************************************
		* FUNCTION
		*	dealloc
		* PARAMETERS
		*	DATtype & - FAT
		* MEANING
		*	deallocates the file's sectors, freeing the space in the DAT.
		* SEE ALSO
		*	void howmuchempty()
		*	void alloc(DATtype &, unsigned int , unsigned int)
		*	void alloc(DATtype &, unsigned int , unsigned int , unsigned int)
		*	void allocextend(DATtype &, unsigned int, unsigned int)
		**************************************************/
		void dealloc(DATtype &);

		/*************************************************
		* FUNCTION
		*	createfile
		* PARAMETERS
		*	string & - Name of file
		*	string & - Name of file owner
		*	string & - file type:
		*		- file of [F]ixed length
		*		- file of [V]eriable length
		*	unsigned int - file length for length type "F", or file MAX length for legth type "V"
		*	unsigned int - Number of sectors to allocate
		*	string & - key datatype:
		*		- [I]nteger
		*		- [F]loat
		*		- [D]ouble
		*		- [C]haracter string
		*	unsigned int - key offset
		*	unsigned int - length of key, required for type "C" - default value:KEY_DEFAULT_LENGTH
		*	FitType - how to allocate space for the file - default value:firstFit
		* MEANING
		*	creates a new file, allocate sectors, and put in RootDir.
		* SEE ALSO
		*	void alloc(DATtype &, unsigned int , unsigned int)
		*	void delfile(string &, string &)
		*	void extendfile(string &, string &, unsigned int)
		**************************************************/
		void createfile (string &,  string &, string &, unsigned int, unsigned int, string &, unsigned int, unsigned int=KEY_DEFAULT_LENGTH, FitType=firstFit);

		/*************************************************
		* FUNCTION
		*	delfile
		* PARAMETERS
		*	string & - File name
		*	string & - Name of user trying to delete file
		* MEANING
		*	deletes the file and dealoc the the sectors.
		* SEE ALSO
		*	void dealloc(DATtype &)
		*	void extendfile(string &, string &, unsigned int)
		*	void createfile(string &, string &, string &, unsigned int, unsigned int, string &, unsigned int, unsigned int, FitType)
		**************************************************/
		void delfile(string &, string &);

		/*************************************************
		* FUNCTION
		*	extendfile
		* PARAMETERS
		*	string& - File name
		*	string& - Name of user trying to extend file
		*	unsigned int - Number of sectors to add
		* MEANING
		*	extend the file's number of available sectors
		* SEE ALSO
		*	void createfile(string &, string &, string &, unsigned int, unsigned int, string &, unsigned int, unsigned int, FitType)
		*	void delfile(string &, string &)
		*	void allocextend(DATtype &, unsigned int, unsigned int)
		**************************************************/
		void extendfile(string &, string &, unsigned int);

		/*************************************************
		* FUNCTION
		*	DiskMapping
		* PARAMETERS
		*	DATtype - File's DAT
		* RETURN VALUE
		*	an diskmap(defined map<int,int>) who contains pairs of indecies of first sectors of empty areas in the DAT and sizes of of said empty areas.
		* MEANING
		*	finds a list of all empty areas in the DAT, their start indecies and size.
		* SEE ALSO
		*	void alloc(DATtype &, unsigned int, FitType, unsigned int)
		**************************************************/
		diskmap* DiskMapping(const DATtype&);

		/*************************************************
		* FUNCTION
		*	openfile
		* PARAMETERS
		*	string& - File name
		*	string& - user opening file
		*	string& - type of opening:
		*		[I]nput,
		*		[O]utput,
		*		both [IO],
		*		[E]dition only.
		* RETURN VALUE
		*	pointer to FCB of file
		* MEANING
		*	opens a file and creates an FCB.
		* SEE ALSO
		*	FCB
		**************************************************/
		FCB* openfile(string &, string &, string &);
		/*************************************************
		* FUNCTION
		*	GetLastErrorMessage
		* MEANING
		*	Returns the error message 
		* RETURN VALUE
		*	returns the string.
		* SEE ALSO
		*
		**************************************************/
		string& GetLastErrorMessage();

		//	/*************************************************
		//* FUNCTION
		//*	getUseDisk
		//* MEANING
		//*	returns int
		//* RETURN VALUE
		//*	Returns the actual use of the disk (multiple sectors occupied).
		//* SEE ALSO
		//*
		//**************************************************/
		//int getUseDisk();

		/*************************************************
		* FUNCTION
		*	SetLastErrorMessage
		* PARAMETERS
		*	string & - Error message
		* MEANING
		*	Saves the error messages
		*
		**************************************************/
		void Disk::SetLastErrorMessage(string lastErrorMessage);

		
		/*************************************************
		* FUNCTION
		*	getVolumeHeader
		* MEANING
		*	returns vhd
		* RETURN VALUE
		*	returns the vhd.
		* SEE ALSO
		*
		**************************************************/
		 VolumeHeader getVolumeHeader();

		/*************************************************
		* FUNCTION
		*	getDAT
		* MEANING
		*	returns DAT
		* RETURN VALUE
		*	returns the DAT.
		* SEE ALSO
		*
		**************************************************/
		 Dat getDAT();

		 /*************************************************
		* FUNCTION
		*	getDirEntry
		* PARAMETERS
		* int - index of dirEntry
		* MEANING
		*	Returns  dirEntry by index
		* RETURN VALUE
		*	returns the dirEntry.
		* SEE ALSO
		*
		**************************************************/

		 DirEntry  getDirEntry(unsigned int);

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
		*	resetSector
		* MEANING
		*	writes reset all Sectors
		* SEE ALSO
		*	createdisk(string&)
		*	unmountdisk()
		*	savechanges()
		**************************************************/
		void resetSector();

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
		*	resetDat	
		* MEANING
		*	Reset the initial values ​​DAT	
		* SEE ALSO
		*	void createdisk(string &)
		*	void format(string &)
		**************************************************/
		void resetDat();

		/*************************************************
		* FUNCTION
		*	alloc
		* PARAMETERS
		*	DATtype& - FAT
		*	unsigned int - number of sectors to allocate
		*	FitType - allgoritem type:
		*		0 - first fit
		*		1 - best fit
		*		2 - worst fit
		*	usigned int - sector to begin allocating from
		* MEANING
		*	subfuction of void alloc(DATtype &, unsigned int , unsigned int) and void allocextend(DATtype &, unsigned int, unsigned int)
		* SEE ALSO
		*	void howmuchempty()
		*	void alloc(DATtype &, unsigned int , unsigned int)
		*	void allocextend(DATtype &, unsigned int, unsigned int)
		*	void dealloc(DATtype &)
		**************************************************/
		void alloc(DATtype &, unsigned int, FitType, unsigned int);

		/*************************************************
		* FUNCTION
		*	saveFileChanges
		* PARAMETERS
		*	unsigned int - sector number to save
		*	FileHeader & - file header sector data to save
		* MEANING
		*	updates a fileheader and commits changes
		* SEE ALSO
		*	
		**************************************************/
		void saveFileChanges(unsigned int  , FileHeader &);
	};