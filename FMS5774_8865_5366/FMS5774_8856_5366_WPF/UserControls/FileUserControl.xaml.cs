using FMS5774_Cpp_CSharp_Adapter;
using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for FileUserControl.xaml
    /// </summary>
    public partial class FileUserControl : UserControl
    {
        public DirEntry DirEntry { get; set; }

        public event EventHandler OpenMenuItemClicked;
        public event EventHandler OpenReadOnlyMenuItemClicked;
        public event EventHandler OpenAddOnlyMenuItemClicked;
        public event EventHandler DeleteMenuItemClicked;

        public FileUserControl(DirEntry myFile)
        {
            try
            {
                ImageSource imageSource;
                InitializeComponent();

                DirEntry = myFile;

                if (MainWindow.User == myFile.FileOwner)
                    imageSource = new BitmapImage(new Uri(Directory.GetCurrentDirectory() + "\\..\\..\\Resorces\\edit.png"));
                else
                    imageSource = new BitmapImage(new Uri(Directory.GetCurrentDirectory() + "\\..\\..\\Resorces\\edit-not-validated.png"));

                imageIO.Source = imageSource;
                nameLabel.Content = myFile.FileName;
                TextBlockFileUse.Text = "size file: " + myFile.FileSize.ToString() + " KB";
                TextBlockFileUseOwner.Text = "Owner:Rabbi " + myFile.FileOwner.ToString() + ".";

                if (myFile.FileOwner != MainWindow.User)
                {
                    //OpenAddOnlyMenuItem.Visibility = Visibility.Collapsed;
                    OpenMenuItem.Visibility = Visibility.Collapsed;
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void OpenMenuItem_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (OpenMenuItemClicked != null)
                {
                    OpenMenuItemClicked(this, EventArgs.Empty);
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void OpenReadOnlyMenuItem_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (OpenReadOnlyMenuItemClicked != null)
                {
                    OpenReadOnlyMenuItemClicked(this, EventArgs.Empty);
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void OpenAddOnlyMenuItem_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (OpenAddOnlyMenuItemClicked != null)
                {
                    OpenAddOnlyMenuItemClicked(this, EventArgs.Empty);
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void DeleteMenuItem_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (DeleteMenuItemClicked != null)
                {
                    DeleteMenuItemClicked(this, EventArgs.Empty);
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }
    }
}
