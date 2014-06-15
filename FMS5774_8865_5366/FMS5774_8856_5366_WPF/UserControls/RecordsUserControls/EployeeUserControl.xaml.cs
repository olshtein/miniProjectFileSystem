using FMS5774_Cpp_CSharp_Adapter.RecordTypes;
using System.Windows.Controls;

namespace FMS5774_8856_5366_WPF.RecordsUserControls
{
    /// <summary>
    /// Interaction logic for EployeeUserControl.xaml
    /// </summary>
    public partial class EployeeUserControl : UserControl, IRecordUserControl
    {
        public EployeeUserControl()
        {
            InitializeComponent();
            ClearFields();
        }

        public IRecord Record
        {
            get { return new Employee(ID, LastName, FirstName, (float)Salary, Seniority); }
            set
            {
                if (value.GetType() == typeof(Employee))
                {
                    Employee employee = (Employee)value;
                    ID = employee.ID;
                    LastName = employee.lestName;
                    FirstName = employee.firstName;
                    Salary = employee.salary;
                    Seniority = employee.seniority;
                }
            }
        }

        public void DisableControls()
        {
            idTextBox.IsEnabled = false;
            firstNameTextBox.IsEnabled = false;
            lastNameTextBox.IsEnabled = false;
            salaryDoubleUpDown.IsEnabled = false;
            seniorityIntegerUpDown.IsEnabled = false;
        }

        public string ID
        {
            get { return idTextBox.Text; }
            set { idTextBox.Text = value; }
        }

        public string FirstName
        {
            get { return firstNameTextBox.Text; }
            set { firstNameTextBox.Text = value; }
        }

        public string LastName
        {
            get { return lastNameTextBox.Text; }
            set { lastNameTextBox.Text = value; }
        }
        public double Salary
        {
            get { return (double)salaryDoubleUpDown.Value; }
            set { salaryDoubleUpDown.Value = value; }
        }
        public int Seniority
        {
            get { return (int)seniorityIntegerUpDown.Value; }
            set { seniorityIntegerUpDown.Value = value; }
        }

        public void ClearFields()
        {
            ID = "";
            FirstName = "";
            LastName = "";
            Salary = 0;
            Seniority = 0;
        }
    }
}
