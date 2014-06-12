using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace FMS5774_8856_5366_WPF
{
    class ErrorHandling
    {
        public static void ShowError(string msg)
        {
            MessageBox.Show(msg, "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
        }
    }
}
