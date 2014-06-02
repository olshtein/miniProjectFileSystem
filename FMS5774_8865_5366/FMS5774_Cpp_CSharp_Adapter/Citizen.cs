using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS5774_Cpp_CSharp_Adapter
{
    [StructLayout(LayoutKind.Sequential), Serializable]
    class Citizen
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public StringBuilder ID;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public StringBuilder firstName;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public StringBuilder lastName;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public StringBuilder fatherName;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public StringBuilder motherName;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public StringBuilder fatherID;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public StringBuilder motherID;
        
    };
}
