using FMS5774_Cpp_CSharp_Adapter;
using FMS5774_Cpp_CSharp_Adapter.RecordTypes;
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


namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for CreateFile.xaml
    /// </summary>
    public partial class CreateFile : Window
    {
        Disk myDisk;
        uint sizeClass = 0;
        uint sizeOffset = 4;
        public CreateFile(Disk my)
        {
            try
            {
                myDisk = my;

                InitializeComponent();
                typeRec.ItemsSource = new List<string> { "employee", "store", "Product" };
                typeRec.SelectedIndex = 0;
                ChangeMaxRecords();
            }
            catch (Exception exp)
            {               
                ErrorHandling.ShowError(exp.Message);
            }

        }


        private void OK_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (nameRec.Text == "")
                {
                    throw new Exception("Please enter a name");
                }
                uint sizeClass = 0;
                uint sizeOffset = 4;
                switch (typeRec.SelectedItem.ToString())
                {
                    case "employee":
                        sizeClass = Employee.size();
                        sizeOffset = Employee.sizeKey();
                        break;
                    case "store":
                        sizeClass = Store.size();
                        sizeOffset = Store.sizeKey();
                        break;
                    case "Product":
                        sizeClass = Product.size();
                        sizeOffset = Product.sizeKey();
                        break;
                    default:
                        break;

                }

                myDisk.Createfile(this.nameRec.Text, MainWindow.User, "F", sizeClass, Convert.ToUInt32(Math.Ceiling((Double)(numRec.Value * sizeClass) / 1020)), "I", 0, sizeOffset);
                this.Close();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void cancel_Click(object sender, RoutedEventArgs e)
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
        private void sizeRec()
        {
            switch (typeRec.SelectedItem.ToString())
            {
                case "employee":
                    sizeClass = Employee.size();
                    sizeOffset = Employee.sizeKey();
                    break;
                case "store":
                    sizeClass = Store.size();
                    sizeOffset = Store.sizeKey();
                    break;
                case "Product":
                    sizeClass = Product.size();
                    sizeOffset = Product.sizeKey();
                    break;
                default:
                    break;

            }
        }

        private void TypeRec_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ChangeMaxRecords();
        }

        private void ChangeMaxRecords()
        {
            sizeRec();
            numRec.Maximum = (int?)(myDisk.Howmuchempty(myDisk.myDiskPointer) * (1020 / sizeClass));
        }

    }
}
