using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Lab_MAP_02
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            (DataContext as User).Username = "Ion";
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            User u = new User()
            {
                Username = textBoxUsername.Text,
                Password = textBoxPassword.Text
            };
            (DataContext as UserDataContext).Users.Add(u);
            (DataContext as UserDataContext).CurrentUser = u;
        }
    }
}