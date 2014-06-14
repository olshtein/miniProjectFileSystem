using System;
using System.Globalization;
using System.Windows.Data;

namespace FMS5774_8856_5366_WPF.Converters
{
    public class ValuePercentageConverter : IValueConverter
    {
        private int part;

        public object Convert(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            if (int.TryParse(value.ToString(), out part))
                return (float)part / 3200 * 100;
            return String.Format("{0}/{1}",part,3200);
        }

        public object ConvertBack(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            if (int.TryParse(value.ToString(), out part))
                return (float)part / 100 * 3200;
            return String.Format("{0}/{1}", part, 100);
        }
    }

}

