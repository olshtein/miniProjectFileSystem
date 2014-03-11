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
};

