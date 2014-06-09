#include <iostream>
#include <string>
#include "TestLevel_0.h"
#include "TestLevel_3.h"
#include "TestLevel_1_2.h"

using namespace std;


void main()
{
	try
	{
		TestLevel_0 myTest_0;
		myTest_0.test_0();
		//Test_3 myTest_3;
		//myTest_3.test_3();
		system("pause");

	}
	catch (exception e)
	{
		cout << e.what() << '\n';
		system("pause");
	}
}
