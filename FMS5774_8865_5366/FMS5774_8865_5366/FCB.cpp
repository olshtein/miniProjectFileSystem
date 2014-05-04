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
	memcpy(data,&Buffer,fileDesc.actualRecSize);
	if (updateFlag==0 && currRecNr <= fileDesc.eofRecNr)
	{
		currRecNr++;
		if (1020/fileDesc.actualRecSize <=currRecNrInBuff)
		currRecNrInBuff++;

	}


}
void FCB::readNewSectorToBuffer()
{
	if(fileDesc.fileSize<=1+currSecNr)
		throw exception("ERROR: There is not more sector (at void FCB::readNewSectorToBuffer()");

}
