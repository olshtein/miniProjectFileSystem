#include "Disk.h"


Disk::Disk(void)
{
	createdisk(string(""),string(""));
}

Disk::Disk (string & nameFile, string & nameOwner, char createOrMountDisk)
{
	if (createOrMountDisk=='c')
	{
		createdisk(nameFile,nameOwner);
		mountdisk (nameFile);
	}
	else if (createOrMountDisk=='m')
		mountdisk (nameFile);
	else
		throw exception("ERROR: Improper initialization command (in Disk::Disk(string, string, char))");

}

Disk::~Disk(void)
{
	if (dskfl.is_open())
		unmountdisk();
}

void Disk::createdisk(string & nameFile, string & nameOwner)
{
	//vhd
	dskfl.open(nameFile+".disk",ios::out  | ios::_Nocreate);
	if (dskfl.is_open())
	{	
		dskfl.close();
		throw exception("ERROR: this File name already exists (in Disk::createdisk(string&, string&))");
	}

	mounted=false;

	if (nameFile!="")
	{
		dskfl.open(nameFile+".disk",ios::out  | ios::binary);
		vhd.sectorNr=0;
		strncpy_s(vhd.diskName, nameFile.c_str(), sizeof(vhd.diskName));
		vhd.diskName[sizeof(vhd.diskName) - 1] = NULL; 
		createdisk(nameOwner);
		dskfl.close();
	}

}

void Disk::createdisk( string & nameOwner)
{
	//vhd
	strncpy_s(vhd.diskOwner, nameOwner.c_str(), sizeof(vhd.diskOwner));
	vhd.diskOwner[sizeof(vhd.diskOwner) - 1] = NULL;  //אם אנחנו רוצים שאחרון יהיה null?
	Functions::dateNow(vhd.prodDate);
	vhd.intClusQty=1600;
	vhd.dataClusQty=1596;//1600-2*(vh(0.5)+dat(0.5)+rootdir(1))=1596
	vhd.addrDAT=1; //הקלאסטר הראשון הסקטור השני
	vhd.addrDATcpy=3199;//הקלסטר האחרון הסקטור השני
	vhd.addrRootDir=2;
	vhd.addrRootDirCpy=3196;//הקלאסטר שמתחיל במיקום הסקטור אחד לפני האחרון
	vhd.addrDataStart=4;
	vhd.isFormated=false;

	//rootdir
	rootdir.sector1.sectorNr=2;
	rootdir.sector2.sectorNr=3;

	//dat
	dat.sectorNr=1;
	resetDat();

	//disk fstream
	savechanges();

}

void Disk::mountdisk(string & nameFile)
{
	dskfl.open(nameFile + ".disk", ios::in | ios::out | ios::binary);

	if (dskfl.is_open())
	{
		mounted=true;

		dskfl.seekg(0);
		dskfl.read((char*)(&vhd), sizeof(Sector));
		dskfl.read((char*)(&dat), sizeof(Sector));
		dskfl.read((char*)(&rootdir), 2*sizeof(Sector));

		for (unsigned int i=vhd.addrDataStart; i < vhd.addrRootDirCpy; i++) // for all data sectors
		{
			Sector my;
			my.sectorNr=i;
			dskfl.read((char*)(&my),sizeof(Sector));
		}
	}
	else
		throw exception("ERROR: file does not exist in path: (in Disk::mountdisk(string&))");
	//throw exception("ERROR: file does not exist in path:" + nameFile.c_str + ".disk (in Disk::mountdisk(string&))");
}

void Disk::unmountdisk()
{
	if (!dskfl.is_open())
		throw exception("ERROR: disk not mounted, cannot unmount. (in Disk::unmountdisk())");

	// step 1: update data fields.
	savechanges();

	// step 2: closing the disk.
	dskfl.close();

	// step 3: turn 'mounted' to false.
	mounted=false;
}

void Disk::recreatedisk(string & nameOwner)
{	
	if (dskfl.is_open())
	{
		if (vhd.diskOwner==nameOwner)
		{
			if(mounted==false)
				createdisk(nameOwner);
			else
				throw  exception("ERROR: the Disk is not available (in Disk::recreatedisk(string &))");
		}
		else
			throw  exception("ERROR: nameOwner does not match (in Disk::recreatedisk(string &))");
	}
	else
		throw  exception("ERROR: the File name is not open (in Disk::recreatedisk(string &))");
}

fstream* const Disk::getdskfl()
{
	//dskfl.open(*vhd.diskName+".disk", ios::in |ios::out  | ios::binary);

	if(dskfl.is_open() ) 
		return &dskfl;
	return NULL;

}

