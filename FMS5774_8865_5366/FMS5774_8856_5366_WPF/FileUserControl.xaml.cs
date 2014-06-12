using FMS5774_Cpp_CSharp_Adapter;
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

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

                if (myFile.FileOwner != MainWindow.User)
                {
                    OpenAddOnlyMenuItem.Visibility = Visibility.Collapsed;
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
    }
}
