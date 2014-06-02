using System.Windows;
using System.Collections.Generic;
using System.Windows.Controls;
using Microsoft.Win32;
using FMS5774_Cpp_CSharp_Adapter;
using FMS5774_8856_5366_WPF.CreateDisk;
using System.IO;

namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string user; //current user of the system.

        public MainWindow()
        {
            InitializeComponent();
            InitializeDiskList();
            InitializeUsersList();
        }

        private void InitializeDiskList()
        {
            string[] diskPaths = Directory.GetFiles(Directory.GetCurrentDirectory(), "*.disk");

            foreach (string diskPath in diskPaths)
            {
                Disk dsk = new Disk();
                dsk.Mountdisk(Path.GetFileNameWithoutExtension(diskPath));
                DiskUserControl duc = new DiskUserControl(dsk);
                DisksWrapPanel.Children.Insert(0, duc);
            }
        }

        private void InitializeUsersList()
        {
            //get user names from file
            string filePath = Directory.GetCurrentDirectory() + "\\..\\..\\Resorces\\Users.txt";
            string[] usersArr = File.ReadAllLines(filePath);

            //make radio buttons for each user
            RadioButton[] radioButtons = new RadioButton[usersArr.Length];
            for (int i = 0; i < usersArr.Length; i++)
            {
                radioButtons[i] = new RadioButton { Content = usersArr[i], IsChecked = false, GroupName = "users" };
                radioButtons[i].Checked += UsersRadioButtons_Checked;
            }

            // make first radio button default if exist.
            if (radioButtons.Length > 0)
                radioButtons[0].IsChecked = true;

            //bind the radio buttons as the items for the 'chage user' menu.
            this.changeUserMenuItem.ItemsSource = radioButtons;
        }

        private void UsersRadioButtons_Checked(object sender, RoutedEventArgs e)
        {
            // Check of the raiser of the event is a checked RadioButton.
            if (((RadioButton)sender).IsChecked == true)
            {
                // This is the correct control.
                user = (string)((RadioButton)sender).Content;
            }
        }

        private void New_Disk_Click(object sender, RoutedEventArgs e)
        {
            // Instantiate the dialog box
            CreateDiskDialog dlg = new CreateDiskDialog();

            // Configure the dialog box
            dlg.Owner = this;

            // Open the dialog box modally 
            dlg.ShowDialog();

            if (dlg.DialogResult == true)
            {
                Disk dsk = new Disk();
                dsk.Createdisk(dlg.DiskName, user);
                DiskUserControl duc = new DiskUserControl(dsk);
                DisksWrapPanel.Children.Insert(0, duc);
            }
        }

        private void Mount_Disk_Click(object sender, RoutedEventArgs e)
        {
            //Microsoft.Win32.OpenFileDialog ofd = new Microsoft.Win32.OpenFileDialog();
            //ofd.Filter = "disk Files (*.disk)|*.disk|All Files (*.*)|*.*";
            //ofd.ShowDialog();
            //if (ofd.FileName!="")
            //{
            //    Disk add = new Disk();
            //    string fileNamePart;
            //    ofd.FileName.CopyTo(0,fileNamePart,0,ofd.FileName.c
            //    add.Mountdisk(ofd.FileName);
            //}

        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
        }
    }
}
