using System.Windows.Controls;
using System.Windows;
using FMS5774_Cpp_CSharp_Adapter;
using System;
<<<<<<< HEAD
=======

>>>>>>> 2c7c4b70d731416c8b8bdcfcc8d378434b33d4e4


namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for DiskUserControl.xaml
    /// </summary>
    public partial class DiskUserControl : UserControl
    {
<<<<<<< HEAD
        public Disk Dsk { get; set; }
        private Window container;

        public DiskUserControl(Window container, Disk my)
        {
            Dsk = my;
            this.container = container;
=======
        Disk myDisk;
        public DiskUserControl(Disk my)
        {
            myDisk = my;
>>>>>>> 2c7c4b70d731416c8b8bdcfcc8d378434b33d4e4
            InitializeComponent();
            int Used = 1600 - my.Howmuchempty(my.myDiskPointer);
            sizeBar.Value = Convert.ToDouble(Used);
            TextBlockDiskUse.Text = "Used: " +(2* Used).ToString()+" KB";
            TextBlockDiskFree.Text = "free: " + (2*(1600 - Used)).ToString()+" KB";
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
<<<<<<< HEAD
            container.Visibility = Visibility.Visible;
=======
            FileWindow myFile = new FileWindow(myDisk);
            myFile.Show();

>>>>>>> 2c7c4b70d731416c8b8bdcfcc8d378434b33d4e4
        }
    }
}
