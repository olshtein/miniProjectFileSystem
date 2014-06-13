using System;
using System.Runtime.InteropServices;

namespace FMS5774_Cpp_CSharp_Adapter
{
    public class FCB
    {
        private IntPtr myFCBpointer;

        public FCB(IntPtr myFCBpointer)
        {
            this.myFCBpointer = myFCBpointer;
        }

        ~FCB()
        {
            if (myFCBpointer != null)
                cppToCsharpAdapter.deleteFcbObject(ref myFCBpointer);
        }

        public DirEntry GetFileDescription()
        {
            try
            {
                DirEntry d = new DirEntry();
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(d.GetType()));
                // ... send buffer to dll        
                cppToCsharpAdapter.getFileDesctription(this.myFCBpointer, buffer);
                Marshal.PtrToStructure(buffer, d);
                // free allocate        
                Marshal.FreeHGlobal(buffer);
                return d;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Closefile()
        {
            try
            {
                cppToCsharpAdapter.closefile(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public object readRec(object dest, uint readForUpdate = 0)
        {
            try
            {

                IntPtr buffer;
                buffer = Marshal.AllocHGlobal(Marshal.SizeOf(dest.GetType()));

                cppToCsharpAdapter.readRec(this.myFCBpointer, buffer, readForUpdate);
                Marshal.PtrToStructure(buffer, dest);

                Marshal.FreeHGlobal(buffer);

                return dest;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void writeRec(object source)
        {
            try
            {
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(source.GetType()));
                Marshal.StructureToPtr(source, buffer, true);

                cppToCsharpAdapter.writeRec(this.myFCBpointer, buffer);

                Marshal.FreeHGlobal(buffer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void seekRec(uint from, int pos)
        {
            try
            {
                cppToCsharpAdapter.seekRec(this.myFCBpointer, from, pos);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void updateRecCancel()
        {
            try
            {
                cppToCsharpAdapter.updateRecCancel(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void deleteRec()
        {
            try
            {
                cppToCsharpAdapter.deleteRec(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void updateRec(object source)
        {
            try
            {
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(source.GetType()));
                Marshal.StructureToPtr(source, buffer, true);
                cppToCsharpAdapter.updateRec(this.myFCBpointer, buffer);
                Marshal.FreeHGlobal(buffer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public IOState IorO()
        {
            try
            {
                return cppToCsharpAdapter.IorO(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public override bool Equals(Object obj)
        {
            // If parameter is null return false.
            if (obj == null)
            {
                return false;
            }

            // If parameter cannot be cast to Point return false.
            FCB p = obj as FCB;
            if ((Object)p == null)
            {
                return false;
            }

            // Return true if the fields match:
            return (GetFileDescription().FileName == p.GetFileDescription().FileName);
        }

        public bool Equals(FCB p)
        {
            // If parameter is null return false:
            if ((object)p == null)
            {
                return false;
            }

            // Return true if the fields match:
            return (GetFileDescription().FileName == p.GetFileDescription().FileName);
        }

        public override int GetHashCode()
        {
            return GetFileDescription().FileName.GetHashCode();
        }
    }
}
