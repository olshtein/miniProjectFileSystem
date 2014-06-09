using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace FMS5774_8856_5366_WPF.Converters
{
    public class ValuePercentageConverter : IValueConverter
    {
        private int part, whole;

        public object Convert(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            if ((int.TryParse(value.ToString(), out part)) && (int.TryParse(parameter.ToString(), out whole)))
                return (float)part / whole * 100;
            return String.Format("{0}/{1}",part,whole);
        }

        public object ConvertBack(object value, Type targetType,
            object parameter, CultureInfo culture)
        {
            if ((int.TryParse(value.ToString(), out part)) && (int.TryParse(parameter.ToString(), out whole)))
                return (float)part / 100 * whole;
            return String.Format("{0}/{1}", part, 100);
        }
    }

}

