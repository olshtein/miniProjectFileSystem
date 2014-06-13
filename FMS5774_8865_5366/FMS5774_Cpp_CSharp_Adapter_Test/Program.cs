using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;
using FMS5774_Cpp_CSharp_Adapter;
using FMS5774_Cpp_CSharp_Adapter.RecordTypes;

namespace FMS5774_Cpp_CSharp_Adapter_Test
{
    class Program
    {
        public static string ToStringProperty(object t)
        {
            string str = "";
            foreach (PropertyInfo item in t.GetType().GetProperties())
                str += "\n" + item.Name + ": " + item.GetValue(t, null);
            return str;
        }

        static void Main(string[] args)
        {

            try
            {
                int structSize = Marshal.SizeOf(typeof(VolumeHeader));
                Console.WriteLine("Marshal.SizeOf(typeof(VolumeHeader) == " + structSize);

                Disk d = new Disk();
                Console.WriteLine("\nMake Disk:");
                Console.WriteLine(ToStringProperty(d.GetVolumeHeader()));

                d.Createdisk("disk1", "oshri");
                Console.WriteLine("\nCreate Disk:");
                Console.WriteLine(ToStringProperty(d.GetVolumeHeader()));
                d.Mountdisk("disk1");
                if (d.Ismounted(d.myDiskPointer))
                    Console.WriteLine("Mounted!");
                d.Createfile("f1", "meir", "F", Store.size(), 2, "I", 0);

                FCB fcb = d.Openfile("f1", "meir", "IO");
                fcb.seekRec(fcb.GetFileDescription().FileAddr - 4, 0);
                Store str = new Store("", "", "", "");
                Store str2 = new Store("", "", "", "");
                fcb.readRec(str, 1);
                str = new Store("123", "aaa", "aaa", "aaa");
                fcb.updateRec(str);
                fcb.seekRec(fcb.GetFileDescription().FileAddr - 4, 0);
                fcb.readRec(str2, 0);
                fcb.Closefile();

                DirEntry newdir = d.GetDirEntry(0);
                d.Format("oshri");
                Console.WriteLine("\nFormat Disk:");
                Console.WriteLine(ToStringProperty(d.GetVolumeHeader()));
                d.Unmountdisk(d.myDiskPointer);
                if (d.Ismounted(d.myDiskPointer))
                    Console.WriteLine("Mounted!");
            }
            catch (Exception e)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(e.Message);
                Console.ResetColor();
            }
        }

    }
}
