using System.Windows.Controls;
using System.Windows;
using FMS5774_Cpp_CSharp_Adapter;
using System;
using FMS5774_Cpp_CSharp_Adapter;



namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for DiskUserControl.xaml
    /// </summary>
    public partial class DiskUserControl : UserControl
    {
        public DiskUserControl(Disk my)
        {
            InitializeComponent();
            sizeBar.Value = Convert.ToDouble(my.Howmuchempty(my.myDiskPointer));
            nameLabl.Content = my.GetVolumeHeader().DiskName;
            this.MouseDoubleClick += new System.Windows.Input.MouseButtonEventHandler(doubleClickEvent);
        }

        private void doubleClickEvent(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            throw new NotImplementedException();
        }
    }
}
