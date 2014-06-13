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

using FMS5774_Cpp_CSharp_Adapter;
using FMS5774_Cpp_CSharp_Adapter.RecordTypes;
using FMS5774_8856_5366_WPF.RecordsUserControls;

namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for RecordsWindow.xaml
    /// </summary>
    public partial class RecordsWindow : Window
    {
        public FCB FCB { get; set; }
        public IRecord CurrentRecord { get; set; }
        public int MaxRecord { get; set; }

        public RecordsWindow(FCB fcb)
        {
            try
            {
                InitializeComponent();
                FCB = fcb;
                InitRecordFields();
                InitAvailableButtons();
                InitData();
                MaxRecord = (int)FCB.GetFileDescription().FileSize-2;
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                this.Close();
            }
        }

        private void InitData()
        {
            switch (FCB.IorO())
            {
                case IOState.IO:
                    FCB.seekRec(FCB.GetFileDescription().FileAddr - 4, 0);
                    BackButton.IsEnabled = false;
                    NextButton.IsEnabled = true;

                    if (IsStore())
                    {
                        Store temp = new Store();
                        FCB.readRec(temp, 1);
                        ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                    }
                    else if (IsProduct())
                    {
                        Product temp = new Product();
                        FCB.readRec(temp, 1);
                        ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                    }
                    else if (IsEmployee())
                    {
                        Employee temp = new Employee();
                        FCB.readRec(temp, 1);
                        ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                    }
                    break;
                case IOState.O:
                    FCB.seekRec(FCB.GetFileDescription().FileAddr - 4, 0);
                    BackButton.IsEnabled = false;
                    NextButton.IsEnabled = true;

                    if (IsStore())
                    {
                        Store temp = new Store();
                        FCB.readRec(temp);
                        ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                    }
                    else if (IsProduct())
                    {
                        Product temp = new Product();
                        FCB.readRec(temp);
                        ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                    }
                    else if (IsEmployee())
                    {
                        Employee temp = new Employee();
                        FCB.readRec(temp);
                        ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                    }
                    break;
                //case IOState.E:
                //    FCB.seekRec(2, 1);
                //    break;
                default:
                    throw new Exception("Unknown format to read/write from file.");
            }
        }

        private void InitAvailableButtons()
        {
            try
            {
                switch (FCB.IorO())
                {
                    case IOState.IO:
                        SaveButton.IsEnabled = true;
                        CencelButton.IsEnabled = true;
                        break;
                    case IOState.O:
                        break;
                    case IOState.E:
                        AddButton.IsEnabled = true;
                        CencelButton.IsEnabled = true;

                        LastButton.IsEnabled = false;
                        BackButton.IsEnabled = false;
                        GoToButton.IsEnabled = false;
                        GoToIntegerUpDown.IsEnabled = false;
                        NextButton.IsEnabled = false;
                        FirstButton.IsEnabled = false;
                        break;
                    default:
                        throw new Exception("Unknown format to read/write from file.");
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                this.Close();
            }
        }

        private void InitRecordFields()
        {
            try
            {
                //create right record type
                if (IsEmployee())
                {
                    RecordDetailsStackPanel.Children.Add(new EployeeUserControl());
                }

                else if (IsStore())
                {
                    RecordDetailsStackPanel.Children.Add(new StoreUserControl());
                }

                else if (IsProduct())
                {
                    RecordDetailsStackPanel.Children.Add(new ProductUserControl());
                }
                else
                    throw new Exception("Record type unsupported.");
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                this.Close();
            }
        }

        private bool IsProduct()
        {
            return FCB.GetFileDescription().ActualRecSize == Product.size();
        }

        private bool IsStore()
        {
            return FCB.GetFileDescription().ActualRecSize == Store.size();
        }

        private bool IsEmployee()
        {
            return FCB.GetFileDescription().ActualRecSize == Employee.size();
        }

        private void SaveButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                IRecord rec = ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record;
                FCB.updateRec(rec);
                ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).ClearFields();
                BackButton.IsEnabled = true;
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                IRecord rec = ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record;
                FCB.writeRec(rec);
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void FirstButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                FCB.updateRecCancel();
                InitData();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }

        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                FCB.updateRecCancel();
                FCB.seekRec(1, -1);
                NextButton.IsEnabled = true;

                switch (FCB.IorO())
                {
                    case IOState.IO:
                        if (IsStore())
                        {
                            Store temp = new Store();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsProduct())
                        {
                            Product temp = new Product();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsEmployee())
                        {
                            Employee temp = new Employee();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        break;
                    case IOState.O:
                        if (IsStore())
                        {
                            Store temp = new Store();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsProduct())
                        {
                            Product temp = new Product();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsEmployee())
                        {
                            Employee temp = new Employee();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        break;
                    default:
                        throw new Exception("Unknown format to read/write from file.");
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                BackButton.IsEnabled = false;
            }
        }

        private void GoToButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (GoToIntegerUpDown.Value > MaxRecord)
                {
                    GoToIntegerUpDown.Value = MaxRecord;
                    throw new Exception("GoTo value too high");
                }
                FCB.updateRecCancel();
                FCB.seekRec(FCB.GetFileDescription().FileAddr - 4, (int)GoToIntegerUpDown.Value);
                BackButton.IsEnabled = true;
                NextButton.IsEnabled = true;

                switch (FCB.IorO())
                {
                    case IOState.IO:
                        if (IsStore())
                        {
                            Store temp = new Store();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsProduct())
                        {
                            Product temp = new Product();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsEmployee())
                        {
                            Employee temp = new Employee();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        break;
                    case IOState.O:
                        if (IsStore())
                        {
                            Store temp = new Store();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsProduct())
                        {
                            Product temp = new Product();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsEmployee())
                        {
                            Employee temp = new Employee();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        break;
                    default:
                        throw new Exception("Unknown format to read/write from file.");
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void NextButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                FCB.updateRecCancel();
                FCB.seekRec(1, 1);
                BackButton.IsEnabled = true;

                switch (FCB.IorO())
                {
                    case IOState.IO:
                        if (IsStore())
                        {
                            Store temp = new Store();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsProduct())
                        {
                            Product temp = new Product();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsEmployee())
                        {
                            Employee temp = new Employee();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        break;
                    case IOState.O:
                        if (IsStore())
                        {
                            Store temp = new Store();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsProduct())
                        {
                            Product temp = new Product();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsEmployee())
                        {
                            Employee temp = new Employee();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        break;
                    default:
                        throw new Exception("Unknown format to read/write from file.");
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                NextButton.IsEnabled = false;
            }
        }

        private void LastButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                FCB.updateRecCancel();
                FCB.seekRec(2, 0);
                NextButton.IsEnabled = false;
                BackButton.IsEnabled = true;

                switch (FCB.IorO())
                {
                    case IOState.IO:
                        if (IsStore())
                        {
                            Store temp = new Store();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsProduct())
                        {
                            Product temp = new Product();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsEmployee())
                        {
                            Employee temp = new Employee();
                            FCB.readRec(temp, 1);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        break;
                    case IOState.O:
                        if (IsStore())
                        {
                            Store temp = new Store();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsProduct())
                        {
                            Product temp = new Product();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        else if (IsEmployee())
                        {
                            Employee temp = new Employee();
                            FCB.readRec(temp);
                            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).Record = temp;
                        }
                        break;
                    default:
                        throw new Exception("Unknown format to read/write from file.");
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }
    }
}
