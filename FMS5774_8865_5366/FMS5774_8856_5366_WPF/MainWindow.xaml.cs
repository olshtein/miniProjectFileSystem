using FMS5774_8856_5366_WPF.CreateDisk;
using FMS5774_Cpp_CSharp_Adapter;
using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;

namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static string user = "";

        public static string User
        {
            get { return user; }
            private set { user = value; }
        }
       

        public MainWindow()
        {
            try
            {
                InitializeComponent();
                InitializeDiskList();
                InitializeUsersList();

            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                this.Close();
            }
        }

        private void InitializeDiskList()
        {
            try
            {
                string[] diskPaths = Directory.GetFiles(Directory.GetCurrentDirectory(), "*.disk");

                foreach (string diskPath in diskPaths)
                {
                    Disk dsk = new Disk();
                    dsk.Mountdisk(Path.GetFileNameWithoutExtension(diskPath));
                    DiskUserControl duc = new DiskUserControl(this, dsk);
                    DisksWrapPanel.Children.Insert(0, duc);
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                this.Close();
            }
        }

        private void InitializeUsersList()
        {
            try
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
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                this.Close();
            }
        }

        private void UsersRadioButtons_Checked(object sender, RoutedEventArgs e)
        {
            try
            {
                // Check of the raiser of the event is a checked RadioButton.
                if (((RadioButton)sender).IsChecked == true)
                {
                    // This is the correct control.
                    User = (string)((RadioButton)sender).Content;
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void New_Disk_Click(object sender, RoutedEventArgs e)
        {
            try
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
                    dsk.Createdisk(dlg.DiskName, User);
                    dsk.Mountdisk(dlg.DiskName);
                    DiskUserControl duc = new DiskUserControl(this, dsk);
                    DisksWrapPanel.Children.Insert(0, duc);
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                this.Close();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }
        
    }
}
