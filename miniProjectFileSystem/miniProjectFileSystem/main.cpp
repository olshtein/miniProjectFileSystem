#include <iostream>
#include <string>
#include "Disk.h"

using namespace std;


void main()
{
	string namefile("newMyDisk");
	string diskOwner("meir");
	try
	{
	Disk newMyDisk(namefile,diskOwner,'m');
	Disk newMyDisk1(namefile,diskOwner,'m');
	newMyDisk.seekToSector(0);
	newMyDisk1.seekToSector(0);

	for (int i=0;i<3200;i++)
	{
		Sector my;
		Sector my2;
		newMyDisk.readSector(i,&my);
		newMyDisk1.readSector(&my2);
		cout<<my.sectorNr<<endl<<my2.sectorNr<<endl;
	}

	newMyDisk.unmountdisk();
	newMyDisk1.unmountdisk();
	system("pause");
	}
	catch (exception& e)
  {
    cout << e.what() << '\n';
	system("pause");
  }
}