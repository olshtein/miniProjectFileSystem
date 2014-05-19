#pragma once

#include "BaseSector.h"

// represent key length for non string keys.
const unsigned int KEY_DEFAULT_LENGTH = 4;

/*************************************************
* ENUM
*	EntryStatus
* MEANING
*	represents the different statueses of a dirEntry.
* SEE ALSO
*   DirEntry
**************************************************/
enum EntryStatus
{
	empty,
	active,
	inactive
};

/*************************************************
* ENUM
*	RecordFormat
* MEANING
*	represents the different record formats of a dirEntry.
* SEE ALSO
*   DirEntry
**************************************************/
enum RecordFormat
{
	directory = 'D',
	fixed = 'F',
	veriable = 'V'
};

/*************************************************
* ENUM
*	KeyType
* MEANING
*	represents the different types of a dirEntry key.
* SEE ALSO
*   DirEntry
**************************************************/
enum KeyType
{
	Integer = 'I',
	Float = 'F',
	Double = 'D',
	CharString = 'C'
};

struct DirEntry
{
	unsigned int const NAME_STRING_SIZE = 12;
	unsigned int const DATE_STRING_SIZE = 10;  

	char Filename[NAME_STRING_SIZE]; //entry name
	char fileOwner[NAME_STRING_SIZE];  //entry owner name
	unsigned int fileAddr;  //address of the first sector in the entry
	char crDate[DATE_STRING_SIZE];  //creation date
	unsigned int fileSize;  //size of file
	unsigned int eofRecNr;  //location of the EOF(End of File) entry, relative to the start location of this entry
	unsigned int maxRecSize;  //entry max length
	unsigned int actualRecSize;  //actual entry length
	char recFormat [2];	/*	file type:
						*	file of [F]ixed length
						*	file of [V]eriable length
						*	[D]irectory					*/
	unsigned int keyOffset; //key offset in the entry
	unsigned int keySize;  //key lenght
	char keyType[2];	/*	key datatype:
						*	[I]nteger
						*	[F]loat
						*	[D]ouble
						*	[C]haracter string	*/

	unsigned char entryStatus;	/* the status of the entry
								*	0 - empty - not yet used since format.
								*	1 - active - entry in use.
								*	2 - inactive - entry was deleted		*/

	/*************************************************
	* FUNCTION
	*	contor
	* MEANING
	*	constracts the DirEntry with default values.
	**************************************************/
	DirEntry()
	{
		strcpy_s(Filename,1,"");
		strcpy_s(fileOwner,1,"");
		fileAddr = -1; // no first sector, so address in non existant.
		strcpy_s(crDate,11,"01/01/1970");
		fileSize = 0; 
		eofRecNr = 0; 
		maxRecSize = 0; 
		actualRecSize = 0;
		strcpy_s(recFormat,2,"F");
		keyOffset=0;
		keySize=KEY_DEFAULT_LENGTH;
		strcpy_s(keyType,2,"I");
		entryStatus = empty;
	}

};

