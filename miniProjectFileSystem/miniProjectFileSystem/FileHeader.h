#pragma once

#include "BaseSector.h"
#include "DAT.h"
#include "DirEntry.h"

struct FileHeader : BaseSector
{
DirEntry fileDesc ; // ���� �� ������ �� ����� ������� (file descriptor)
DATtype FAT; // FAT

char emptyArea[744];  //���� ������ �����
};

