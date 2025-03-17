using AxisProject.Commands;
using AxisProject.Models;
using AxisProject.Views;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace AxisProject.Views
{
    public partial class MainWindowView : Window
    {
        private Window _sidebarWindow = null!;
        private bool _isSidebarOpen = false;

        // Memory view fields
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

            // Pass 'this' so the input handler can call ToggleMemoryView and update the memory view.
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

        // Toggle the memory view.
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
                UpdateMemoryViewDisplay(); // Update display when opening.
                _memoryWindow.Show();
                _isMemoryOpen = true;
            }
        }

        // Called by InputHandler after a memory operation to update the memory view.
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
            // Create and show the programmer view
            ProgrammerView programmerView = new ProgrammerView();
            programmerView.Show();

            // Close the main window (and associated sidebar and memory view)
            this.Close();
        }

        // Add this method to MainWindowView class
        public void ToggleThousandsSeparator()
        {
            if (_calculator != null)
            {
                _calculator.ToggleDigitGrouping();
                DisplayTextBox.Text = _calculator.GetDisplayText();
            }
        }

        // Add this method to MainWindowView class
        public CalculatorModel GetCalculator()
        {
            return _calculator;
        }
    }
}
