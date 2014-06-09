﻿using FMS5774_Cpp_CSharp_Adapter;
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

        public FileWindow(Disk myDisk)
        {

            allFile = myDisk.GetDirRoot();

            InitializeComponent();
            InitializeFileList();
        }
        private void InitializeFileList()
        {
            foreach (DirEntry file in allFile)
            {
                if (file.FileName != "")
                {
                    FileUserControl fuc = new FileUserControl(file);
                    FilesWrapPanel.Children.Insert(0, fuc);
                }
            }
        }
        private void New_File_Click(object sender, RoutedEventArgs e)
        {

        }

        private void open_File_Click(object sender, RoutedEventArgs e)
        {

        }

        private void delete_File(object sender, RoutedEventArgs e)
        {

        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {

        }

        private void New_Files_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