void Disk::seekToSector(unsigned int numOfSector)
{
	if(dskfl.is_open() ) 
	{
		dskfl.seekg(numOfSector*(sizeof(Sector)));
		dskfl.seekp(numOfSector*(sizeof(Sector)));
		currDiskSectorNr=numOfSector;
	}
	else
		throw exception("ERROR: File does not open (in Disk::seekToSector(unsigned int))");
}

void Disk::writeSector(unsigned int numOfSector, Sector* toWrite)
{
	seekToSector(numOfSector);
	dskfl.write((char*)(toWrite),sizeof(Sector));
	currDiskSectorNr++;
}

void Disk::writeSector(Sector* toWrite)
{
	if(dskfl.is_open() ) 
	{
		dskfl.write((char*)(toWrite),sizeof(Sector));
		currDiskSectorNr++;
	}
	else
		throw exception("ERROR: File does not open (in Disk::writeSector(Sector*))");
}

void Disk::readSector(int numOfSector, Sector* toRead)
{
	seekToSector(numOfSector);
	dskfl.read((char*)(toRead),sizeof(Sector));
	currDiskSectorNr++;
}

void Disk::readSector(Sector* toRead)
{
	if(dskfl.is_open() ) 
	{
		dskfl.read((char*)(toRead),sizeof(Sector));
		currDiskSectorNr++;
	}
	else
		throw exception("ERROR: File does not open (in Disk::readSector(Sector*))");
}

void Disk::savechanges()
{
	if(dskfl.is_open() )  //כתיבה לקובץ של כל הדיסק
	{
		dskfl.seekg(0);
		dskfl.write((char *)(&vhd),sizeof(Sector));
		dskfl.write((char *)(&dat),sizeof(Sector));
		dskfl.write((char *)(&rootdir),2*sizeof(Sector));
		for (unsigned int i=vhd.addrDataStart; i < vhd.addrRootDirCpy; i++) // לכל סקטורי המידע
		{
			Sector my;
			my.sectorNr=i;
			dskfl.write((char *)(&my),sizeof(Sector));
		}

		// update rootdir, vhd, dat sectorNr to fit, copies sector numbers.
		rootdir.sector1.sectorNr=3196;
		rootdir.sector2.sectorNr=3197;
		dskfl.write((char *)(&rootdir),2*sizeof(Sector));
		rootdir.sector1.sectorNr=2;
		rootdir.sector2.sectorNr=3;
		vhd.sectorNr=3198;
		dskfl.write((char *)(&vhd),sizeof(Sector));
		vhd.sectorNr=0;
		dat.sectorNr=3199;
		dskfl.write((char *)(&dat),sizeof(Sector));
		dat.sectorNr=1;
	}
	else
	{
		throw  exception("ERROR: File does not open, fails to perform file creation (in Disk::savechanges())");

	}
}

void Disk::resetDat()
{
	dat.DAT.set();
	dat.DAT.set(0,0);
	dat.DAT.set(1,0);
	dat.DAT.set(1598,0);
	dat.DAT.set(1599,0);
}
//שלב 1

void Disk::format(string & nameOwner)
{
	if (!this->getdskfl()->is_open() || nameOwner!=vhd.diskOwner)
	{
		throw exception("ERROR: unable to open file, or file owner does not match data in vhd (at Disk::format(string&))");
	}

	resetDat();

	for (int i=0; i < MAX_DIR_IN_SECTOR; i++)
		*rootdir[i] = DirEntry();

}

unsigned int  Disk::howmuchempty( )
{
	try 
	{
			return dat.DAT.size()-dat.DAT.count();
	}
	catch (...)
	{
		throw exception("ERROR: DAT count bigger then DAT size(in Disk::howmuchempty())");
	}
}

intmap* Disk::DiskMapping( DATtype& dat)
{

	intmap *mapDisk=new intmap;
	for (int i=0;i<1600;i++)
	{
		if (dat[i]==1)
		{
			int index=i;
			int size=0;
			while (true)
			{
				if (dat[i]==1)
				{
					i++;
					size++;
				}
				if (dat[i]!=1||i==1599)
				{
					mapDisk->insert(pair<int,int>(index,size));
					break;
				}
			}
		}
	}
	return mapDisk;
}

