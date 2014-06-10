using System.Windows.Controls;
using System.Windows.Input;
using System.Windows;
using System.Windows.Media;
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
            int Used = 1600 - my.Howmuchempty(my.myDiskPointer);
            sizeBar.Value = Convert.ToDouble(Used);
            TextBlockDiskUse.Text = "Used: " +(2* Used).ToString()+" KB";
            TextBlockDiskFree.Text = "Free: " + (2*(1600 - Used)).ToString()+" KB";
            TextBlockOwner.Text = "Owner: " + Dsk.GetVolumeHeader().DiskOwner;
            nameLabel.Content = my.GetVolumeHeader().DiskName;
        }

        private void DiskUserControl_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            OpenDisk();
        }

        private void OpenDisk()
        {
            if (Dsk.Ismounted(Dsk.myDiskPointer))
            {
                FileWindow fw = new FileWindow(Dsk);
                container.Visibility = Visibility.Hidden;
                fw.Show();

                fw.Closed += fw_Closed;
            }
            else
            {
                MessageBox.Show("Error: Disk is not mounted", "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        void fw_Closed(object sender, EventArgs e)
        {
            container.Visibility = Visibility.Visible;
        }

        private void OpenMenuItem_Click(object sender, RoutedEventArgs e)
        {
            OpenDisk();
        }

        private void UnmountMenuItem_Click(object sender, RoutedEventArgs e)
        {
            Dsk.Unmountdisk(Dsk.myDiskPointer);

            //visual representation
            sizeBar.Visibility = Visibility.Hidden;
            sizeText.Visibility = Visibility.Hidden;
            innerGStop.Color = Colors.LightGray;
            outerGStop.Color = Colors.Gray;

            //functional changes
            UnmountMenuItem.Visibility = Visibility.Collapsed;
            MountMenuItem.Visibility = Visibility.Visible;
            OpenMenuItem.IsEnabled = false;
            FormatMenuItem.IsEnabled = true;
        }

        private void MountMenuItem_Click(object sender, RoutedEventArgs e)
        {
            Dsk.Mountdisk(nameLabel.Content.ToString());

            //visual representation
            sizeBar.Visibility = Visibility.Visible;
            sizeText.Visibility = Visibility.Visible;
            innerGStop.Color = Colors.Cyan;
            outerGStop.Color = Colors.Blue;

            //functional changes
            UnmountMenuItem.Visibility = Visibility.Visible;
            MountMenuItem.Visibility = Visibility.Collapsed;
            OpenMenuItem.IsEnabled = true;
            FormatMenuItem.IsEnabled = false;
        }

        private void FormatMenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (!Dsk.Ismounted(Dsk.myDiskPointer))
            {
                MessageBoxResult mbr = MessageBox.Show("This operation can't be undone. are you sure you want to continue?", "Warning!", MessageBoxButton.OKCancel, MessageBoxImage.Warning);
                if (mbr == MessageBoxResult.Cancel)
                    return;

                try
                {
                    Dsk.Format(MainWindow.User);
                    MessageBox.Show("Success! Disk was formated", "Success", MessageBoxButton.OK);
                }
                catch (Exception exp)
                {
                    MessageBox.Show(exp.Message, "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
                }

            }
        }
    }
}
