using FMS5774_Cpp_CSharp_Adapter.RecordTypes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FMS5774_8856_5366_WPF.RecordsUserControls
{
    interface IRecordUserControl
    {
        IRecord Record { get; set; }
    }
}
