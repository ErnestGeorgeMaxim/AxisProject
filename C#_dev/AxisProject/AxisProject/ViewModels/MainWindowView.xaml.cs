using AxisProject.Commands;
using AxisProject.Models;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace AxisProject.Views
{
    public partial class MainWindowView : Window
    {
        private Window _sidebarWindow = null!;
        private bool _isSidebarOpen = false;

        private Window _memoryWindow = null!;
        private bool _isMemoryOpen = false;

        private CalculatorModel _calculator;
        private InputHandler _inputHandler;

        public MainWindowView()
        {
            InitializeComponent();
            this.Focusable = true;
            this.Focus();

            _calculator = new CalculatorModel();
            _inputHandler = new InputHandler(DisplayTextBox, _calculator, this);
            DisplayTextBox.Text = _calculator.GetDisplayText();

            InitializeSidebar();
            InitializeMemoryView();

            if (MenuButton != null)
            {
                MenuButton.Click += MenuButton_Click;
            }
            else
            {
                foreach (var child in ButtonGrid.Children)
                {
                    if (child is Button button && button.Content?.ToString() == "☰")
                    {
                        button.Click += MenuButton_Click;
                        break;
                    }
                }
            }

            AttachButtonHandlers();

            this.LocationChanged += MainWindow_LocationChanged;
            this.KeyDown += MainWindow_KeyDown;

            if (SettingsManager.Instance.CalculatorMode == CalculatorMode.Programmer)
            {
                this.Dispatcher.BeginInvoke(new Action(() => SwitchToProgrammerMode()));
            }
        }

        private void MainWindow_KeyDown(object sender, KeyEventArgs e)
        {
            _inputHandler.KeyPressHandler(sender, e);
        }

        private void MainWindow_LocationChanged(object? sender, EventArgs e)
        {
            if (_isSidebarOpen)
                PositionSidebar();
            if (_isMemoryOpen)
                PositionMemoryView();
        }

        private void AttachButtonHandlers()
        {
            foreach (var child in ButtonGrid.Children)
            {
                if (child is Grid grid)
                {
                    foreach (var gridChild in grid.Children)
                    {
                        if (gridChild is Button button && button != MenuButton)
                        {
                            button.Click += (s, e) => _inputHandler.ButtonClickHandler(s, e);
                        }
                    }
                }
                else if (child is Button button && button != MenuButton)
                {
                    button.Click += (s, e) => _inputHandler.ButtonClickHandler(s, e);
                }
            }
        }

        private void InitializeSidebar()
        {
            _sidebarWindow = new SidebarView();
            _sidebarWindow.Width = 300;
            _sidebarWindow.Height = this.Height;
            _sidebarWindow.WindowStyle = WindowStyle.None;
            _sidebarWindow.ResizeMode = ResizeMode.NoResize;
            _sidebarWindow.ShowInTaskbar = false;

            if (_sidebarWindow is SidebarView sidebarView)
            {
                sidebarView.SetStandardWindow(this);
            }
            this.Closed += (s, e) =>
            {
                _sidebarWindow.Close();
            };
            this.ContentRendered += (s, e) =>
            {
                _sidebarWindow.Owner = this;
            };
        }

        private void InitializeMemoryView()
        {
            _memoryWindow = new MemoryView();
            _memoryWindow.Width = 300;
            _memoryWindow.Height = this.Height;
            _memoryWindow.WindowStyle = WindowStyle.None;
            _memoryWindow.ResizeMode = ResizeMode.NoResize;
            _memoryWindow.ShowInTaskbar = false;

            if (_memoryWindow is MemoryView memoryView)
            {
                memoryView.SetMainWindow(this);
            }
            this.Closed += (s, e) =>
            {
                _memoryWindow.Close();
            };
            this.ContentRendered += (s, e) =>
            {
                _memoryWindow.Owner = this;
            };
        }

        private void PositionSidebar()
        {
            _sidebarWindow.Left = this.Left + this.Width;
            _sidebarWindow.Top = this.Top;
        }

        private void PositionMemoryView()
        {
            _memoryWindow.Left = this.Left - _memoryWindow.Width;
            _memoryWindow.Top = this.Top;
        }

        private void MenuButton_Click(object sender, RoutedEventArgs e)
        {
            if (_isSidebarOpen)
            {
                _sidebarWindow.Hide();
            }
            else
            {
                PositionSidebar();
                _sidebarWindow.Show();
            }
            _isSidebarOpen = !_isSidebarOpen;
        }

        public void ToggleMemoryView()
        {
            if (_isMemoryOpen)
            {
                _memoryWindow.Hide();
                _isMemoryOpen = false;
            }
            else
            {
                PositionMemoryView();
                UpdateMemoryViewDisplay();
                _memoryWindow.Show();
                _isMemoryOpen = true;
            }
        }

        public void UpdateMemoryViewDisplay()
        {
            if (_memoryWindow is MemoryView memView)
            {
                memView.UpdateMemoryItems(_calculator.MemoryStackDisplay());
            }
        }

        public void SetSidebarState(bool isOpen)
        {
            _isSidebarOpen = isOpen;
        }

        public void SetMemoryViewState(bool isOpen)
        {
            _isMemoryOpen = isOpen;
        }

        public void SwitchToProgrammerMode()
        {
            // Save calculator mode setting
            SettingsManager.Instance.CalculatorMode = CalculatorMode.Programmer;

            Console.WriteLine($"Saved calculator mode: {SettingsManager.Instance.CalculatorMode}");

            // Create and show the programmer view
            ProgrammerView programmerView = new ProgrammerView();
            programmerView.Show();

            // Close the main window (and associated sidebar and memory view)
            this.Close();
        }

        public void ToggleThousandsSeparator()
        {
            if (_calculator != null)
            {
                _calculator.ToggleDigitGrouping();
                SettingsManager.Instance.IsDigitGroupingEnabled = _calculator.IsDigitGroupingEnabled;
                DisplayTextBox.Text = _calculator.GetDisplayText();
            }
        }

        public CalculatorModel GetCalculator()
        {
            return _calculator;
        }

        private void CopyCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            _calculator.Copy();
        }

        private void CutCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            DisplayTextBox.Text = _calculator.Cut();
        }

        private void PasteCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            _calculator.Paste();
            DisplayTextBox.Text = _calculator.GetDisplayText();
        }

        private void Copy_Click(object sender, RoutedEventArgs e)
        {
            _calculator.Copy();
        }

        private void Cut_Click(object sender, RoutedEventArgs e)
        {
            DisplayTextBox.Text = _calculator.Cut();
        }

        private void Paste_Click(object sender, RoutedEventArgs e)
        {
            _calculator.Paste();
            DisplayTextBox.Text = _calculator.GetDisplayText();
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            _inputHandler.KeyPressHandler(sender, e);
        }
    }
}