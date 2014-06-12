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
        }

        public Record Record
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

        public string Barcode { get; set; }
        public string Manufacturer { get; set; }
        public string Name { get; set; }
        public string Suplier { get; set; }
        public double Price { get; set; }
    }
}
