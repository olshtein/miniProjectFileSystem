using System.Windows.Controls;
using System.Windows;
using FMS5774_Cpp_CSharp_Adapter;
using System;


namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for DiskUserControl.xaml
    /// </summary>
    public partial class DiskUserControl : UserControl
    {
        public Disk Dsk { get; set; }
        private Window container;

        public DiskUserControl(Window container, Disk my)
        {
            Dsk = my;
            this.container = container;
            InitializeComponent();
            sizeBar.Value = 1600 - Convert.ToDouble(my.Howmuchempty(my.myDiskPointer));
            nameLabl.Content = my.GetVolumeHeader().DiskName;
        }

        private void DiskUserControl_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            FileWindow fw = new FileWindow(Dsk);
            container.Visibility = Visibility.Hidden;
            fw.Show();
            fw.Closed += fw_Closed;
        }

        void fw_Closed(object sender, EventArgs e)
        {
            container.Visibility = Visibility.Visible;
        }
    }
}
