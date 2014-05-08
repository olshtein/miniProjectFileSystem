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
	if (iostate!=I && changeBuf)
	{
		try
		{
			flushfile();
			if (changeDir)
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
	d=NULL;
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
	try
	{
		isClose();
		if (iostate == O)
			throw exception("ERROR: The file open to read-only (at void FCB::readRec(char * , unsigned int )");

		if (lock == true && updateFlag == 1)
			throw exception("ERROR: You can not edit a record that is already being edited (at void FCB::readRec(char * , unsigned int )");

		memcpy(data,&(Buffer.rawData[ (currRecNrInBuff*fileDesc.actualRecSize)]),fileDesc.actualRecSize);

		if (updateFlag==0 && currRecNr <= fileDesc.eofRecNr)
			seekRec(1,1);
		else if (updateFlag==1)
			lock=true;
	}

	catch (exception ex)
	{
		throw exception(ex);
	}
}

void FCB::seekRec(unsigned int startingPoint, int num)
{
	try
	{
		isClose();
		if ( fileDesc.recFormat == "v" && (startingPoint == 1 || num != 0))
			throw exception ("ERROR: Jump is unavailable. (at void FCB::seekRec(unsigned int , int )");

		switch (startingPoint)
		{
		case 0:	
			break;

		case 1:
			num += currRecNr;
			break;

		case 2:
			num += fileDesc.eofRecNr;;		
			break;

		default:
			throw exception ("ERROR: Starting point is invalid. (at void FCB::seekRec(unsigned int , int )");
			break;
		}
		if ( iostate == E && num != fileDesc.eofRecNr+1)
			throw exception ("ERROR: Open the file for editing only, you can not move to the requested address. (at void FCB::seekRec(unsigned int , int )");

		if (num < 0 && num >= fileDesc.eofRecNr )
			throw exception ("The address is not valid. (at void FCB::seekRec(unsigned int , int )");

		if (num/1024 != currSecNr)
			readNewSectorToBuffer(num/1024);
		currRecNr = num;
		currRecNrInBuff = num%1024;
		lock=false;

	}
	catch (exception ex)
	{
		throw exception(ex);
	}
}

void FCB::readNewSectorToBuffer(unsigned int numSector)
{
	try
	{
		isClose();

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
	catch (exception ex)
	{
		throw exception(ex);
	}
}

void  FCB::writeUpdateRec(char * data)
{
	try
	{
		isClose();
		if (iostate ==I || (iostate == E && currRecNr != fileDesc.eofRecNr))
			throw exception ("No permission to write to address current. (at void FCB::readNewSectorToBuffer(unsigned int )");

		if (lock == false)
			throw exception("ERROR: need to lock record before read/update (at void FCB::readUpdateRec(char*))");

		memcpy(&(Buffer.rawData[(currRecNrInBuff*fileDesc.actualRecSize)]),data,fileDesc.actualRecSize);
		changeBuf = true;
		seekRec(1,1);
	}
	catch (exception ex)
	{
		throw exception(ex);
	}
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
	try 
	{
		if (lock == false)
			throw exception("ERROR:need to lock record before deleting it. (at void FCB::deleteRec())");

		//delete by putting logical 0's at key.
		unsigned int keyStart =  currRecNrInBuff * fileDesc.actualRecSize + 4 + fileDesc.keyOffset;
		for (int i = keyStart; i < keyStart + fileDesc.keySize; i++) 
		{
			Buffer.rawData[i] = 0;
		}

		lock = false;

		//move to next record.
		seekRec(1,1);
	}
	catch (exception ex)
	{
		throw exception(ex);
	}
}

void FCB::updateRec(char * recPtr)
{
	try
	{
		if (iostate == I || iostate == O)
			throw exception("ERROR: can't update in I, O modes (at void FCB::updateRec(char *))");

		if (lock == false)
			throw exception("ERROR:need to lock record before updating it. (at void FCB::updateRec())");

		//update
		writeUpdateRec(recPtr);

		lock = false;

		//move to next record.
		seekRec(1,1);
	}
	catch (exception ex)
	{
		throw exception(ex);
	}
}

void  FCB::writeRec(char * data)
{
	try
	{
		unsigned int keyStart =  currRecNrInBuff * fileDesc.actualRecSize + 4 + fileDesc.keyOffset;

		for (int i = keyStart; i < keyStart + fileDesc.keySize; i++) 
		{
			if (Buffer.rawData[i] != 0)
				throw exception("ERROR:can not write, another record is writen here. (at void  FCB::writeRec(char * data))");

		}
		writeUpdateRec(data);
	}
	catch (exception ex)
	{
		throw exception(ex);
	}
}