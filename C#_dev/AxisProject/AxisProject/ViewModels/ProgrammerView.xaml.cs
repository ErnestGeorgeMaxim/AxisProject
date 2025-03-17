using AxisProject.Commands;
using AxisProject.Models;
using AxisProject.Views;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;

namespace AxisProject.Views
{
    public partial class ProgrammerView : Window
    {
        private Window _sidebarWindow = null!;
        private bool _isSidebarOpen = false;

        // Memory view fields
        private Window _memoryWindow = null!;
        private bool _isMemoryOpen = false;

        // Change these types to the programmer versions
        private ProgrammerCalculatorModel _calculator;
        private InputHandlerProgrammer _inputHandler;

        public ProgrammerView()
        {
            InitializeComponent();

            this.Focusable = true;
            this.Focus();

            // Create an instance of ProgrammerCalculatorModel
            _calculator = new ProgrammerCalculatorModel();

            // Use InputHandlerProgrammer
            _inputHandler = new InputHandlerProgrammer(DisplayTextBox, _calculator, this);

            DisplayTextBox.Text = _calculator.GetDisplayText();

            // Add number representation display
            InitializeNumberSystemDisplays();

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

            // Set click handlers for the number system buttons
            SetNumberSystemButtonHandlers();

            AttachButtonHandlers();

            // Update button states for initial number system
            _inputHandler.UpdateButtonStates();

            this.LocationChanged += ProgrammerView_LocationChanged;
            this.KeyDown += ProgrammerView_KeyDown;
        }

        private void InitializeNumberSystemDisplays()
        {
            // Create a StackPanel for number representations
            StackPanel representationsPanel = new StackPanel
            {
                Orientation = Orientation.Vertical,
                Margin = new Thickness(10, 212, 10, 0),
                VerticalAlignment = VerticalAlignment.Top,
                HorizontalAlignment = HorizontalAlignment.Stretch
            };

            // Add the StackPanel to the main grid
            ButtonGrid.Children.Add(representationsPanel);

            // Initial update of displays
            UpdateNumberRepresentations();
        }

        private TextBlock CreateNumberSystemDisplay(string prefix, string accentColor)
        {
            var textBlock = new TextBlock
            {
                Foreground = new SolidColorBrush(Colors.White),
                FontSize = 14,
                Margin = new Thickness(0, 2, 0, 2),
                TextWrapping = TextWrapping.Wrap
            };

            // Create the content with accent color for the prefix
            var prefixRun = new Run(prefix + ": ")
            {
                Foreground = (SolidColorBrush)new BrushConverter().ConvertFrom(accentColor)
            };

            textBlock.Inlines.Add(prefixRun);
            textBlock.Inlines.Add(new Run("0"));

            return textBlock;
        }

        private void UpdateNumberRepresentations()
        {
            // Get the values in different number systems
            string hexValue = _calculator.GetHexRepresentation();
            string decValue = _calculator.CurrentInput;
            string octValue = _calculator.GetOctalRepresentation();
            string binValue = _calculator.GetBinaryRepresentation();

            // Format the binary value for better readability
            string formattedBinValue = FormatBinaryValue(binValue);
        }

        private void UpdateNumberSystemInline(TextBlock textBlock, string prefix, string value)
        {
            // Clear existing inlines and rebuild
            textBlock.Inlines.Clear();
            var prefixRun = new Run(prefix)
            {
                Foreground = (SolidColorBrush)new BrushConverter().ConvertFrom("#FF9500")
            };
            textBlock.Inlines.Add(prefixRun);
            textBlock.Inlines.Add(new Run(value));
        }

        private string FormatBinaryValue(string binValue)
        {
            // Group binary digits for better readability
            string result = "";
            for (int i = 0; i < binValue.Length; i++)
            {
                result += binValue[i];
                if ((i + 1) % 4 == 0 && i < binValue.Length - 1)
                    result += " ";
            }
            return result;
        }

        private void SetNumberSystemButtonHandlers()
        {
            foreach (var child in ButtonGrid.Children)
            {
                if (child is Button button)
                {
                    switch (button.Content?.ToString())
                    {
                        case "HEX":
                            button.Click += (s, e) => SwitchNumberSystem(NumberSystem.HEX);
                            break;
                        case "DEC":
                            button.Click += (s, e) => SwitchNumberSystem(NumberSystem.DEC);
                            break;
                        case "OCT":
                            button.Click += (s, e) => SwitchNumberSystem(NumberSystem.OCT);
                            break;
                        case "BIN":
                            button.Click += (s, e) => SwitchNumberSystem(NumberSystem.BIN);
                            break;
                    }
                }
            }
        }

