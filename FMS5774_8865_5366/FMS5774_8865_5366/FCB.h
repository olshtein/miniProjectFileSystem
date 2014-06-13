#pragma once

#include "Disk.h"
#include <string>

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

	I = 'I', // Input
	O = 'O', // Output
	IO = 0, // Input and Output
	E = 'E' // Edition.


};

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
IOState static converToIOEnum(const string & io)
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
string static converIOEnumToString(const IOState & io)
{
	if (io==I)
		return "I";
	if (io==O)
		return "O";
	if (io==IO)
		return "IO";
	if (io==E)
		return "E";
	throw exception("ERROR: Bad I/O value");
};

extern "C"
{

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
		bool changeDir; //  has the DirEntry changed value from the value on disk
		unsigned int placeDir; // plase DirEntry in rootdir
		unsigned int currRecNr;// Current record's serial number in file
		unsigned int currSecNr;// Current sector's serial number in file
		unsigned int currRecNrInBuff;//Current record's serial number in sector
		IOState iostate; // Input/Output state (see IOState)

		string lastErrorMessage;  

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
		*	updateRec
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
		/*************************************************
		* FUNCTION
		*	getFileDesctription
		* RETURN VALUE
		*	DirEntry
		* MEANING
		*	return  DirEntry to file
		**************************************************/
		DirEntry getFileDesctription();
		/*************************************************
		* FUNCTION
		*	IorO
		* RETURN VALUE
		*	IOState - the status of the iostate
		* MEANING
		*	return iostate after convert to string
		**************************************************/
		IOState IorO();
		/*************************************************
		* FUNCTION
		*	addMemory
		* PARAMETERS
		*	unsigned int - number of sectors needed
		* MEANING
		*	to done allocextend number of sectors needed
		* SEE ALSO
		*	disk::allocextend()
		**************************************************/
		void addMemory(unsigned int num); 
		/*************************************************
		* FUNCTION
		*	GetLastErrorMessage
		* RETURN VALUE
		*	string -error nessage.
		* MEANING
		*	Is designed to send messages in case of error
		* SEE ALSO
		*	 SetLastErrorMessage(string)
		**************************************************/
		string& GetLastErrorMessage();
		/*************************************************
		* FUNCTION
		*	 SetLastErrorMessage
		* PARAMETERS
		*	string - error nessage.
		* MEANING
		*	Is designed to keep messages in case of error
		* SEE ALSO
		*	GetLastErrorMessage()
		**************************************************/
		void SetLastErrorMessage(string lastErrorMessage);


	private:
		/*************************************************
		* FUNCTION
		*	isClose
		* RETURN VALUE	
		*	bool
		* MEANING
		*	is the FCB closed, i.e. not corolated to a disk.
		* SEE ALSO
		*
		**************************************************/
		bool isClose()
		{
			return d != NULL ?  true : throw exception("File closed! You can not access the file.");
		}

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

		/*************************************************
		* FUNCTION
		*	writeUpdateRec
		* PARAMETERS
		*	char * - data to update/write sector with
		* MEANING
		*	changes data in buffer in update/write processes. and seek to the next record.
		* SEE ALSO
		*	writeRec(char*)
		*	updateRec(char*)
		**************************************************/
		void writeUpdateRec(char *);

		/*************************************************
		* FUNCTION
		*	isKeyNull
		* RETURN VALUE
		*	bool
		* MEANING
		*	check if current record's key is all 0's
		* SEE ALSO
		*
		**************************************************/
		bool isKeyNull();
		/*************************************************
		* FUNCTION
		*	checkchanges
		* PARAMETERS
		*	unsigned int- num of sector in file
		* RETURN VALUE
		*	unsigned int -location sector in disk.
		* MEANING
		*	Looking for the location of the sector  in the disc with mapdisk
		* SEE ALSO
		*	disk::mapDisk()
		**************************************************/
		unsigned int locationSector(unsigned int);

	



	};

}