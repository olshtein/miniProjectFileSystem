#pragma once

#include "BaseSector.h"

struct DirEntry
{
char Filename[12]; //שם הקובץ
char fileOwner[12];  //שם בעל הקובץ

unsigned int fileAddr;  //כתובת הסקטור הראשון של הקובץ
char crDate[11];  //תאריך יצירת הקובץ
unsigned int fileSize;  //גודל הקובץ, כמספר סקטורים
unsigned int eofRecNr;  //מיקום "רשומת" ה-end-of-file (המספר הסידורי של מיקומה מהתחלת הקובץ)
unsigned int maxRecSize;  //אורך רשומה מרבי
unsigned int actualRecSize;  //אורך רשומה בפועל
char recFormat [2];  /*  סוג:
			-          אם מדובר בקובץ נתונים, זה מסמל סוג רשומה כלומר, אורך קבוע או משתנה "F" : או  "V"
			-          אם מדובר בתת-תיקיה, ערך השדה הזה יהיה האות "D".*/

unsigned int keyOffset; //Offset של התחלת המפתח בתוך הרשומה
unsigned int keySize;  // אורך המפתח, כמספר בתים
char keyType[2];  /*טיפוס נתונים של ערך המפתח:
						"I" -  מספר שלם (int)
						"F" – מספר ממשי  (float)
						"D" – מספר ממשי כפול (double)
						"C"  - מחרוזת תווים*/

unsigned char entryStatus; /* שדה זה מעיד על מצב הכניסה הספציפית בתיקייה. המצב יכול להיות אחד מתוך שלושה:
							0        -  כניסה ריקה (empty): הכניסה עדיין לא הייתה בשימוש מאז שבוצע format  על הדיסק .
							1        -  כניסה פעילה (active): הכניסה מייצגת קובץ קיים ופעיל.
							2        -  כניסה לא פעילה (inactive): הכניסה מייצגת קובץ מחוק.*/
};

