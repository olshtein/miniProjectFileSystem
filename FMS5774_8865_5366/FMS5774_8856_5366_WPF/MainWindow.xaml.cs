using System.Windows;
using System.Windows.Controls;

namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            FMS5774_Cpp_CSharp_Adapter_Test.cppToCsharpAdapter adapter;

            InitializeComponent();
            InitializeUsersList();
        }

        private void InitializeUsersList()
        {
            //get user names from file
            string filePath = System.IO.Directory.GetCurrentDirectory() + "\\..\\..\\Resorces\\Users.txt";
            string[] usersArr = System.IO.File.ReadAllLines(filePath);

            //make radio buttons for each user
            RadioButton[] radioButtons = new RadioButton[usersArr.Length];
            for (int i = 0; i < usersArr.Length; i++)
                radioButtons[i] = new RadioButton { Content = usersArr[i], IsChecked = false, GroupName="users"};

            // make first radio button default if exist.
            if (radioButtons.Length > 0)
                radioButtons[0].IsChecked = true;

            //bind the radio buttons as the items for the 'chage user' menu.
            this.changeUserMenuItem.ItemsSource = radioButtons;
        }

        private void New_Disk_Click(object sender, RoutedEventArgs e)
        {
        }

        private void Mount_Disk_Click(object sender, RoutedEventArgs e)
        {
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
        }
    }
}
