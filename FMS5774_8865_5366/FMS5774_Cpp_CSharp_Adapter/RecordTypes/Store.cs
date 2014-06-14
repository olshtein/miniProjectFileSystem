using System;
using System.Runtime.InteropServices;

namespace FMS5774_Cpp_CSharp_Adapter.RecordTypes
{
    [StructLayout(LayoutKind.Sequential), Serializable]
    public class Store : IRecord
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string phone;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string name;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public String address;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public String city;

        public Store()
        {
        }

        public Store(string Phone, string Name, string Address, string City)
        {
            phone = Phone;
            name = Name;
            address = Address;
            city = City;
        }

        public string Key
        {
            get { return phone; }
            set { phone = value; }
        }

        public static uint sizeKey()
        {
            return 12; //phone is the key
        }
        public static uint size()
        {
            return 12 * 4;
        }
    }
}
