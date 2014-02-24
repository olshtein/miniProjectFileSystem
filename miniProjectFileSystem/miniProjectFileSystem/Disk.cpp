#include "Disk.h"


Disk::Disk(void)
{
	createdisk(string(""),string(""));
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
	dskfl.open(nameFile+".disk",ios::out  | ios::_Nocreate);
	if (dskfl.is_open())
	{	
		dskfl.close();
		throw new exception("ERROR: this File name already exists (in Disk::createdisk(string&, string&))");
	}
	dskfl.open(nameFile+".disk",ios::out  | ios::binary);
	vhd.sectorNr=0;
	strncpy_s(vhd.diskName, nameFile.c_str(), sizeof(vhd.diskName));
	vhd.diskName[sizeof(vhd.diskName) - 1] = NULL;  //�� ����� ����� ������ ���� null?
	createdisk(nameOwner);
	dskfl.close();

}

void Disk::createdisk( string & nameOwner)
{
	//vhd
	strncpy_s(vhd.diskOwner, nameOwner.c_str(), sizeof(vhd.diskOwner));
	vhd.diskOwner[sizeof(vhd.diskOwner) - 1] = NULL;  //�� ����� ����� ������ ���� null?
	Functions::dateNow(vhd.prodDate);
	vhd.intClusQty=1600;
	vhd.dataClusQty=1596;//1600-2*(vh(0.5)+dat(0.5)+rootdir(1))=1596
	vhd.addrDAT=1; //������� ������ ������ ����
	vhd.addrDATcpy=3199;//������ ������ ������ ����
	vhd.addrRootDir=2;
	vhd.addrRootDirCpy=3196;//������� ������ ������ ������ ��� ���� ������
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
	dat.DAT.set(2,0);
	dat.DAT.set(3199,0);
	dat.DAT.set(3198,0);
	dat.DAT.set(3197,0);
	dat.DAT.set(3196,0);

	//disk fstream
	
		if(dskfl.is_open() )  //����� ����� �� �� �����
		{
			dskfl.seekg(0);
			dskfl.write((char *)(&vhd),sizeof(Sector));
			dskfl.write((char *)(&dat),sizeof(Sector));
			dskfl.write((char *)(&rootdir),2*sizeof(Sector));
			for (int i=vhd.addrDataStart;i<vhd.addrRootDirCpy;i++) // ��� ������ �����
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
			throw new exception("ERROR: File does not open, fails to perform file creation (in Disk::createdisk(string&, string&))");

		}
}
void Disk::mountdisk(string & nameFile)
{

}
void Disk::unmountdisk( ){}
void Disk::recreatedisk(string & nameOwner)
{	
	if (dskfl.is_open())
	{
		if (vhd.diskOwner==nameOwner)
		{
			if(mounted==false)
				createdisk(nameOwner);
			else
				throw new exception("ERROR: the Disk is not available (in Disk::recreatedisk(string &))");
		}
		else
			throw new exception("ERROR: nameOwner does not match (in Disk::recreatedisk(string &))");
	}
	else
				throw new exception("ERROR: the File name is not open (in Disk::recreatedisk(string &))");
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
		currDiskSectorNr=numOfSector;
	}
	else
		throw string("ERROR File does not open (seekToSector(unsigned int) error)");
}
void Disk::writeSector(unsigned int numOfSector, Sector* toWrite)
{
	seekToSector(numOfSector);
	dskfl.write(reinterpret_cast< const char * >(&toWrite),sizeof(Sector));
	currDiskSectorNr++;
}
void Disk::writeSector(Sector* toWrite)
{
	if(dskfl.is_open() ) 
	{
		dskfl.write(reinterpret_cast< const char * >(&toWrite),sizeof(Sector));
			currDiskSectorNr++;
	}
	else
		throw string("ERROR: File does not open (writeSector(Sector*) error)");
}
void Disk::readSector(int, Sector*){}
void Disk::readSector(Sector*){}




Disk::~Disk(void)
{
}
