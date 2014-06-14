using FMS5774_Cpp_CSharp_Adapter.RecordTypes;
using System.Windows.Controls;

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

        public void DisableControls()
        {
            nameTextBox.IsEnabled = false;
            phoneTextBox.IsEnabled = false;
            addressTextBox.IsEnabled = false;
            cityTextBox.IsEnabled = false;
        }

        public string Name
        {
            get { return nameTextBox.Text; }
            set { nameTextBox.Text = value; }
        }
        public string PhoneNumber
        {
            get { return phoneTextBox.Text; }
            set { phoneTextBox.Text = value; }
        }
        public string Address
        {
            get { return addressTextBox.Text; }
            set { addressTextBox.Text = value; }
        }
        public string City
        {
            get { return cityTextBox.Text; }
            set { cityTextBox.Text = value; }
        }

        public StoreUserControl()
        {
            InitializeComponent();
            ClearFields();
        }

        public void ClearFields()
        {
            Name = "";
            PhoneNumber = "";
            Address = "";
            City = "";
        }
    }
}
