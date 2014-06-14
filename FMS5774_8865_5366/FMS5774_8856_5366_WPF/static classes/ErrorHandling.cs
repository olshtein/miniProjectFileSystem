using System.Windows;

namespace FMS5774_8856_5366_WPF
{
    static class ErrorHandling
    {
        public static void ShowError(string msg)
        {
            MessageBox.Show(msg, "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
        }
    }
}
