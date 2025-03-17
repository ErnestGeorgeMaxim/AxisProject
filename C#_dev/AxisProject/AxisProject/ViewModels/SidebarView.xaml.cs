using System;
using System.Windows;
using System.Windows.Controls;

namespace AxisProject.Views
{
    public partial class SidebarView : Window
    {
        // References to windows for state synchronization
        private MainWindowView? _mainWindow;
        private ProgrammerView? _programmerView;

        // Button reference for thousands separator toggle
        private Button? _thousandsSeparatorButton;

        public SidebarView()
        {
            InitializeComponent();

            // Add click handlers for the calculator mode buttons
            if (StandardMode != null)
                StandardMode.Click += StandardMode_Click;
            if (ProgrammerMode != null)
                ProgrammerMode.Click += ProgrammerMode_Click;
            if (CloseButton != null)
                CloseButton.Click += CloseButton_Click;

            // Get reference to the thousands separator button and add click handler
            _thousandsSeparatorButton = FindName("ThousandsSeparator") as Button;
            if (_thousandsSeparatorButton != null)
                _thousandsSeparatorButton.Click += ThousandsSeparator_Click;
        }

        // Method to set the main window reference
        public void SetStandardWindow(MainWindowView mainWindow)
        {
            _mainWindow = mainWindow ?? throw new ArgumentNullException(nameof(mainWindow));
            _programmerView = null;

            // Update UI to reflect current mode
            UpdateModeSelection(isProgrammerMode: false);

            // Update thousands separator button state
            UpdateThousandsSeparatorState();
        }

        // Method to set the programmer window reference
        public void SetProgrammerWindow(ProgrammerView programmerWindow)
        {
            _programmerView = programmerWindow ?? throw new ArgumentNullException(nameof(programmerWindow));
            _mainWindow = null;

            // Update UI to reflect current mode
            UpdateModeSelection(isProgrammerMode: true);

            // Update thousands separator button state
            UpdateThousandsSeparatorState();
        }

        // Update the thousands separator button to reflect the current state
        private void UpdateThousandsSeparatorState()
        {
            if (_thousandsSeparatorButton != null)
            {
                bool isEnabled = false;

                if (_mainWindow != null && _mainWindow.GetCalculator() != null)
                {
                    isEnabled = _mainWindow.GetCalculator().IsDigitGroupingEnabled;
                }

                // Update button style based on state
                _thousandsSeparatorButton.Style = isEnabled ?
                    (Style)FindResource("SelectedModeButtonStyle") :
                    (Style)FindResource("CustomButtonStyle");
            }
        }

        // Handle the thousands separator button click
        private void ThousandsSeparator_Click(object sender, RoutedEventArgs e)
        {
            if (_mainWindow != null)
            {
                _mainWindow.ToggleThousandsSeparator();
                UpdateThousandsSeparatorState();
            }
        }

        // Update UI to highlight the current calculator mode
        private void UpdateModeSelection(bool isProgrammerMode)
        {
            if (StandardMode != null && ProgrammerMode != null)
            {
                // Apply styles based on selection
                StandardMode.Style = isProgrammerMode ? (Style)FindResource("CustomButtonStyle") : (Style)FindResource("DisabledModeButtonStyle");
                ProgrammerMode.Style = isProgrammerMode ? (Style)FindResource("DisabledModeButtonStyle") : (Style)FindResource("CustomButtonStyle");
            }
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();

            // Update state in the appropriate window
            if (_mainWindow != null)
                _mainWindow.SetSidebarState(false);
            else if (_programmerView != null)
                _programmerView.SetSidebarState(false);
        }

        private void StandardMode_Click(object sender, RoutedEventArgs e)
        {
            // Only switch modes if we're currently in programmer mode
            if (_programmerView != null)
            {
                try
                {
                    _programmerView.SwitchToStandardMode();
                    // The sidebar will be closed automatically when the programmer window is closed
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
            // Only switch modes if we're currently in standard mode
            if (_mainWindow != null)
            {
                try
                {
                    _mainWindow.SwitchToProgrammerMode();
                    // The sidebar will be closed automatically when the main window is closed
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Error switching to Programmer mode: {ex.Message}", "Mode Switch Error",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Add method to explicitly position the sidebar relative to parent window
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