using FMS5774_Cpp_CSharp_Adapter;
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

namespace FMS5774_8856_5366_WPF
{
    /// <summary>
    /// Interaction logic for FileWindow.xaml
    /// </summary>
    public partial class FileWindow : Window
    {
         List<DirEntry> allFile;
         private Disk dsk;
         private List<Window> subwindows;

         public List<FCB> FCBList { get; set; }

        public FileWindow(Disk dsk)
        {
            try
            {
                this.dsk = dsk;
                allFile = dsk.GetDirRoot();
                FCBList = new List<FCB>();
                subwindows = new List<Window>();

                InitializeComponent();
                InitializeFileList();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }
        private void InitializeFileList()
        {
            try
            {
                ClearFileList();
                allFile = dsk.GetDirRoot();
                foreach (DirEntry file in allFile)
                {
                    if (file.FileName != "")
                    {
                        FileUserControl fuc = new FileUserControl(file);
                        FilesWrapPanel.Children.Insert(0, fuc);

                        fuc.MouseDoubleClick += fuc_MouseDoubleClick;
                        fuc.OpenMenuItemClicked += fuc_OpenMenuItemClicked;
                        fuc.OpenReadOnlyMenuItemClicked += fuc_OpenReadOnlyMenuItemClicked;
                        fuc.OpenAddOnlyMenuItemClicked += fuc_OpenAddOnlyMenuItemClicked;
                    }
                }
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        void fuc_OpenAddOnlyMenuItemClicked(object sender, EventArgs e)
        {
            try
            {
                FileUserControl fuc = (FileUserControl)sender;

                OpenFileAddOnly(fuc);
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        void fuc_OpenReadOnlyMenuItemClicked(object sender, EventArgs e)
        {
            try
            {
                FileUserControl fuc = (FileUserControl)sender;

                OpenFileReadOnly(fuc);
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void OpenFileReadOnly(FileUserControl fuc)
        {

            try
            {
                if ((from i in FCBList
                     where i.GetFileDescription().FileName == fuc.DirEntry.FileName
                     select i).AsParallel().FirstOrDefault() != null)
                    return;// create only one FCB.
                FCBList.Add(dsk.Openfile(fuc.DirEntry.FileName, MainWindow.User, "O"));

                RecordsWindow rw = new RecordsWindow(FCBList[0]);
                subwindows.Add(rw);
                rw.Show();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        void fuc_OpenMenuItemClicked(object sender, EventArgs e)
        {
            try
            {
                FileUserControl fuc = (FileUserControl)sender;

                OpenFileAddOnly(fuc);
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void OpenFileAddOnly(FileUserControl fuc)
        {
            try
            {
                if ((from i in FCBList
                     where i.GetFileDescription().FileName == fuc.DirEntry.FileName
                     select i).AsParallel().FirstOrDefault() != null)
                    return;// create only one FCB.
                FCBList.Add(dsk.Openfile(fuc.DirEntry.FileName, MainWindow.User, "E"));

                RecordsWindow rw = new RecordsWindow(FCBList[0]);
                subwindows.Add(rw);
                rw.Show();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void ClearFileList()
        {
            try
            {
                FilesWrapPanel.Children.RemoveRange(0, FilesWrapPanel.Children.Count - 1); // delete all fuc, leave button.
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        void fuc_MouseDoubleClick(object sender, EventArgs e)
        {
            try
            {
                FileUserControl fuc = (FileUserControl)sender;

                if (fuc.DirEntry.FileOwner == MainWindow.User)
                    OpenFile(fuc);
                else
                    OpenFileReadOnly(fuc);
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void OpenFile(FileUserControl fuc)
        {
            try
            {
                if ((from i in FCBList
                     where i.GetFileDescription().FileName == fuc.DirEntry.FileName
                     select i).AsParallel().FirstOrDefault() != null)
                    return;// create only one FCB.
                FCBList.Add(dsk.Openfile(fuc.DirEntry.FileName, MainWindow.User, "IO"));

                RecordsWindow rw = new RecordsWindow(FCBList[0]);
                subwindows.Add(rw);
                rw.Show();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }
        private void New_File_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                CreateFile();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                this.Close();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void CreateFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                CreateFile();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        private void CreateFile()
        {
            try
            {
                CreateFile cf = new CreateFile(dsk);
                subwindows.Add(cf);
                cf.Show();
                cf.Closed += cf_Closed;
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        void cf_Closed(object sender, EventArgs e)
        {
            try
            {

                InitializeFileList();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }

        void Window_Closed(object sender, EventArgs e)
        {
            try
            {
                foreach (Window win in subwindows)
                    win.Close();
            }
            catch (Exception exp)
            {
                ErrorHandling.ShowError(exp.Message);
            }
        }
    }
}
