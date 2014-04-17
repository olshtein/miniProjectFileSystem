#include <iostream>
#include <string>
#include "Disk.h"
#include "TestLevel_0.h"
#include "TestLevel_1_2.h"

using namespace std;


void main()
{
	try
	{
	//	TestLevel_0 myTest;
	//	myTest.test_0();
		TestLevel_1_2 myTest_2;
		myTest_2.test_1_2();
		system("pause");

	}
	catch (exception e)
	{
		cout << e.what() << '\n';
		system("pause");
	}
}