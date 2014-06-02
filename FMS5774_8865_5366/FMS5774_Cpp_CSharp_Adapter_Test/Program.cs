using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;

namespace FMS5774_Cpp_CSharp_Adapter_Test
{
    class Program
    {

        List<FCB> fcbList;

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
                d.Format("oshri");
                Console.WriteLine("\nFormat Disk:");
                Console.WriteLine(ToStringProperty(d.GetVolumeHeader()));
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
