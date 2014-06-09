using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS5774_Cpp_CSharp_Adapter
{
    [StructLayout(LayoutKind.Sequential), Serializable]
    public class store
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string phone;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string name;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public String address;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public String city;

        public store(string Phone, string Name, string Address, string City)
        {
            phone = Phone;
            name = Name;
            address = Address;
            city = City;
        }
        public static uint size()
        {
            return 12 * 4;
        }
    }
}
