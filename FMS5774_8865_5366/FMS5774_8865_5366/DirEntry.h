#pragma once

#include "BaseSector.h"

struct DirEntry
{
char Filename[12]; //�� �����
char fileOwner[12];  //�� ��� �����

unsigned int fileAddr;  //����� ������ ������ �� �����
char crDate[11];  //����� ����� �����
unsigned int fileSize;  //���� �����, ����� �������
unsigned int eofRecNr;  //����� "�����" �-end-of-file (����� ������� �� ������ ������ �����)
unsigned int maxRecSize;  //���� ����� ����
unsigned int actualRecSize;  //���� ����� �����
char recFormat [2];  /*  ���:
			-          �� ����� ����� ������, �� ���� ��� ����� �����, ���� ���� �� ����� "F" : ��  "V"
			-          �� ����� ���-�����, ��� ���� ��� ���� ���� "D".*/

unsigned int keyOffset; //Offset �� ����� ����� ���� ������
unsigned int keySize;  // ���� �����, ����� ����
char keyType[2];  /*����� ������ �� ��� �����:
						"I" -  ���� ��� (int)
						"F" � ���� ����  (float)
						"D" � ���� ���� ���� (double)
						"C"  - ������ �����*/

unsigned char entryStatus; /* ��� �� ���� �� ��� ������ �������� �������. ���� ���� ����� ��� ���� �����:
							0        -  ����� ���� (empty): ������ ����� �� ����� ������ ��� ����� format  �� ����� .
							1        -  ����� ����� (active): ������ ������ ���� ���� �����.
							2        -  ����� �� ����� (inactive): ������ ������ ���� ����.*/

DirEntry()
{
	strcpy_s(Filename,1,"");
	strcpy_s(fileOwner,1,"");
	fileAddr = -1;
	strcpy_s(crDate,11,"01/01/1970");
	fileSize = 0; 
	eofRecNr = 0; 
	maxRecSize = 0; 
	actualRecSize = 0;
	strcpy_s(recFormat,2,"F");
	keyOffset=0;
	keySize=0;
	strcpy_s(keyType,2,"I");
	entryStatus = 0;
}
};

