using System;
using System.Runtime.InteropServices;

namespace FMS5774_Cpp_CSharp_Adapter.RecordTypes
{

    [StructLayout(LayoutKind.Sequential), Serializable]
    public class Employee : IRecord
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string ID;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string lestName;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string firstName;
        public float salary;
        public int seniority;

        public Employee()
        {
        }

        public Employee(string id, string LestName,string FirstName,float Salary,int Seniority)
        {
            ID = id;
            lestName = LestName;
            firstName = FirstName;
            salary = Salary;
            seniority = Seniority;
        }

        public string Key
        {
            get { return ID; }
            set { ID = value; }
        }

        public static uint sizeKey()
        {
            return 12;
        }
        public static uint size()
        {
            return 12 * 3 + 4 + 4; //3 * string + int + float
        }
    }
}