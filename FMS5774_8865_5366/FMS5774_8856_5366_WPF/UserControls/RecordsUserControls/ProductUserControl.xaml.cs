using FMS5774_Cpp_CSharp_Adapter.RecordTypes;
using System.Windows.Controls;

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

        public void DisableControls()
        {
            barcodeTextBox.IsEnabled = false;
            manufacturerTextBox.IsEnabled = false;
            nameTextBox.IsEnabled = false;
            suplierTextBox.IsEnabled = false;
            priceDoubleUpDown.IsEnabled = false;
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
