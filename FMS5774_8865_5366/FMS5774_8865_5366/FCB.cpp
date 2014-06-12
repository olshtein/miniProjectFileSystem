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

FCB::~FCB()
{
}

DirEntry FCB::getFileDesctription()
{
	return fileDesc;
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
		//if (!isKeyNull())//בודק אם הרשומה לא ריקה צריך לבדוק רך ניתן לעשות את זה כי ברשומה חדשה לגמרי  היא לא תהיה שווה ל0
		//	throw exception("ERROR: There is no record at this location. (at void  FCB::readRec(char * , unsigned int ))");

		isClose();

		if (iostate == O)
			throw exception("ERROR: The file open to read-only (at void FCB::readRec(char * , unsigned int )");

		if (lock == true && updateFlag == 1)
			throw exception("ERROR: You can not edit a record that is already being edited (at void FCB::readRec(char * , unsigned int )");

		memcpy(data,&(Buffer.rawData[ (currRecNrInBuff*fileDesc.maxRecSize)]),fileDesc.maxRecSize);

		if (updateFlag==0 && currRecNr < fileDesc.eofRecNr)
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

		case 0:	//Start file
			break;

		case 1: //Current record
			num += currRecNr;
			break;

		case 2: //end file
			num += fileDesc.eofRecNr;;		
			break;

		default:
			throw exception ("ERROR: Starting point is invalid. (at void FCB::seekRec(unsigned int , int )");
			break;
		}
		if ( iostate == E && num != fileDesc.eofRecNr+1)//כתיבה במצב "הוספה" למקום לא מורשה
			throw exception ("ERROR: Open the file for editing only, you can not move to the requested address. (at void FCB::seekRec(unsigned int , int )");

		if (num < 0 || num > (fileDesc.fileSize-1)*(SIZE_DATA_IN_SECTOR/fileDesc.maxRecSize) )// כתיבה אל מחוץ לקובץ קדימה או אחורה
			throw exception ("ERROR: The address is not valid. (at void FCB::seekRec(unsigned int , int )");

		if (num > fileDesc.eofRecNr+1)//כתיבת רשומה תוך דילוג על מקום ריק
			throw exception ("ERROR: Unauthorized location. (at void FCB::seekRec(unsigned int , int )");

		int numSector = (num)/(SIZE_DATA_IN_SECTOR/fileDesc.maxRecSize)+1;//מיקום הסקטור הדרוש לרשימה

		cout<<num<<"  "<<numSector <<endl<< currSecNr<<endl;
		if (numSector != currSecNr)//אם יש צורך לעבור סקטור
			readNewSectorToBuffer(numSector);

		currRecNr = num;
		currRecNrInBuff = num%(SIZE_DATA_IN_SECTOR/fileDesc.maxRecSize);

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
			d->readSector(locationSector(numSector),&Buffer);
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

		memcpy(&(Buffer.rawData[(currRecNrInBuff*fileDesc.maxRecSize)]),data,fileDesc.maxRecSize);
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
		unsigned int keyStart =  currRecNrInBuff * fileDesc.maxRecSize  + fileDesc.keyOffset;

		for (int i = keyStart; i < keyStart + (fileDesc.keySize ? fileDesc.keySize : fileDesc.maxRecSize); i++) //כאשר ה .keySize מוגדר ל 0 יש צורך למחוק את כל הרשומה
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
		unsigned int keyStart =  currRecNrInBuff * fileDesc.maxRecSize + fileDesc.keyOffset;//המיקום של המפתח בכל רשומה

		if (isKeyNull())
				throw exception("ERROR:can not write, another record is writen here. (at void  FCB::writeRec(char * data))");
		writeUpdateRec(data);

		if ( currRecNr== fileDesc.eofRecNr+1)//אם הוספנו רשומה חדשה בסוף הרשומות
		{
			fileDesc.eofRecNr++;
			changeDir=true;
		}

	}
	catch (exception ex)
	{
		throw exception(ex);
	}
}

bool FCB::isKeyNull()
{
	unsigned int keyStart =  currRecNrInBuff * fileDesc.maxRecSize  + fileDesc.keyOffset;
	
	for (int i = keyStart; i < keyStart + (fileDesc.keySize ? fileDesc.keySize : fileDesc.maxRecSize); i++) 
		if (Buffer.rawData[i] != 0)
			return false;
	return true;
}

unsigned int  FCB::locationSector(unsigned int num)
{
	diskmap *mymap = d->DiskMapping(FAT);
	int sum = 0;
	for (it_diskmap it= mymap->begin(); it!=mymap->end(); ++it)
	{
		sum += it->second;
		if (sum*2>num)
		{
			int location= it->first*2+num-(sum - it->second-1);
			delete mymap;
			return location;
		}
	}
	throw exception("ERROR: Unusual surface data on file. (at  unsigned int  FCB::locationSector(unsigned int )");
}

void FCB::addMemory(unsigned int num)
{
	try
	{
	d->allocextend(FAT,num,firstFit);
	fileDesc.fileSize+=num;
	changeDir = true;
	}
	catch (exception ex)
	{
		throw exception(ex);
	}
}

string FCB::IorO()
		{
			return converIOEnumToString(iostate);
		}

// Stage 4-5

// Stage 4-5

string& FCB::GetLastErrorMessage() 
{ 
 return this->lastErrorMessage; 
} 
 
void FCB::SetLastErrorMessage(string lastErrorMessage) 
{ 
 this->lastErrorMessage = lastErrorMessage; 
} 