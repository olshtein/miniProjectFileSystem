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
    /// Interaction logic for CreateFile.xaml
    /// </summary>
    public partial class CreateFile : Window
    {
        Disk myDisk;
        public CreateFile(Disk my)
        {
            myDisk = my;

            InitializeComponent();
            typeRec.ItemsSource = new List<string> { "employee", "store", "Product" };

        }


        private void OK_Click(object sender, RoutedEventArgs e)
        {
            uint sizeClass=0;
            uint sizeOffset=4;
           switch( typeRec.SelectedItem.ToString())
           {
               case "employee":
                   sizeClass=Employee.size();
                   sizeOffset =  Employee.sizeKey();
                   break;
               case "store":
                   sizeClass=store.size();
                   sizeOffset = store.sizeKey();
                   break;
               case "Product":
                   sizeClass=Product.size();
                   sizeOffset =  Product.sizeKey();
                    break;
               default:
                   break;

           }

           myDisk.Createfile(this.nameRec.Text, MainWindow.User, "F", sizeClass, Convert.ToUInt32(Math.Ceiling((Double)(numRec.Value * sizeClass) / 1020)), "I", 0, sizeOffset);
            //                d.Createfile("disk1", "meir", "F", 50, 2, "I", 0);
        }

        private void cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

    }
}
