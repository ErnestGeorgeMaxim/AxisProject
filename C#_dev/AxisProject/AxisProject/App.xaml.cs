using AxisProject.Models;
using AxisProject.Views;
using System.Windows;

namespace AxisProject
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            try
            {
                // Get calculator mode
                CalculatorMode calculatorMode = SettingsManager.Instance.CalculatorMode;

                // Create the appropriate window based on the saved mode
                Window mainWindow;

                if (calculatorMode == CalculatorMode.Programmer)
                {
                    mainWindow = new ProgrammerView();
                }
                else
                {
                    mainWindow = new MainWindowView();
                }

                // Set as the main window and show it
                this.MainWindow = mainWindow;
                mainWindow.Show();
            }
            catch (Exception ex)
            {
                // If there's an error, just show the standard calculator
                MessageBox.Show($"Error loading settings: {ex.Message}. Starting with standard calculator.",
                               "Settings Error", MessageBoxButton.OK, MessageBoxImage.Warning);

                this.MainWindow = new MainWindowView();
                this.MainWindow.Show();
            }

            // Don't call Shutdown here
        }
    }
}