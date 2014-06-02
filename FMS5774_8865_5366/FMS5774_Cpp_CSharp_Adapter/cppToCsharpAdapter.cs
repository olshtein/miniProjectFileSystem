using System;
using System.Runtime.InteropServices;

namespace FMS5774_Cpp_CSharp_Adapter
{
   

[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
public class VolumeHeader
{
    uint sectorNr;
        
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
    string diskName;
    public string DiskName { get { return diskName; }}

    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
    string diskOwner;
    public string DiskOwner { get { return diskOwner; } }

    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
    string prodDate;
    public string ProdDate { get { return prodDate; } }

    uint clusQty;
    public uint ClusQty{ get { return clusQty; } }

    uint dataClusQty;
    public uint DataClusQty { get { return dataClusQty; } }

    uint addrDAT;
    public uint AddrDAT { get { return addrDAT; } }

    uint addrRootDir;
    public uint AddrRootDir { get { return addrRootDir; } }

    uint addrDATcpy;
    public uint AddrDATcpy { get { return addrDATcpy; } }

    uint addrRootDirCpy;
    public uint AddrRootDirCpy { get { return addrRootDirCpy; } }

    uint addrDataStart;
    public uint aAddrDataStart { get { return addrDataStart; } }

    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
    string formatDate;
    public string FormatDate { get { return formatDate; } }

    [MarshalAs(UnmanagedType.I1)]
    bool isFormated;
    public bool IsFormated { get { return isFormated; } }


    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 944)]
    string emptyArea;
}

  

   
public class cppToCsharpAdapter
{
    const string dllPath  = "FMS5774_DLL.dll";

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl )]
    public static extern int sum(int a, int b);


    // init disk
    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern IntPtr makeDiskObject();

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void deleteDiskObject(ref IntPtr THIS);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern IntPtr getLastDiskErrorMessage(IntPtr THIS);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern IntPtr getLastFcbErrorMessage(IntPtr THIS);

        [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void deleteFcbObject(ref IntPtr THIS);
        
    // Level 0

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void createdisk(IntPtr THIS, string diskName, string diskOwner);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void mountdisk(IntPtr THIS, string diskName);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void unmountdisk(IntPtr THIS);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void recreatedisk(IntPtr THIS, string diskOwner);



    // Level 1
    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void format(IntPtr THIS, string diskOwner);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern int howmuchempty(IntPtr THIS);


    //Level 2
    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void createfile(IntPtr THIS, string fileName, string fileOwner, string FinalOrVar,
                            uint recSize, uint fileSize,
                            string keyType, uint keyOffset, uint keySize = 4);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void delfile(IntPtr THIS, string fileName, string fileOwner);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void extendfile(IntPtr THIS, string fileName, string fileOwner, uint size);


    // Level 3
    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern IntPtr openfile(IntPtr THIS, string fileName, string fileOwner, string openMode);


    // FCB
    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void closefile(IntPtr THIS);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void readRec(IntPtr THIS, IntPtr dest, uint readForUpdate = 0);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void writeRec(IntPtr THIS, IntPtr source);


    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void seekRec(IntPtr THIS, uint from, int pos);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void updateRecCancel(IntPtr THIS);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void deleteRec(IntPtr THIS);

    [DllImport(dllPath , CallingConvention=CallingConvention.Cdecl)]
    public static extern void updateRec(IntPtr THIS, IntPtr source);

    //extra
    [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.AnsiBStr)]
    public static extern string getDat(IntPtr THIS);

    [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
    public static extern void getVolumeHeader(IntPtr THIS, IntPtr buffer);

    [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
    [return:MarshalAs(UnmanagedType.U1)]
    public static extern bool IorO(IntPtr THIS);
}
}
