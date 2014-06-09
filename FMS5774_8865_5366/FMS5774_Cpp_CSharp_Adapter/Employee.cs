using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS5774_Cpp_CSharp_Adapter
{

    [StructLayout(LayoutKind.Sequential), Serializable]
    public class Employee
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string ID;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string lestName;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string firstName;
        public float salary;
        public int seniority;

        public Employee(string id, string LestName,string FirstName,float Salary,int Seniority)
        {
            ID = id;
            lestName = LestName;
            firstName = FirstName;
            salary = Salary;
            seniority = Seniority;
        }

        public static uint size()
        {
            return 12 * 3 + 4 + 4; //3 * string + int + float
        }
    }
}