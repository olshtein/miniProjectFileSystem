#include <iostream>
#include <string>
#include "Disk.h"
#include "TestLevel_0.h"

using namespace std;


void main()
{
	try
	{
		TestLevel_0 myTest;
		myTest.test_0();
		
	}
	catch (logic_error e)
	{
		cout << e.what() << '\n';
		system("pause");
	}
}