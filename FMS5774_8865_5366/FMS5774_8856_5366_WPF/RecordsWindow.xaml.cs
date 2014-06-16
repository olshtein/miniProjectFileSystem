using FMS5774_8856_5366_WPF.RecordsUserControls;
using FMS5774_Cpp_CSharp_Adapter;
using FMS5774_Cpp_CSharp_Adapter.RecordTypes;
using System;
using System.Windows;
using System.Windows.Input;

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

        public int? CurrentRecordNumber
        {
            get { return CurrentRecordIntegerUpDown.Value; }
            set { CurrentRecordIntegerUpDown.Value = value; }
        }

        public RecordsWindow(FCB fcb)
        {
            try
            {
                InitializeComponent();
                FCB = fcb;
                InitRecordFields();
                InitAvailableButtons();

                CurrentRecordNumber = 0;
                InitData();
                MaxRecord = (int)FCB.GetFileDescription().FileSize*(1020/(int)FCB.GetFileDescription().MaxRecSize);
                GoToIntegerUpDown.Maximum = MaxRecord;
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                this.Close();
            }
        }

        private void InitData()
        {
            //FCB.seekRec(0, 0);
//            CurrentSector = 0;
            BackButton.IsEnabled = false;
            NextButton.IsEnabled = true;
            GoToIntegerUpDown.Value = 0;
            GoTo();
            //ReadRecord();
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
                        ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).DisableControls();
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
                if (CurrentRecordNumber == FCB.GetFileDescription().EofRecNr)
                    FCB.writeRec(rec);
                else
                    FCB.updateRec(rec);
                ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).ClearFields();
                BackButton.IsEnabled = true;
                MessageBox.Show("Record Saved", "Info", MessageBoxButton.OK, MessageBoxImage.Information);

               //CurrentSector++;

               //if (CurrentSector > FCB.GetFileDescription().EofRecNr || CurrentSector < 0)
               //{
               //    //FCB.seekRec(0,0);
               //    //CurrentSector = 0;
               //    ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).ClearFields();

               //    BackButton.IsEnabled = false;
               //    NextButton.IsEnabled = true;
               //}
               GoToIntegerUpDown.Value++;
               GoTo();
               //ReadRecord();
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
                if (FCB.IorO() == IOState.IO)
                    FCB.updateRecCancel();
                //InitData();
                GoToIntegerUpDown.Value = 0;
                GoTo();
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
                if (FCB.IorO() == IOState.IO)
                    FCB.updateRecCancel();
                //FCB.seekRec(1, -1);
                //CurrentSector--;
                GoToIntegerUpDown.Value--;
                NextButton.IsEnabled = true;

                if (GoToIntegerUpDown.Value <= 0)
                {
                    GoToIntegerUpDown.Value = 0;
                    BackButton.IsEnabled = false;
                }

                GoTo();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
                BackButton.IsEnabled = false;
            }
        }

        private void ReadRecord()
        {
            ((IRecordUserControl)RecordDetailsStackPanel.Children[0]).ClearFields();

            if (GoToIntegerUpDown.Value != FCB.GetFileDescription().EofRecNr)
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

        private void GoToButton_Click(object sender, RoutedEventArgs e)
        {
            GoTo();
        }

        private void GoTo()
        {
            try
            {
                if (GoToIntegerUpDown.Value > MaxRecord)
                {
                    GoToIntegerUpDown.Value = MaxRecord;
                    throw new Exception("GoTo value too high");
                }

                if (FCB.IorO() == IOState.IO)
                    FCB.updateRecCancel();
                FCB.seekRec(0,(int)GoToIntegerUpDown.Value);
                CurrentRecordNumber = GoToIntegerUpDown.Value;

                //if (CurrentSector == FCB.GetFileDescription().EofRecNr)
                    NextButton.IsEnabled = false;
                //else
                //{
                    if (GoToIntegerUpDown.Value == 0)
                        BackButton.IsEnabled = false;
                    else
                        BackButton.IsEnabled = true;

                    NextButton.IsEnabled = true;
                //}

                ReadRecord();
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
                if (FCB.IorO() == IOState.IO)
                    FCB.updateRecCancel();
                //FCB.seekRec(1, 1);
                //CurrentSector++;
                BackButton.IsEnabled = true;

                if (GoToIntegerUpDown.Value >= FCB.GetFileDescription().EofRecNr)
                    NextButton.IsEnabled = false;
                GoToIntegerUpDown.Value++;
                GoTo();
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
                if (FCB.IorO() == IOState.IO)
                    FCB.updateRecCancel();
                //FCB.seekRec(0, (int)FCB.GetFileDescription().FileAddr - 4 + (int)FCB.GetFileDescription().EofRecNr - 1);
 //               FCB.seekRec(0, (int)FCB.GetFileDescription().EofRecNr - 1);
                GoToIntegerUpDown.Value = (int)FCB.GetFileDescription().EofRecNr;

                GoTo();
                NextButton.IsEnabled = false;
                BackButton.IsEnabled = true;
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void CencelButton_Click(object sender, RoutedEventArgs e)
        {
            FCB.updateRecCancel();
            GoTo();
        }

        private void GoToIntegerUpDown_KeyDown(object sender, KeyEventArgs e)
        {
            if (Keyboard.GetKeyStates(Key.Enter) == KeyStates.Down)
                GoTo();
        }
    }
}
