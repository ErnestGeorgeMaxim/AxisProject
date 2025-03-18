using AxisProject.Commands;
using AxisProject.Models;
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
        private Window _memoryWindow = null!;
        private bool _isMemoryOpen = false;
        private ProgrammerCalculatorModel _calculator;
        private InputHandlerProgrammer _inputHandler;

        public ProgrammerView()
        {
            InitializeComponent();

            this.Focusable = true;
            this.Focus();

            _calculator = new ProgrammerCalculatorModel();
            _inputHandler = new InputHandlerProgrammer(DisplayTextBox, _calculator, this);

            DisplayTextBox.Text = _calculator.GetDisplayText();
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

            SetNumberSystemButtonHandlers();

            AttachButtonHandlers();
            NumberSystem savedSystem = SettingsManager.Instance.NumberSystem;
            _calculator.ChangeNumberSystem(savedSystem);
            HighlightActiveNumberSystemButton(savedSystem);
            _inputHandler.UpdateButtonStates();
            UpdateNumberRepresentations();

            this.LocationChanged += ProgrammerView_LocationChanged;
            this.KeyDown += ProgrammerView_KeyDown;
        }

        private void InitializeNumberSystemDisplays()
        {
            StackPanel representationsPanel = new StackPanel
            {
                Orientation = Orientation.Vertical,
                Margin = new Thickness(10, 212, 10, 0),
                VerticalAlignment = VerticalAlignment.Top,
                HorizontalAlignment = HorizontalAlignment.Stretch
            };

            ButtonGrid.Children.Add(representationsPanel);
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
            string hexValue = _calculator.GetHexRepresentation();
            string decValue = _calculator.CurrentInput;
            string octValue = _calculator.GetOctalRepresentation();
            string binValue = _calculator.GetBinaryRepresentation();
            string formattedBinValue = FormatBinaryValue(binValue);
        }

        private void UpdateNumberSystemInline(TextBlock textBlock, string prefix, string value)
        {
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

            SettingsManager.Instance.NumberSystem = system;

            Console.WriteLine($"Saved number system: {SettingsManager.Instance.NumberSystem}");
            _inputHandler.UpdateButtonStates();
            DisplayTextBox.Text = _calculator.GetDisplayText();
            UpdateNumberRepresentations();
            HighlightActiveNumberSystemButton(system);
        }

        private void HighlightActiveNumberSystemButton(NumberSystem system)
        {
            foreach (var child in ButtonGrid.Children)
            {
                if (child is Button button)
                {
                    string? content = button.Content?.ToString();
                    if (content == null) continue;

                    bool isActiveSystem = false;

                    switch (content)
                    {
                        case "HEX": isActiveSystem = system == NumberSystem.HEX; break;
                        case "DEC": isActiveSystem = system == NumberSystem.DEC; break;
                        case "OCT": isActiveSystem = system == NumberSystem.OCT; break;
                        case "BIN": isActiveSystem = system == NumberSystem.BIN; break;
                        default: continue;
                    }

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
                                button.Click += MemoryButton_Click;
                            }
                            else
                            {
                                button.Click += (s, e) =>
                                {
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
                        button.Click += MemoryButton_Click;
                    }
                    else
                    {
                        button.Click += (s, e) =>
                        {
                            _inputHandler.ButtonClickHandler(s, e);
                            UpdateNumberRepresentations();
                        };
                    }
                }
            }
        }

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

        public void SwitchToStandardMode()
        {
            // Save calculator mode setting
            SettingsManager.Instance.CalculatorMode = CalculatorMode.Standard;

            Console.WriteLine($"Saved calculator mode: {SettingsManager.Instance.CalculatorMode}"); // Debug line

            // Create and show the standard calculator view
            MainWindowView mainView = new MainWindowView();
            mainView.Show();

            // Close the programmer window (and associated sidebar and memory view)
            this.Close();
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