void Disk::alloc(DATtype & fat, unsigned int numSector, unsigned int typeFit)
{
	try
	{
		if (howmuchempty() < numSector)
			throw  exception("ERROR:There is not enough free space  (in Disk::alloc(DATtype & , unsigned int , unsigned int )");
	}
	catch(exception ex)
	{
		throw ex;
	}

	fat.set(1);

	intmap * mapDisk = DiskMapping(dat.DAT);
	it_intmap it=mapDisk->begin();
	int locationSector=-1;
	switch (typeFit)
	{
	case firstFit://first fit 
		for (;it!= mapDisk->end(); ++it)
			if (it->second >= numSector)
			{
				locationSector=it->first;
				break;
			} 
			break;
	case bestFit:// best fit 
		for (;it!= mapDisk->end(); ++it)
			if (it->second >= numSector && locationSector == -1 || it->second < (*mapDisk)[locationSector]) 
			{
				locationSector=it->first;
			}
			break;
	case worstFit://worst fit
		for (;it!= mapDisk->end(); ++it)
			if (it->second >= numSector && locationSector == -1 || it->second < (*mapDisk)[locationSector])
			{
				locationSector=it->first;
			}
			break;
	default:
		throw  exception("ERROR: the value of typeFit not suitable (in Disk::alloc(DATtype & , unsigned int , unsigned int )");
		break;
	}
	if (locationSector>=0)
	{
		for (int i=numSector;i>0;i--)
			fat.set(locationSector++,0);
	}
	else//במקרה של צורך לפיצול קובץ
	{
		while (numSector>0)
		{
			it=mapDisk->begin();
			//Using in worst fit for minimal splitting
			for (;it!= mapDisk->end(); ++it)
				if ((*mapDisk)[locationSector]<=it->second)
					locationSector=it->second;
			int j=locationSector;
			for (int i=mapDisk->find(locationSector)->first ;i>0;i--)
				fat.set(j++,1);
			mapDisk->erase(locationSector);
		}
	}
	dat.DAT^=fat;
	delete mapDisk;
}

void Disk::allocextend(DATtype & fat, unsigned int numSector, unsigned int typeFit)
{
	try
	{
		if (howmuchempty() < numSector)
			throw  exception("ERROR:There is not enough free space  (in Disk::allocextend(DATtype & , unsigned int , unsigned int )");
	}
	catch(exception ex)
	{
		throw ex;
	}

	intmap * mapDisk = DiskMapping(dat.DAT);
	intmap * mapFile =DiskMapping(fat);
	it_intmap it=mapDisk->find(mapFile->end()->first+mapFile->end()->second);	// Should begin only after the current position
	int locationSector=-1;
	switch (typeFit)
	{
	case firstFit://first fit 
		for (;it!= mapDisk->end(); ++it)
			if (it->second >= numSector)
			{
				locationSector=it->first;
				break;
			}
			break;
	case bestFit:// best fit 
		for (;it!= mapDisk->end(); ++it)
			if (it->second >= numSector && locationSector==-1 || it->second < (*mapDisk)[locationSector])
			{
				locationSector=it->first;
			}
			break;
	case worstFit://worst fit
		for (;it!= mapDisk->end(); ++it)
			if (it->second >= numSector && it->second < (*mapDisk)[locationSector])
			{
				locationSector=it->first;
			}
			break;
	default:
		throw  exception("ERROR: the value of typeFit not suitable (in Disk::alloc(DATtype & , unsigned int , unsigned int )");
		break;
	}
	if (locationSector>=0)
	{
		for (int i=numSector;i>0;i--)
		{
			fat.set(locationSector++,1);
			dat.DAT.set(locationSector++,0);
		}
	}
	else//במקרה של צורך לפיצול קובץ
	{
		//Using in worst fit for minimal splitting
		while (numSector>0)
		{
			it=mapDisk->find(mapFile->end()->first+mapFile->end()->second);
			for (;it!= mapDisk->end(); ++it)
				if (mapDisk->find(locationSector)->first<=it->second)
					locationSector=it->second;
			int j=locationSector;
			for (int i=mapDisk->find(locationSector)->first ;i>0;i--)
				fat.set(j++,1);
			mapDisk->erase(locationSector);
		}
	}

	delete mapDisk;
	delete mapFile;

}

void Disk::dealloc(DATtype & fat)
{
	dat.DAT^=fat;
}

//Stage 2



