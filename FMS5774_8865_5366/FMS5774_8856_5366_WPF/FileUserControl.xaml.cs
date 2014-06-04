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
        public FileUserControl(DirEntry myFile)
        {
            ImageSource imageSource;
            if (MainWindow.User==myFile.FileOwner)
                imageSource = new BitmapImage(new Uri(Directory.GetCurrentDirectory() + "\\..\\..\\Resorces\\edit.png"));
            else
                imageSource = new BitmapImage(new Uri(Directory.GetCurrentDirectory() + "\\..\\..\\Resorces\\edit-not-validated.png"));

            imageIO.Source = imageSource;
            InitializeComponent();
        }
    }
}
