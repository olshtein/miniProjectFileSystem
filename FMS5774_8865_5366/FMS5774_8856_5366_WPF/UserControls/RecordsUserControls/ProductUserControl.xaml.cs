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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace FMS5774_8856_5366_WPF.RecordsUserControls
{
    /// <summary>
    /// Interaction logic for ProductUserControl.xaml
    /// </summary>
    public partial class ProductUserControl : UserControl, IRecordUserControl
    {
        public ProductUserControl()
        {
            InitializeComponent();
            ClearFields();
        }

        public IRecord Record
        {
            get { return new Product(Barcode, Manufacturer, Name, Suplier, (float)Price); }
            set
            {
                if (value.GetType() == typeof(Product))
                {
                    Product product = (Product)value;
                    Barcode = product.barcode;
                    Manufacturer = product.manufacturer;
                    Name = product.nameProduct;
                    Suplier = product.supplier;
                    Price = product.price;
                }
            }
        }

        public string Barcode
        {
            get { return barcodeTextBox.Text; }
            set { barcodeTextBox.Text = value; }
        }
        public string Manufacturer
        {
            get { return manufacturerTextBox.Text; }
            set { manufacturerTextBox.Text = value; }
        }
        public string Name
        {
            get { return nameTextBox.Text; }
            set { nameTextBox.Text = value; }
        }
        public string Suplier
        {
            get { return suplierTextBox.Text; }
            set { suplierTextBox.Text = value; }
        }
        public double Price
        {
            get { return (double)priceDoubleUpDown.Value; }
            set { priceDoubleUpDown.Value = value; }
        }

        public void ClearFields()
        {
            Barcode = "";
            Manufacturer = "";
            Name = "";
            Suplier = "";
            Price = 0;
        }
    }
}
