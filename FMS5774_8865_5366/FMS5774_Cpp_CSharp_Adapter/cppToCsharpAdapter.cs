using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices; 

namespace FMS5774_Cpp_CSharp_Adapter
{
    public class cppToCsharpAdapter
    {
        const string dllPath = "FMS5774_8865_5366.dll";

        [DllImport(dllPath)]
        public static extern int sum(int a, int b); 
    }
}
