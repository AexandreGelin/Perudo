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

namespace Perudo_UI.View
{
    /// <summary>
    /// Interaction logic for WaitingScreen.xaml
    /// </summary>
    public partial class WaitingScreen : Window
    {
        public WaitingScreen()
        {
            InitializeComponent();
        }

        private void Button_Play_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Return_Click(object sender, RoutedEventArgs e)
        {
            MainWindow window1 = new MainWindow();
            // window1.Show(); // Win10 tablet in tablet mode, use this, when sub Window is closed, the main window will be covered by the Start menu.
            window1.ShowDialog();
            this.Close();
        }
    }
}
