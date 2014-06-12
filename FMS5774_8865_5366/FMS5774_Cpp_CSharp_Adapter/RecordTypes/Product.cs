using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS5774_Cpp_CSharp_Adapter.RecordTypes
{
    [StructLayout(LayoutKind.Sequential), Serializable]
    public class Product : IRecord
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string barcode;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string manufacturer;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string nameProduct;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string supplier;
        public float price;

        public Product(string Barcode,string Manufacturer,string name ,string Supplier, float Price)
        {
            barcode = Barcode;
            manufacturer = Manufacturer;
            nameProduct = name;
            supplier = Supplier;
            price = Price;
        }

        public string Key
        {
            get { return barcode; }
            set { barcode = value; }
        }

        public static uint sizeKey()
        {
            return sizeof(int);
        }

        public static uint size()
        {
            return 12 * 4  + 4; //3 * string + int + float
        }
    }
}
