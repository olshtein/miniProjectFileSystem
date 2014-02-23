#include "Disk.h"
#include <time.h>

Disk::Disk(void)
{

}
Disk::Disk (string & nameFile, string & nameOwner, char createOrMountDisk)
{
	if (createOrMountDisk=='c')
		createdisk(nameFile,nameOwner);
	else if (createOrMountDisk=='m')
			mountdisk (nameFile);
	else
		throw new exception("ERROR: Improper initialization command (in Disk::Disk(string, string, char))");

}

void Disk::createdisk(string & nameFile, string & nameOwner)
{
	//vhd
	vhd.sectorNr=0;
	strncpy(vhd.diskName, nameFile.c_str(), sizeof(vhd.diskName));
	vhd.diskName[sizeof(vhd.diskName) - 1] = NULL;  //אם אנחנו רוצים שאחרון יהיה null?
	strncpy(vhd.diskOwner, nameOwner.c_str(), sizeof(vhd.diskOwner));
	vhd.diskOwner[sizeof(vhd.diskOwner) - 1] = NULL;  //אם אנחנו רוצים שאחרון יהיה null?
	dateNow(vhd.prodDate);
	vhd.intClusQty=1600;
	vhd.dataClusQty=1596;//1600-2*(vh(0.5)+dat(0.5)+rootdir(1))=1596
	vhd.addrDAT=1; //הקלאסטר הראשון הסקטור השני
	vhd.addrDATcpy=3199;//הקלסטר האחרון הסקטור השני
	vhd.addrRootDir=2;
	vhd.addrRootDirCpy=3196;//הקלאסטר שמתחיל במיקום הסקטור אחד לפני האחרון
	vhd.addrDataStart=4;
	vhd.isFormated=false;

	//rootdir
	rootdir.sectorNr_1=2;
	rootdir.sectorNr_2=3;

	//dat
	dat.sectorNr=1;
	dat.DAT.set();
	dat.DAT.set(0,0);
	dat.DAT.set(1,0);
	dat.DAT.set(2,0);
	dat.DAT.set(3199,0);
	dat.DAT.set(3198,0);
	dat.DAT.set(3197,0);
	dat.DAT.set(3196,0);

	//disk fstream
	dskfl.open(nameFile+".disk",ios::out  | ios::binary);

	if(dskfl.is_open() )  //כתיבה לקובץ של כל הדיסק
	{
		dskfl.seekg(0);
		dskfl.write(reinterpret_cast< const char * >(&vhd),sizeof(Sector));
		dskfl.write(reinterpret_cast< const char * >(&dat),sizeof(Sector));//האים צריך בכל פעם להקפיץ את המצביע?? 
		dskfl.write(reinterpret_cast< const char * >(&rootdir),2*sizeof(Sector));
		for (int i=vhd.addrDataStart;i<vhd.addrRootDirCpy;i++) // לכל סקטורי המידע
		{
			Sector my;
			my.sectorNr=i;
			dskfl.write(reinterpret_cast< const char * >(&my),2*sizeof(Sector));
		}

		// update rootdir, vhd, dat sectorNr to fit, copies sector numbers.

		dskfl.write(reinterpret_cast< const char * >(&rootdir),2*sizeof(Sector));
		dskfl.write(reinterpret_cast< const char * >(&vhd),sizeof(Sector));
		dskfl.write(reinterpret_cast< const char * >(&dat),sizeof(Sector));

		dskfl.close();
	}
	else
	{
		throw new exception("ERROR: File does not open, fails to perform file creation (in Disk::createdisk(string&, string&))");

	}


}
void Disk::mountdisk(string & nameFile)
{

}
void Disk::unmountdisk( ){}
void Disk::recreatedisk(string &){}

fstream* const Disk::getdskfl()
{
	dskfl.open(*vhd.diskName+".disk", ios::in |ios::out  | ios::binary);

	if(dskfl.is_open() ) 
		return &dskfl;
	return NULL;

}
void Disk::seekToSector(unsigned int numOfSector)
{
	if(dskfl.is_open() ) 
		dskfl.seekg(numOfSector*(sizeof(Sector)));
	throw string("ERROR File does not open (seekToSector error)");
}
void Disk::writeSector(unsigned int, Sector*)
{

}
void Disk::writeSector(Sector*){}
void Disk::readSector(int, Sector*){}
void Disk::readSector(Sector*){}

void Disk::dateNow(char* date)//שומר את התאריך הנוכחי
{
	time_t t = time(0); 
	tm* lt = localtime(&t);
	sprintf(date, "%02d/%02d/%04d/0", lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
}


Disk::~Disk(void)
{
}
