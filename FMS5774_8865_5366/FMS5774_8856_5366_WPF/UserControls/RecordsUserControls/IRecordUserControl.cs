using FMS5774_Cpp_CSharp_Adapter.RecordTypes;

namespace FMS5774_8856_5366_WPF.RecordsUserControls
{
    interface IRecordUserControl
    {
        IRecord Record { get; set; }

        void ClearFields();
        void DisableControls();
    }
}
