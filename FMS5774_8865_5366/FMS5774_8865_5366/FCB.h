#pragma once

#include "Disk.h"

using namespace std;

class Disk;

/*************************************************
* ENUM
*	IOState
* MEANING
*	represents the different ways to open a file logically.
* SEE ALSO
*   Disk::openfile(string&, string&, string&)
**************************************************/
enum IOState
{

	I, // Input
	O, // Output
	IO, // Input and Output
	E // Edition.


};

<<<<<<< HEAD
/*************************************************
* FUNCTION
*	conver
* PARAMETERS
*	const string & - string to convert
* RETURN VALUE
*	IOState convertion of input string
* MEANING
*	converts a string value into an IOState value
* SEE ALSO
*   IOState
**************************************************/
IOState conver(const string & io)
=======
IOState static conver(const string & io)
>>>>>>> 6346c173a022d0b781754206555647ca183bae20
{
	if (io=="I")
		return I;
	if (io=="O")
		return O;
	if (io=="IO")
		return IO;
	if (io=="E")
		return E;
	throw exception("ERROR: Bad I/O value");
};

/*************************************************
* CLASS
*	FCB
* MEANING
*	File Control Block to read/write a file logically.
* SEE ALSO
*	Disk
*	Sector
*	FileHeader
*	DirEntry
**************************************************/
class FCB
{
	
public:
	Disk * d; // disk file is on
	DirEntry fileDesc; // copy of file description from disk
	DATtype FAT; // copy of file FAT.
	Sector Buffer; // buffer sector.

	bool lock; // is the file ready for update action
	bool changeBuf; // has the buffer changed value from the value on disk
	bool changeDir; //  ?
	unsigned int placeDir; // ?
	unsigned int currRecNr;// Current record's serial number in file
	unsigned int currSecNr;// Current sector's serial number in file
	unsigned int currRecNrInBuff;//Current record's serial number in sector
	IOState iostate; // Input/Output state (see IOState)


	/*************************************************
	* FUNCTION
	*	ctor
	* MEANING
	*	constructs a file control block not atached to any disk
	* SEE ALSO
	*   FCB(Disk *)
	**************************************************/
	FCB();

	/*************************************************
	* FUNCTION
	*	ctor
	* PARAMETERS
	*	Disk * - disk to attach to the fcb
	* MEANING
	*	constructs a file control block and attaches it to a disk.
	* SEE ALSO
	*   FCB()
	**************************************************/
	FCB(Disk *);

	/*************************************************
	* FUNCTION
	*	dtor
	* MEANING
	*	deconstructs the fcb.
	* SEE ALSO
	*	FCB()
	*	FCB(Disk *)
	**************************************************/
	~FCB(void);

	/*************************************************
	* FUNCTION
	*	closefile
	* MEANING
	*	saves buffer data in the disk, updates file header and detaches the disk from the fcb.
	* SEE ALSO
	*	FCB(Disk *)
	*	flushfile()
	**************************************************/
	void closefile();

	/*************************************************
	* FUNCTION
	*	flushfile
	* MEANING
	*	saves buffer data unto the disk
	* SEE ALSO
	*
	**************************************************/
	void flushfile();
<<<<<<< HEAD
=======
	 void readRec(char *, unsigned int = 0);
	 void writeRec(char *);
	 void writeUpdateRec(char *);
	 void seekRec(unsigned int, int);
	 void deleteRec();
	 void updateRec(char *);
	 void readNewSectorToBuffer(unsigned int );
>>>>>>> 6346c173a022d0b781754206555647ca183bae20

	/*************************************************
	* FUNCTION
	*	readRec
	* PARAMETERS
	*	char * - pointer to where data is read
	*	unsigend int - opening option (default: 0)
	*		0 - read
	*		1 - read in order to update
	* MEANING
	*	reads next record, and locks record if second paremeter is 1.
	* SEE ALSO
	*	writeRec(char *)
	*	seekRec(unsigned int, int)
	*	deleteRec()
	*	updateRec(char *)
	**************************************************/
	void readRec(char *, unsigned int = 0);

	/*************************************************
	* FUNCTION
	*	writeRec
	* PARAMETERS
	*	char * - data to write
	* MEANING
	*	writes into the next record in the buffer
	* SEE ALSO
	*	readRec(char *, unsigend int=0)
	*	seekRec(unsigned int, int)
	*	deleteRec()
	*	updateRec(char *)
	**************************************************/
	void writeRec(char *);

	/*************************************************
	* FUNCTION
	*	seekRec
	* PARAMETERS
	*	unsigned int - type of movment:
	*		0 - seek from the start of the file
	*		1 - seek from corrent sector
	*		2 - from logical end of file
	*	int - amount of sectors to jump
	* MEANING
	*	move to a different record.
	* SEE ALSO
	*	readRec(char *, unsigend int=0)
	*	writeRec(char *)
	*	deleteRec()
	*	updateRec(char *)
	**************************************************/
	void seekRec(unsigned int, int);

	/*************************************************
	* FUNCTION
	*	deleteRec
	* MEANING
	*	delete corrent record by putting nullifing the key.
	* SEE ALSO
	*	readRec(char *, unsigend int=0)
	*	writeRec(char *)
	*	seekRec(unsigned int, int)
	*	updateRec(char *)
	**************************************************/
	void deleteRec();

	/*************************************************
	* FUNCTION
	*	updateeRec
	* PARAMETERS
	*	char * - data to update sector with
	* MEANING
	*	update sector by changing data.
	* SEE ALSO
	*	readRec(char *, unsigend int=0)
	*	writeRec(char *)
	*	seekRec(unsigned int, int)
	*	updateRec(char *)
	*	updateCancel()
	**************************************************/
	void updateRec(char *);

	/*************************************************
	* FUNCTION
	*	updateCancel
	* MEANING
	*	unlcoks record.
	* SEE ALSO
	*	updateRec(char *)
	*	updateCancel()
	**************************************************/
	void updateCancel();

	private:
	/*************************************************
	* FUNCTION
	*	readNewSectorToBuffer
	* PARAMETERS
	*	unsigned int - sector to read
	* MEANING
	*	saves buffer into current sector, and read new sector into the buffer.
	* SEE ALSO
	*	seekRec(unsigned int, int)
	**************************************************/
	void readNewSectorToBuffer(unsigned int );
};

