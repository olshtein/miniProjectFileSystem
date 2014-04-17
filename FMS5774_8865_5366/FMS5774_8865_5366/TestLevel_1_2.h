#pragma once
#include <iostream>
#include <string>
#include "Disk.h"
#include "TestLevel_0.h"

using namespace std;


class TestLevel_1_2
{
	static void create()
		{
			string diskName = "disk 1_2";  
			string ownerName = "meir";  
			string fileName1 = "newFile1";
			string fileName2 = "newFile2";
			string fileName3 = "newFile3";
			string fileName4 = "newFile4";


			string fileFormat="F";
			string  keyDT = "I";
			Disk d;
			d.createdisk(diskName, ownerName);
			d.mountdisk(diskName);
			d.createfile(fileName1,ownerName,fileFormat,128,4,keyDT,1028,2,firstFit);
			d.createfile(fileName2,ownerName,fileFormat,128,4,keyDT,1028,2,firstFit);
			cout<<d.dat.DAT<<endl;
			d.createfile(fileName4,ownerName,fileFormat,128,32,keyDT,1028,2,firstFit);
			d.createfile(fileName3,ownerName,fileFormat,128,2,keyDT,1028,2,firstFit);
			cout<<d.dat.DAT<<endl;
			d.delfile(fileName2,ownerName);
			d.createfile(fileName2,ownerName,fileFormat,128,4,keyDT,1028,2,firstFit);
			cout<<d.dat.DAT<<endl;
			d.delfile(fileName4,ownerName);
			cout<<d.dat.DAT<<endl;
			d.createfile(fileName4,ownerName,fileFormat,128,32,keyDT,1028,2,worstFit);
			cout<<d.dat.DAT<<endl;
			d.delfile(fileName4,ownerName);
			cout<<d.dat.DAT<<endl;
			d.createfile(fileName4,ownerName,fileFormat,128,1558,keyDT,1028,2,bestFit);
			cout<<d.dat.DAT<<endl;
			cout<<"howmuchempty: "<<d.howmuchempty()<<endl;



//void Disk::createfile (string & fileName,  string & fileOwner, string & fileFormat, unsigned int entryLen, unsigned int requestedSectors, string & keyDT, unsigned int offset, unsigned int keyLen, FitType fitType)


		}
	static void printSectors(Disk& my)
	{
		for (int i=0;i<3200;i++)
		{
			Sector my1;
			my.readSector(i,&my1);
			cout<<"num of sector :"<<my1.sectorNr<<" "<<my1.rawData<<endl;
		}
	}
	public: 

	static void test_1_2() 
	{ 
		
		try  
		{    
			create();
		}   
		catch (exception ex) 
		{    cout << ex.what() << endl;   } 
	}

};