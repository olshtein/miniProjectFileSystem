#include "Disk.h";
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>     



extern "C"
{
	// init disk
	__declspec(dllexport) Disk*  makeDiskObject()
	{
		return new Disk();
	}
	__declspec(dllexport) void  deleteDiskObject(Disk*& THIS)
	{
		if (THIS != NULL)
			delete  THIS;
		THIS = NULL;
	}
	__declspec(dllexport) const  char*  getLastDiskErrorMessage(Disk* THIS)
	{
		const char* str = THIS->GetLastErrorMessage().c_str();
		return str;
	}

	__declspec(dllexport) void  deleteFcbObject(FCB*& THIS)
	{
		if (THIS != NULL)
			delete  THIS;
		THIS = NULL;
	}
	__declspec(dllexport) const  char*  getLastFcbErrorMessage(FCB* THIS)
	{
		const char* str = THIS->GetLastErrorMessage().c_str();
		return str;
	}

	// Level 0
	__declspec(dllexport) void  createdisk(Disk* THIS, char* diskName, char* diskOwner)
	{
		try
		{
			THIS->createdisk(string(diskName), string(diskOwner));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  mountdisk(Disk* THIS, char* diskName)
	{
		try
		{
			THIS->mountdisk(string(diskName));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  unmountdisk(Disk* THIS)
	{
		try
		{
			THIS->unmountdisk();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  recreatedisk(Disk* THIS, char* diskOwner)
	{
		try
		{
			THIS->recreatedisk(string(diskOwner));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	// Level 1
	__declspec(dllexport) void  format(Disk* THIS, char* diskOwner)
	{
		try
		{
			THIS->format(string(diskOwner));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) int   howmuchempty(Disk* THIS)
	{
		try
		{
			return THIS->howmuchempty();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	//Level 2
	__declspec(dllexport) void  createfile(Disk* THIS, char* fileName, char* fileOwner, char* FinalOrVar,
		unsigned int recSize, unsigned int fileSize,
		char* keyType, unsigned int keyOffset, unsigned int keySize)
	{
		try
		{
			THIS->createfile(string(fileName), string(fileOwner), string(FinalOrVar),
				recSize, fileSize,
				string(keyType), keyOffset, keySize);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	__declspec(dllexport) void  delfile(Disk* THIS, char* fileName, char* fileOwner)
	{
		try
		{
			THIS->delfile(string(fileName), string(fileOwner));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  extendfile(Disk* THIS, char* fileName, char* fileOwner, unsigned int size)
	{
		try
		{
			THIS->extendfile(string(fileName), string(fileOwner), size);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}


	// Level 3
	__declspec(dllexport)  FCB *  openfile(Disk* THIS, char* fileName, char* fileOwner, char* openMode)
	{
		try
		{
			return THIS->openfile(string(fileName), string(fileOwner), string(openMode));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}


	// FCB
	__declspec(dllexport) void  closefile(FCB* THIS)
	{
		try
		{
			THIS->closefile();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  readRec(FCB* THIS, char * dest, unsigned int readForUpdate)
	{
		try
		{
			THIS->readRec(dest, readForUpdate);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  writeRec(FCB* THIS, char * source)
	{
		try
		{
			THIS->writeRec(source);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  seekRec(FCB* THIS, unsigned int from, int pos)
	{
		try
		{
			THIS->seekRec(from, pos);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	__declspec(dllexport) void  updateRecCancel(FCB* THIS)
	{
		try
		{
			THIS->updateCancel();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  deleteRec(FCB* THIS)
	{
		try
		{
			THIS->deleteRec();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  updateRec(FCB* THIS, char * source)
	{
		try
		{
			THIS->updateRec(source);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}



	// extra

	__declspec(dllexport)   void  getVolumeHeader(Disk* THIS, VolumeHeader* buffer)
	{
		memcpy_s(buffer, sizeof(VolumeHeader), &THIS->getVolumeHeader(), sizeof(VolumeHeader));
	}

	string str;
	__declspec(dllexport) const char*  getDat(Disk* THIS)
	{
		stringstream ss;
		ss << THIS->getDAT().sectorNr;
		ss << THIS->getDAT().DAT;
		ss << THIS->getDAT().emptyArea;
		str = ss.str();
		return str.c_str();
	}

}
