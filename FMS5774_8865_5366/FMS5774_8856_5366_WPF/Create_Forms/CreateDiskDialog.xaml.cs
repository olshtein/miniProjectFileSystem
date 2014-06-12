using System;
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
using System.Windows.Shapes;

namespace FMS5774_8856_5366_WPF.CreateDisk
{
    /// <summary>
    /// Interaction logic for CreateDiskDialog.xaml
    /// </summary>
    public partial class CreateDiskDialog : Window
    {
        public string DiskName { get; set; }

        public CreateDiskDialog()
        {
            InitializeComponent();
        }

        void OkButton_Click(object sender, RoutedEventArgs e)
        {
            string msg;
            // Don't accept the dialog box if there is invalid data 
            if ((msg = IsValid()) != null)
            {
                MessageBox.Show(msg, "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            
            DialogResult = true;
        }

        private string IsValid()
        {
            // Is length in range? 
            if ((DiskNameTextBox.Text.Length < 1) || (DiskNameTextBox.Text.Length > 10))
            {
                return "Length of name must be between 1 and 10.";
            }

            // Is name all letters or numbers (and spaces)?
            foreach (char l in DiskNameTextBox.Text)
            {
                if ((l < 'a' || l > 'z') && (l < 'A' || l > 'Z') && (l < '0' || l > '9') && (l != ' '))
                    return "name must be of letters 'a-z' or 'A-Z' or space.";
            }
            return null;
        }

        private void DiskNameTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            DiskName = DiskNameTextBox.Text;
        }
    }
}