#pragma once
#include <iostream>
#include <string>
#include "Disk.h"

using namespace std;


class TestLevel_0
{
	static void printStructSize() 
	{
		cout << "start" << endl;
		cout << "Size Of Sector -->" << sizeof(Sector) << endl;  
		cout << "Size Of VolumeHeader -->" << sizeof(VolumeHeader) << endl; 
		cout << "Size Of DAT -->" << sizeof(Dat) << endl;  
		cout << "Size Of DirEntry -->" << sizeof(DirEntry) << endl; 
		cout << "Size Of SectorDir -->" << sizeof(RD_Sector) << endl; 
		cout << "Size Of FileHeader -->" << sizeof(FileHeader) << endl;   
		cout << "Size Of RootDir -->" << sizeof(RootDirectory) << endl; 
	}

	static void printDiskInfo(Disk& d) 
	{
		VolumeHeader* vh = &(d.vhd); 
		cout << " disk name:        " << vh->diskName << endl; 
		cout << " Owner Name:       " << vh->diskOwner << endl; 
		cout << " prodDate:         " << vh->prodDate << endl; 
		cout << " formatDate:       " << vh->formatDate << endl;  
		cout << " isFormated:       " << vh->isFormated << endl;  
		cout << " addrDataStart:    " << vh->addrDataStart << endl;  
		cout << " ClusQty:          " << vh->intClusQty << endl; 
		cout << " dataClusQty:      " << vh->dataClusQty << endl;   
		cout << " addrDAT:          " << vh->addrDAT << endl;  
		cout << " addrRootDir:      " << vh->addrRootDir << endl;  
		cout << " addrDATcpy:       " << vh->addrDATcpy << endl;   
		cout << " addrRootDirCpy:   " << vh->addrRootDirCpy << endl << endl;
	}  

	static void test_create(string diskName, string ownerName)  
	{
		Disk d; 
		cout << "\npre createdisk: " << endl; 
		printDiskInfo(d); 
		cout << "post createdisk: " << endl; 
		d.createdisk(diskName, ownerName);
		printDiskInfo(d); 
	}

	static void test_mount(string diskName)  
	{
		Disk d;  
		cout << "\npre mountdisk: " << endl;  
		printDiskInfo(d);   
		d.mountdisk(diskName); 
		cout << "post mountdisk: " << endl;  
		printDiskInfo(d);   d.unmountdisk(); 
	}   

	static void test_rwSector(string diskName) 
	{   
		Disk d;  
		Sector sector;   
		d.mountdisk(diskName);    
		cout << "\nread sector: " << endl;   
		d.readSector(8, &sector);  
		strcpy_s(sector.rawData, "this is write temp sector"); 
		d.writeSector(8, &sector); 
		d.unmountdisk();  
	}
	static void test_read_write(string diskName, string ownerName)
	{
		cout<<"pres to test read and write"<<endl<<endl;
		system("pause");
		Disk newMyDisk(diskName,ownerName,'c');
		Disk newMyDisk1(diskName,ownerName,'m');
		newMyDisk.seekToSector(0);
		newMyDisk1.seekToSector(0);

		for (int i=0;i<3200;i++)
		{
			Sector my;
			Sector my2;
			newMyDisk.readSector(i,&my);
			newMyDisk1.readSector(&my2);
			cout<<"num of sector newMyDisk:"<<my.sectorNr<<" newMyDisk1: "<<my2.sectorNr<<endl;
		}

		newMyDisk.unmountdisk();
		newMyDisk1.unmountdisk();
		system("pause");
	}
public: 

	static void test_0() 
	{ 
		try  
		{    
			string diskName = "disk 1";  
			string ownerName = "meir";  
			printStructSize();  
			test_create(diskName, ownerName); 
			test_mount(diskName); 
			diskName = "disk 2";
			test_read_write(diskName, ownerName);

		}   
		catch (exception ex) 
		{    cout << ex.what() << endl;   } 
	}
}; 
