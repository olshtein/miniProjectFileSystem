#include <iostream>
#include <string>
#include "Disk.h"
#include "FCB.h"

using namespace std;




class Test_3
{

public: 

	static void test_3() 
	{ 
		try  
		{    
			string diskName1 = "disk 1";  
			string ownerName1 = "meir";  
			Disk d1; 
		
		d1.createdisk(diskName1, ownerName1);
		d1.mountdisk(diskName1);
		d1.createfile(diskName1,ownerName1,string("F"),20,2,string("I"),0);

			string diskName2 = "disk 2";  
			string ownerName2= "sara";  
			Disk d2;

		d2.createdisk(diskName2,ownerName2);
		d2.mountdisk(diskName2);
		d2.createfile(diskName2,ownerName2,string("F"),100,9,string("I"),0);

		FCB* ptr1 = d1.openfile(diskName1,string("noa"),string("I"));
	//גם לנעמה נאפשר ונקצה עבור fcb חדש שגם הוא מכיל את כל המידע שבקובץ
	FCB* ptr2 = d1.openfile(diskName1,string("naama"),string("I"));

	char *arr =new char[ptr1->fileDesc.actualRecSize];
	ptr1->readRec(arr);//עכשיו המערך מכיל את פרטי הרשומה הראשונה שבקובץ fil1 

	ptr1->readRec(arr);//עכשיו המערך מכיל את פרטי הרשומה השניה שבקובץ fil1 

	//נסגור את הקובץ fil1 שנועה פתחה 
	//נעמה יכולה לקרא בו עדיין
	ptr1->closefile();

	ptr2->readRec(arr);//עכשיו המערך מכיל את פרטי הרשומה הראשונה שבקובץ fil1

	//ptr1->readRec(arr);//נזרוק חריגה במקרה כזה כי סגרנו כבר את הקובץ

	//נאפשר לה
	FCB* ptr3 = d2.openfile(diskName2,ownerName2,string("IO"));

	FCB* ptr4= d2.openfile(diskName2,string("noa"),string("I"));
	

	Disk d3;
	d3.createdisk(string ("X"),string("avi"));
	d3.mountdisk(string ("X"));

	//אנחנו מבקשים מהדיסק שיצור לנו קובץ שבו כל רשומה באורך 25 בתים
	//סה"כ יניו 40 רשומות בכל סקטור. ואנחנו רוצים 20 סקטורים . סה"כ הדיסק יתן לנו 11 קלסטרים כי צריך עוד סקטור
	//עבור תוית הזיהוי של הקובץ וזה אומר עוד יחידת הקצאה 
	//(יהיה לנו סקטור 1 מיותר בקובץ)
	//סה"כ נוכל להכניס 800 רשומות לקובץ שלנו
	d3.createfile(string("file1.dat"),string("moshe"),string("F"),25,20,string("I"),0);
	
	ptr1 = d3.openfile(string("file1.dat"),string("naomi"),string("I"));//אפשרי - כי סגרנו את הקובץ הקודם 
	

		}   
		catch (exception ex) 
		{    cout << ex.what() << endl;   } 
	}
}; 
