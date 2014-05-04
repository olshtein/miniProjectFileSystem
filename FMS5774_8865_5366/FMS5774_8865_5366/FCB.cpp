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