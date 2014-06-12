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
using FMS5774_Cpp_CSharp_Adapter;
using FMS5774_Cpp_CSharp_Adapter.RecordTypes;

namespace FMS5774_8856_5366_WPF.RecordsUserControls
{
    /// <summary>
    /// Interaction logic for StoreUserControl.xaml
    /// </summary>
    public partial class StoreUserControl : UserControl, IRecordUserControl
    {
        public IRecord Record
        {
            get { return new Store(PhoneNumber, Name, Address, City); }
            set
            {
                if (value.GetType() == typeof(Store))
                {
                    Store store = (Store)value;
                    Name = store.name;
                    PhoneNumber = store.phone;
                    Address = store.address;
                    City = store.city;
                }
            }
        }

        public string Name { get; set; }
        public string PhoneNumber { get; set; }
        public string Address { get; set; }
        public string City { get; set; }

        public StoreUserControl()
        {
            InitializeComponent();
        }
    }
}