        private void SwitchNumberSystem(NumberSystem system)
        {
            _calculator.ChangeNumberSystem(system);

            // Update the button states to enable/disable based on the new number system
            _inputHandler.UpdateButtonStates();

            // Update display text
            DisplayTextBox.Text = _calculator.GetDisplayText();

            // Update number representations
            UpdateNumberRepresentations();

            // Visually indicate which number system button is active
            HighlightActiveNumberSystemButton(system);
        }

        private void HighlightActiveNumberSystemButton(NumberSystem system)
        {
            // Find the number system buttons and update their appearance
            foreach (var child in ButtonGrid.Children)
            {
                if (child is Button button)
                {
                    string? content = button.Content?.ToString();
                    if (content == null) continue;

                    bool isActiveSystem = false;

                    // Check if this button is for the active system
                    switch (content)
                    {
                        case "HEX": isActiveSystem = system == NumberSystem.HEX; break;
                        case "DEC": isActiveSystem = system == NumberSystem.DEC; break;
                        case "OCT": isActiveSystem = system == NumberSystem.OCT; break;
                        case "BIN": isActiveSystem = system == NumberSystem.BIN; break;
                        default: continue; // Skip other buttons
                    }

                    // Change the appearance of the button based on whether it's active
                    if (isActiveSystem)
                    {
                        button.Foreground = new SolidColorBrush(Colors.White);
                        button.Background = (SolidColorBrush)new BrushConverter().ConvertFrom("#FF9500");
                    }
                    else
                    {
                        button.Foreground = (SolidColorBrush)new BrushConverter().ConvertFrom("#FF9500");
                        button.Background = new SolidColorBrush(Colors.Black);
                    }
                }
            }
        }

        private void ProgrammerView_KeyDown(object sender, KeyEventArgs e)
        {
            _inputHandler.KeyPressHandler(sender, e);
            UpdateNumberRepresentations();
        }

        private void ProgrammerView_LocationChanged(object? sender, EventArgs e)
        {
            if (_isSidebarOpen)
                PositionSidebar();
            if (_isMemoryOpen)
                PositionMemoryView();
        }

        private void AttachButtonHandlers()
        {
            // Define memory button content identifiers
            string[] memoryButtonContents = { "MC", "MR", "M+", "M-", "MS", "M˅" };

            foreach (var child in ButtonGrid.Children)
            {
                if (child is Grid grid)
                {
                    foreach (var gridChild in grid.Children)
                    {
                        if (gridChild is Button button && button != MenuButton)
                        {
                            string? content = button.Content?.ToString();
                            if (content != null && memoryButtonContents.Contains(content))
                            {
                                // Set specific click handler for memory buttons
                                button.Click += MemoryButton_Click;
                            }
                            else
                            {
                                // Regular button handler
                                button.Click += (s, e) => {
                                    _inputHandler.ButtonClickHandler(s, e);
                                    UpdateNumberRepresentations();
                                };
                            }
                        }
                    }
                }
                else if (child is Button button && button != MenuButton)
                {
                    string? content = button.Content?.ToString();
                    if (content != null && memoryButtonContents.Contains(content))
                    {
                        // Set specific click handler for memory buttons
                        button.Click += MemoryButton_Click;
                    }
                    else
                    {
                        // Regular button handler
                        button.Click += (s, e) => {
                            _inputHandler.ButtonClickHandler(s, e);
                            UpdateNumberRepresentations();
                        };
                    }
                }
            }
        }

        // Add this new method to handle memory button clicks
        private void MemoryButton_Click(object sender, RoutedEventArgs e)
        {
            if (sender is Button button)
            {
                string content = button.Content.ToString();

                switch (content)
                {
                    case "MC":
                        _calculator.MemoryClear();
                        UpdateMemoryViewDisplay();
                        break;

                    case "MR":
                        DisplayTextBox.Text = _calculator.MemoryRecall();
                        break;

                    case "M+":
                        _calculator.MemoryAdd();
                        UpdateMemoryViewDisplay();
                        break;

                    case "M-":
                        _calculator.MemorySubtract();
                        UpdateMemoryViewDisplay();
                        break;

                    case "MS":
                        _calculator.MemoryStore();
                        UpdateMemoryViewDisplay();
                        break;

                    case "M˅":
                        ToggleMemoryView();
                        break;
                }

                UpdateNumberRepresentations();
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
                sidebarView.SetProgrammerWindow(this);
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
                memoryView.SetProgrammerWindow(this);
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

        // Toggle the memory view
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
                UpdateMemoryViewDisplay(); // Update display when opening
                _memoryWindow.Show();
                _isMemoryOpen = true;
            }
        }

        // Called by InputHandler after a memory operation to update the memory view
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

        public void SwitchToStandardMode()
        {
            // Create and show the standard calculator view
            MainWindowView mainView = new MainWindowView();
            mainView.Show();

            // Close the programmer window (and associated sidebar and memory view)
            this.Close();
        }
    }
}