void Disk::createfile (string & fileName,  string & fileOwner, string & fileFormat, unsigned int entryLen, unsigned int requestedSectors, string & keyDT, unsigned int offset, unsigned int keyLen, FitType fitType)
{
	//check file name does not exist
	for (int i=0; i < MAX_DIR_IN_SECTOR*2 && rootdir[i]->entryStatus != 0; i++)
		if (rootdir[i]->Filename == fileName)
			throw exception("ERROR: file name already exists (at void Disk::createfile(string &,  string &, string &, unsigned int, unsigned int, string &, unsigned int, unsigned int))");

	// check key format
	if (keyDT != "I" || keyDT != "F" || keyDT != "D" || keyDT != "C")
		throw exception("ERROR: key format is unrecognized, please use I,F,D or C (at void Disk::createfile(string &,  string &, string &, unsigned int, unsigned int, string &, unsigned int, unsigned int))");
	
	//check key length for strings
	if ((keyDT == "C") && keyLen == KEY_DEFAULT_LENGTH)
		throw exception("ERROR: if key is a string or a char*, length of key must be specified. (at void Disk::createfile (string &,  string &, string &, unsigned int, unsigned int, string &, unsigned int, unsigned int=KEY_DEFAULT_LENGTH))");

	//search RootDir for space for entry
	int i;

	for (i=0; i < MAX_DIR_IN_SECTOR*2 && rootdir[i]->entryStatus != 0; i++) ;

	if (i == MAX_DIR_IN_SECTOR*2) // no empty slot was found
		throw exception("ERROR: can't add entry, rootDir is full. (at void Disk::createfile (string &,  string &, string &, unsigned int, unsigned int, string &, unsigned int, unsigned int=KEY_DEFAULT_LENGTH))");

	//create entry.
	strcpy_s(rootdir[i]->Filename, 12, fileName.c_str());
	strcpy_s(rootdir[i]->fileOwner, 12, fileOwner.c_str());
	strcpy_s(rootdir[i]->recFormat, 2, fileFormat.c_str());
	rootdir[i]->maxRecSize = entryLen;
	rootdir[i]->actualRecSize = fileFormat == "F"? entryLen : 0;
	rootdir[i]->fileSize = requestedSectors;
	strcpy_s(rootdir[i]->keyType, 2, keyDT.c_str());
	rootdir[i]->keyOffset = offset;
	rootdir[i]->keySize = keyLen;

	//create FileHeader
	FileHeader fh;
	fh.fileDesc = *rootdir[i];
	fh.FAT = DATtype(0);

	//allocate space for entry and save.
	try
	{
		alloc(fh.FAT, rootdir[i]->fileAddr, fitType);
		writeSector((Sector*)&fh);
	}
	catch (exception ex)
	{
		throw exception(ex);
	}

	//sign entry as entered
	rootdir[i]->entryStatus=1;
}

void Disk::delfile(string & fileName, string & fileOwner)
{
	//search file in rootdir
	for (int i=0; i < MAX_DIR_IN_SECTOR*2 && rootdir[i]->entryStatus != 0; i++)
	{
		if (rootdir[i]->Filename == fileName)
		{
			if (rootdir[i]->fileOwner != fileOwner)
				throw exception("ERROR: user not allowed to delete the file (at void Disk::delfile(string &, string &)");

			//retrive fileHeader
			FileHeader fh;
			try
			{
			readSector(rootdir[i]->fileAddr, (Sector*)&fh);
			}

			catch(exception ex)
			{
				throw exception(ex);
			}

			//delete file
			dealloc(fh.FAT);
			rootdir[i]->entryStatus = 2;

			//save
			try
			{
				writeSector(rootdir[i]->fileAddr, (Sector*)&fh);
			}
			catch (exception ex)
			{
				throw exception(ex);
			}

			return;
		}
	}

	//file not found
	throw exception("ERROR: file not found (at void Disk::delfile(string &, string &)");
}

void Disk::extendfile(string & fileName, string & fileOwner, unsigned int addedSectors)
{
		//search file in rootdir
	for (int i=0; i < MAX_DIR_IN_SECTOR*2 && rootdir[i]->entryStatus != 0; i++)
	{
		if (rootdir[i]->Filename == fileName)
		{
			if (rootdir[i]->fileOwner != fileOwner)
				throw exception("ERROR: user not allowed to delete the file (at void Disk::extendfile(string &, string &, unsigned int)");

			FileHeader fh;
			try
			{
				//retrive fileHeader
				readSector(rootdir[i]->fileAddr, (Sector*)&fh);
				
				//extend allocation for file
				allocextend(fh.FAT, addedSectors, firstFit);

				//save
				writeSector(rootdir[i]->fileAddr, (Sector*)&fh);
			}

			catch(exception ex)
			{
				throw exception(ex);
			}



		}
	}

	//file not found
	throw exception("ERROR: file not found (at void Disk::extendfile(string &, string &, unsigned int)");
}