#include "FCB.h"


FCB::FCB()
{
	d=NULL;
	fileDesc=DirEntry();
	FAT = DATtype(0);
	Buffer = Sector();
	currRecNr=0;
	currSecNr=0;
	currRecNrInBuff=0;
	lock =false;
	changeBuf = false;
	changeDir = false;
}

FCB::FCB(Disk * disk)
{
	d=disk;
	fileDesc=DirEntry();
	FAT = DATtype(0);
	Buffer = Sector();
	currRecNr=0;
	currSecNr=0;
	currRecNrInBuff=0;
	lock =false;
	changeBuf = false;
	changeDir = false;
}


FCB::~FCB(void)
{
	delete this;
}

void FCB::closefile()
{
	if (iostate!=I)
	{
		try
		{
			flushfile();
			if (changeDir&&changeBuf)
			{
				*(d->rootdir[placeDir])=fileDesc;
				FileHeader fh;
				fh.FAT=FAT;
				fh.fileDesc=fileDesc;
				fh.sectorNr=fileDesc.fileAddr;
				d->writeSector(fileDesc.fileAddr, (Sector*)&fh);
			}
			lock =false;
			changeBuf = false;
			changeDir = false;
			d=NULL;

		}
		catch (exception ex)
		{
			throw exception(ex);
		}
	}
}

void FCB::flushfile()
{
	try
	{
		if (changeBuf && iostate!=I)
			d->writeSector(Buffer.sectorNr,&Buffer);
	}
	catch (exception ex)
	{
		throw exception(ex);
	}
}

void FCB::readRec(char * data, unsigned int updateFlag)
{
	if (iostate == O)
		throw exception("ERROR: The file open to read-only (at void FCB::readRec(char * , unsigned int )");

	memcpy(data,&Buffer+(currRecNrInBuff*fileDesc.actualRecSize)+4,fileDesc.actualRecSize);

	if (updateFlag==0 && currRecNr <= fileDesc.eofRecNr)
		seekRec(1,1);
	else if (updateFlag==1)
		lock=true;
}

void FCB::seekRec(unsigned int startingPoint, int num)
{
	switch (startingPoint)
	{
	case 0:	
		break;

	case 1:
		if ( fileDesc.recFormat == "v" )
			throw exception ("You can not jump to the middle of the file,in records with varying size. (at void FCB::seekRec(unsigned int , int )");
		num += currRecNr;
		break;

	case 2:
		num += fileDesc.eofRecNr;;		
		break;

	default:
		throw exception ("Starting point is invalid. (at void FCB::seekRec(unsigned int , int )");
		break;
	}

	if (num < 0 && num > fileDesc.eofRecNr )
		throw exception ("The address is not valid. (at void FCB::seekRec(unsigned int , int )");

	if (num/1024 != currSecNr)
		readNewSectorToBuffer(num/1024);
	currRecNr = num;
	currRecNrInBuff = num%1024;
}

void FCB::readNewSectorToBuffer(unsigned int numSector)
{
	if ( numSector >= 0 && numSector < fileDesc.fileSize )
	{
		flushfile();
		d->readSector(fileDesc.fileAddr+numSector,&Buffer);
		currRecNrInBuff = 0;
		currSecNr = numSector;
		changeBuf = false;
	}
	else
		throw exception("ERROR: There is not more sector (at void FCB::readNewSectorToBuffer()");
}

void FCB::updateCancel()
{
	if (iostate == I || iostate == O)
		throw exception("ERROR: can't update in I, O modes, so can't cancel an update (at void FCB::updateCancel())");

	if (lock == false)
		throw exception("ERROR: no update to cancel. (at void FCB::updateCancel())");

	lock = false;
}

void FCB::deleteRec()
{
	if (lock == false)
		throw exception("ERROR:need to lock record before deleting it. (at void FCB::deleteRec())");

	//delete by putting logical 0's at key.
	//for (int i = 4 + fileDesc.fileAddr + fileDesc.keyOffset; i < fileDesc.fileAddr + fileDesc.keyOffset + fileDesc.keySize; i++) ?
	for (int i = /* ? */; i < /* ? */; i++) 
	{
		Buffer.rawData[i] = 0;
	}

	lock = false;

	//move to next record.
	currRecNr++;
	currRecNrInBuff=(currRecNr%fileDesc.fileSize);
	currSecNr=(currRecNr/fileDesc.fileSize);
}

void FCB::updateRec(char * recPtr)
{
	if (iostate == I || iostate == O)
		throw exception("ERROR: can't update in I, O modes (at void FCB::updateRec(char *))");

	if (lock == false)
		throw exception("ERROR:need to lock record before updating it. (at void FCB::updateRec())");

	//update
	//?

	lock = false;

	//move to next record.
	currRecNr++;
	currRecNrInBuff=(currRecNr%fileDesc.fileSize);
	currSecNr=(currRecNr/fileDesc.fileSize);
}
