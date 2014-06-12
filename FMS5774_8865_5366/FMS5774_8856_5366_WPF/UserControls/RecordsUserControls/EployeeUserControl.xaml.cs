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
    /// Interaction logic for EployeeUserControl.xaml
    /// </summary>
    public partial class EployeeUserControl : UserControl, IRecordUserControl
    {
        public EployeeUserControl()
        {
            InitializeComponent();
        }

        public IRecord Record
        {
            get { return new Employee(ID, LastName, FirstName, (float)Salary, Seniority); }
            set
            {
                if (value.GetType() == typeof(Product))
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

        public string ID { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public double Salary { get; set; }
        public int Seniority { get; set; }
    }
}
