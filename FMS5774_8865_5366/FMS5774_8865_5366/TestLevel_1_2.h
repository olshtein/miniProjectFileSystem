#pragma once
#include <iostream>
#include <string>
#include "Disk.h"

using namespace std;


class TestLevel_1_2
{
	static void create()
		{
			string diskName = "disk 1";  
			string ownerName = "meir";  
			Disk d;
			d.createdisk(diskName, ownerName);

		}
	public: 

	static void test_1() 
	{ 
		
		try  
		{    
			string diskName = "disk 1";  
			string ownerName = "meir";  

			diskName = "disk 2";

		}   
		catch (exception ex) 
		{    cout << ex.what() << endl;   } 
	}

};