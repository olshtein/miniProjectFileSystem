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
		throw new logic_error("ERROR: this File name already exists (in Disk::createdisk(string&, string&))");
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
		throw  logic_error("ERROR: File does not open, fails to perform file creation (in Disk::savechanges())");

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
//��� 1

void Disk::format(string & nameOwner)
{
	if (this->getdskfl()->is_open()&&nameOwner==vhd.diskOwner)
	{
		resetDat();
		for (int i=0;i<(MAX_DIR_IN_SECTOR/2);i++)
		{
			rootdir.sector1.emptyArea[i]=NULL;
			rootdir.sector2.emptyArea[i]=NULL;
		}

	}
}

int  Disk::howmuchempty( )
{
	return dat.DAT.size()-dat.DAT.count();
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
				else
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
	if (howmuchempty()<numSector)
		throw  logic_error("ERROR:There is not enough free space  (in Disk::alloc(DATtype & , unsigned int , unsigned int )");
	fat.set(0);

	intmap * mapDisk = DiskMapping(dat.DAT);
	itmap it=mapDisk->begin();
	int locationSector=-1;
	switch (typeFit)
	{
	case 0://first fit 
		for (;it!= mapDisk->end(); ++it)
			if (it->second>=numSector)
			{
				locationSector=it->first;
				break;
			}
			break;
	case 1:// best fit 
		for (;it!= mapDisk->end(); ++it)
			if (it->second>=numSector&&it->second<locationSector)
			{
				locationSector=it->first;
			}
			break;
	case 2://worst fit
		for (;it!= mapDisk->end(); ++it)
			if (it->second>=numSector&&it->second>locationSector)
			{
				locationSector=it->first;
			}
			break;
	default:
		throw  logic_error("ERROR: the value of typeFit not suitable (in Disk::alloc(DATtype & , unsigned int , unsigned int )");
		break;
	}
	if (locationSector>=0)
	{
		for (int i=numSector;i>0;i--)
			fat.set(++locationSector,1);
	}
	else//����� �� ���� ������ ����
	{
		while (numSector>0)
		{
			it=mapDisk->begin();
			for (;it!= mapDisk->end(); ++it)
				if (mapDisk->find(locationSector)->first<=it->second)
					locationSector=it->second;
			int j=locationSector;
			for (int i=mapDisk->find(locationSector)->first ;i>0;i--)
				fat.set(j++,1);
			mapDisk->erase(locationSector);
		}
	}
	dat.DAT^=fat;

}

void Disk::allocextend(DATtype & fat, unsigned int numSector, unsigned int typeFit)
{
	if (howmuchempty()<numSector)
		throw  logic_error("ERROR:There is not enough free space  (in Disk::allocextend(DATtype & , unsigned int , unsigned int )");

	intmap * mapDisk = DiskMapping(dat.DAT);
	intmap * mapFaile =DiskMapping(fat);
	itmap it=mapDisk->find(mapFaile->end()->first+mapFaile->end()->second);	// ���� ������ �� ���� ������ ������
	int locationSector=-1;
	switch (typeFit)
	{
	case 0://first fit 
		for (;it!= mapDisk->end(); ++it)
			if (it->second>=numSector)
			{
				locationSector=it->first;
				break;
			}
			break;
	case 1:// best fit 
		for (;it!= mapDisk->end(); ++it)
			if (it->second>=numSector&&it->second<locationSector)
			{
				locationSector=it->first;
			}
			break;
	case 2://worst fit
		for (;it!= mapDisk->end(); ++it)
			if (it->second>=numSector&&it->second>locationSector)
			{
				locationSector=it->first;
			}
			break;
	default:
		throw  logic_error("ERROR: the value of typeFit not suitable (in Disk::alloc(DATtype & , unsigned int , unsigned int )");
		break;
	}
	if (locationSector>=0)
	{
		for (int i=numSector;i>0;i--)
		{
			fat.set(++locationSector,1);
			dat.DAT.set(++locationSector,0);
		}
	}
	else//����� �� ���� ������ ����
	{
		while (numSector>0)
		{
			it=mapDisk->find(mapFaile->end()->first+mapFaile->end()->second);
			for (;it!= mapDisk->end(); ++it)
				if (mapDisk->find(locationSector)->first<=it->second)
					locationSector=it->second;
			int j=locationSector;
			for (int i=mapDisk->find(locationSector)->first ;i>0;i--)
				fat.set(j++,1);
			mapDisk->erase(locationSector);
		}
	}

}
void Disk::dealloc(DATtype & fat)
{
	dat.DAT^=fat;
}
