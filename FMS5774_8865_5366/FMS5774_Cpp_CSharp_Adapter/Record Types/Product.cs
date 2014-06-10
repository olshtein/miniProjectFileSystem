using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS5774_Cpp_CSharp_Adapter
{
    [StructLayout(LayoutKind.Sequential), Serializable]
    public class Product
    {
        public int barcode;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string manufacturer;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string nameProduct;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string supplier;
        public float price;

        public Product(int Barcode,string Manufacturer,string name ,string Supplier, float Price)
        {
            barcode = Barcode;
            manufacturer = Manufacturer;
            nameProduct = name;
            supplier = Supplier;
            price = Price;
        }
        public static uint sizeKey()
        {
            return sizeof(int);
        }

        public static uint size()
        {
            return 12 * 3 + 4 + 4; //3 * string + int + float
        }
    }
}
