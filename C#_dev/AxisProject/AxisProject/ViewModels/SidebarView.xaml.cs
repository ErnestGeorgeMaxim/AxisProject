using AxisProject.Models;
using System.Windows;
using System.Windows.Controls;

namespace AxisProject.Views
{
    public partial class SidebarView : Window
    {
        private MainWindowView? _mainWindow;
        private ProgrammerView? _programmerView;
        private Button? _thousandsSeparatorButton;

        public SidebarView()
        {
            InitializeComponent();

            if (StandardMode != null)
                StandardMode.Click += StandardMode_Click;
            if (ProgrammerMode != null)
                ProgrammerMode.Click += ProgrammerMode_Click;
            if (CloseButton != null)
                CloseButton.Click += CloseButton_Click;

            _thousandsSeparatorButton = FindName("ThousandsSeparator") as Button;
            if (_thousandsSeparatorButton != null)
                _thousandsSeparatorButton.Click += ThousandsSeparator_Click;
        }

        public void SetStandardWindow(MainWindowView mainWindow)
        {
            _mainWindow = mainWindow ?? throw new ArgumentNullException(nameof(mainWindow));
            _programmerView = null;
            UpdateModeSelection(isProgrammerMode: false);
            UpdateThousandsSeparatorState();
        }
        public void SetProgrammerWindow(ProgrammerView programmerWindow)
        {
            _programmerView = programmerWindow ?? throw new ArgumentNullException(nameof(programmerWindow));
            _mainWindow = null;
            UpdateModeSelection(isProgrammerMode: true);

            if (_thousandsSeparatorButton != null)
            {
                _thousandsSeparatorButton.Visibility = Visibility.Collapsed;
            }
        }

        private void UpdateThousandsSeparatorState()
        {
            if (_thousandsSeparatorButton != null)
            {
                _thousandsSeparatorButton.Visibility = Visibility.Visible;

                bool isEnabled = SettingsManager.Instance.IsDigitGroupingEnabled;

                _thousandsSeparatorButton.Style = isEnabled ?
                    (Style)FindResource("SelectedModeButtonStyle") :
                    (Style)FindResource("CustomButtonStyle");
            }
        }

        private void ThousandsSeparator_Click(object sender, RoutedEventArgs e)
        {
            if (_mainWindow != null)
            {
                _mainWindow.ToggleThousandsSeparator();

                // Get the current state to update UI
                bool isEnabled = SettingsManager.Instance.IsDigitGroupingEnabled;
                Console.WriteLine($"Digit grouping toggled: {isEnabled}"); // Debug line

                // Update button style based on the current state
                _thousandsSeparatorButton.Style = isEnabled ?
                    (Style)FindResource("SelectedModeButtonStyle") :
                    (Style)FindResource("CustomButtonStyle");
            }
        }

        private void UpdateModeSelection(bool isProgrammerMode)
        {
            if (StandardMode != null && ProgrammerMode != null)
            {
                StandardMode.Style = isProgrammerMode ? (Style)FindResource("CustomButtonStyle") : (Style)FindResource("DisabledModeButtonStyle");
                ProgrammerMode.Style = isProgrammerMode ? (Style)FindResource("DisabledModeButtonStyle") : (Style)FindResource("CustomButtonStyle");
            }
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();

            if (_mainWindow != null)
                _mainWindow.SetSidebarState(false);
            else if (_programmerView != null)
                _programmerView.SetSidebarState(false);
        }

        private void StandardMode_Click(object sender, RoutedEventArgs e)
        {
            if (_programmerView != null)
            {
                try
                {
                    _programmerView.SwitchToStandardMode();
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Error switching to Standard mode: {ex.Message}", "Mode Switch Error",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void ProgrammerMode_Click(object sender, RoutedEventArgs e)
        {
            if (_mainWindow != null)
            {
                try
                {
                    _mainWindow.SwitchToProgrammerMode();
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Error switching to Programmer mode: {ex.Message}", "Mode Switch Error",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        public void PositionRelativeToParent()
        {
            if (_mainWindow != null)
            {
                this.Left = _mainWindow.Left + _mainWindow.Width;
                this.Top = _mainWindow.Top;
            }
            else if (_programmerView != null)
            {
                this.Left = _programmerView.Left + _programmerView.Width;
                this.Top = _programmerView.Top;
            }
        }
    }
}