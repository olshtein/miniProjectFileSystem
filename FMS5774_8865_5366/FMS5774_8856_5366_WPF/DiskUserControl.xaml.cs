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
        Disk myDisk;
        public DiskUserControl(Disk my)
        {
            myDisk = my;
            InitializeComponent();
            int Used = 1600 - my.Howmuchempty(my.myDiskPointer);
            sizeBar.Value = Convert.ToDouble(Used);
            TextBlockDiskUse.Text = "Used: " +(2* Used).ToString()+" KB";
            TextBlockDiskFree.Text = "free: " + (2*(1600 - Used)).ToString()+" KB";
            nameLabl.Content = my.GetVolumeHeader().DiskName;
            this.MouseDoubleClick += new System.Windows.Input.MouseButtonEventHandler(doubleClickEvent);
        }

        private void doubleClickEvent(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            FileWindow myFile = new FileWindow(myDisk);
            myFile.Show();

        }
    }
}
