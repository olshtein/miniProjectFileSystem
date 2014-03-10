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
		throw new logic_error("ERROR: Improper initialization command (in Disk::Disk(string, string, char))");

}

Disk::~Disk(void)
{
}

void Disk::createdisk(string & nameFile, string & nameOwner)
{
	//vhd
	dskfl.open(nameFile+".disk",ios::out  | ios::_Nocreate);
	if (dskfl.is_open())
	{	
		dskfl.close();
		throw new logic_error("ERROR: this File name already exists (in Disk::createdisk(string&, string&))");
	}
		if (nameFile!="")
		{
	dskfl.open(nameFile+".disk",ios::out  | ios::binary);
	vhd.sectorNr=0;
	strncpy_s(vhd.diskName, nameFile.c_str(), sizeof(vhd.diskName));
	vhd.diskName[sizeof(vhd.diskName) - 1] = NULL;  //אם אנחנו רוצים שאחרון יהיה null?
	mounted=false;
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
	dat.DAT.set();
	dat.DAT.set(0,0);
	dat.DAT.set(1,0);
	dat.DAT.set(1598,0);
	dat.DAT.set(1599,0);

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

		for (int i=vhd.addrDataStart;i<vhd.addrRootDirCpy;i++) // for all data sectors
		{
			Sector my;
			my.sectorNr=i;
			dskfl.read((char*)(&my),sizeof(Sector));
		}
	}
	else
		throw logic_error("ERROR: file does not exist in path: (in Disk::mountdisk(string&))");
		//throw logic_error("ERROR: file does not exist in path:" + nameFile.c_str + ".disk (in Disk::mountdisk(string&))");
}

void Disk::unmountdisk()
{
	if (!dskfl.is_open())
		throw logic_error("ERROR: disk not mounted, cannot unmount. (in Disk::unmountdisk())");

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
				throw  logic_error("ERROR: the Disk is not available (in Disk::recreatedisk(string &))");
		}
		else
			throw  logic_error("ERROR: nameOwner does not match (in Disk::recreatedisk(string &))");
	}
	else
		throw  logic_error("ERROR: the File name is not open (in Disk::recreatedisk(string &))");
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
		throw logic_error("ERROR: File does not open (in Disk::seekToSector(unsigned int))");
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
		throw logic_error("ERROR: File does not open (in Disk::writeSector(Sector*))");
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
		throw logic_error("ERROR: File does not open (in Disk::readSector(Sector*))");
}

void Disk::savechanges()
{
	if(dskfl.is_open() )  //כתיבה לקובץ של כל הדיסק
	{
		dskfl.seekg(0);
		dskfl.write((char *)(&vhd),sizeof(Sector));
		dskfl.write((char *)(&dat),sizeof(Sector));
		dskfl.write((char *)(&rootdir),2*sizeof(Sector));
		for (int i=vhd.addrDataStart;i<vhd.addrRootDirCpy;i++) // לכל סקטורי המידע
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
		throw  logic_error("ERROR: File does not open, fails to perform file creation (in Disk::savechanges())");

	}
}
