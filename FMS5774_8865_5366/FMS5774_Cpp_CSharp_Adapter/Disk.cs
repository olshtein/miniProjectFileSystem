using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace FMS5774_Cpp_CSharp_Adapter
{
    public class Disk
    {
        public IntPtr myDiskPointer;

        public Disk()
        {
            this.myDiskPointer = cppToCsharpAdapter.makeDiskObject();
        }

        ~Disk()
        {
            if (myDiskPointer != null)
                cppToCsharpAdapter.deleteDiskObject(ref myDiskPointer);
        }


        public VolumeHeader GetVolumeHeader()
        {
            try
            {

                VolumeHeader v = new VolumeHeader();
                int structSize = Marshal.SizeOf(v.GetType()); //Marshal.SizeOf(typeof(Student)); 
                IntPtr buffer = Marshal.AllocHGlobal(structSize);
                Marshal.StructureToPtr(v, buffer, true);

                // ... send buffer to dll
                cppToCsharpAdapter.getVolumeHeader(this.myDiskPointer, buffer);
                Marshal.PtrToStructure(buffer, v);

                // free allocate
                Marshal.FreeHGlobal(buffer);

                return v;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public DirEntry GetDirEntry( uint dirIndex)
        {
            try
            {
                DirEntry d = new DirEntry();
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(d.GetType()));
                // ... send buffer to dll        
                cppToCsharpAdapter.getDirEntry(this.myDiskPointer, buffer, dirIndex);
                Marshal.PtrToStructure(buffer, d);
                // free allocate        
                Marshal.FreeHGlobal(buffer);
                return d;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                throw new Exception(Marshal.PtrToStringAnsi(cString));
            }
        }

        public List<DirEntry> GetDirRoot()
        {

            try
            {
                List<DirEntry> list = new List<DirEntry>();
                for (uint i = 0; i < 28; i++)
                {
                    DirEntry idir = this.GetDirEntry(i);
                    if (idir.EntryStatus == '1')
                        list.Add(this.GetDirEntry(i));

                }
                return list;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                throw new Exception(Marshal.PtrToStringAnsi(cString));
            }
        }


        public void Createdisk(string diskName, string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.createdisk(this.myDiskPointer, diskName, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Mountdisk(string diskName)
        {
            try
            {
                cppToCsharpAdapter.mountdisk(this.myDiskPointer, diskName);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Unmountdisk(IntPtr THIS)
        {
            try
            {
                cppToCsharpAdapter.unmountdisk(this.myDiskPointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public bool Ismounted(IntPtr THIS)
        {
            try
            {
                return cppToCsharpAdapter.ismounted(this.myDiskPointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Recreatedisk(string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.recreatedisk(this.myDiskPointer, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }



        // Level 1

        public void Format(string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.format(this.myDiskPointer, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public int Howmuchempty(IntPtr THIS)
        {
            try
            {
                return cppToCsharpAdapter.howmuchempty(this.myDiskPointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        //Level 2

        public void Createfile(string fileName, string fileOwner, string FinalOrVar,
                                uint recSize, uint fileSize,
                                string keyType, uint keyOffset, uint keySize = 4)
        {
            try
            {
                cppToCsharpAdapter.createfile(this.myDiskPointer, fileName, fileOwner, FinalOrVar,
                              recSize, fileSize,
                                keyType, keyOffset, keySize);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        public void Delfile(string fileName, string fileOwner)
        {
            try
            {
                cppToCsharpAdapter.delfile(this.myDiskPointer, fileName, fileOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        public void Extendfile(string fileName, string fileOwner, uint size)
        {
            try
            {
                cppToCsharpAdapter.extendfile(this.myDiskPointer, fileName, fileOwner, size);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        // Level 3

        public FCB Openfile(string fileName, string fileOwner, string openMode)
        {
            try
            {
                IntPtr p = cppToCsharpAdapter.openfile(this.myDiskPointer, fileName, fileOwner, openMode);
                return new FCB(p);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
    }
}
