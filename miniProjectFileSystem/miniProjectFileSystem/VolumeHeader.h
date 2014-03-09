#pragma once

#include "BaseSector.h"

/*************************************************
* STRUCT
*	VolumeHeader
* INHERITS
*	BaseSector
* MEANING
*	Struct representing a sector-length volume header of a disk.
* SEE ALSO
*   SectorBase
*	Sector
*   DAT
*	FileHeader
*	RD_Sector
**************************************************/
struct VolumeHeader : BaseSector
{
	char diskName[12]; //�� ����� �����
	char diskOwner[12]; //�� ��� �����   
	char prodDate[11]; //����� ���� ����� (ddmmyyyy)
	unsigned intClusQty; //��"� ������ ����� (clusters)  �����
	unsigned int dataClusQty; //���� ������ ����� ������� ����
	unsigned int addrDAT; //����� ������ ����� �� �-DAT
	unsigned int addrRootDir; //����� �-cluster ����� �� ������� ������ (Root Directory)
	unsigned int addrDATcpy; //����� ������ ����� ���� ��� �� �-DAT 
	unsigned int addrRootDirCpy; //����� �-cluster ����� ���� ��� �� ������� ������ (Root Directory)  
	unsigned int addrDataStart;  //����� �-cluster ������ ����� ������ �������.
	char formatDate [11];  //����� ������ (ddmmyyyy)
	bool isFormated; // ��� ��� ������?
	char emptyArea [944]; //���� ������ �����
};

