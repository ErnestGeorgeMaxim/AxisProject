using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
namespace AxisProject.Views
{
    public partial class MemoryView : Window
    {
        private MainWindowView? _mainWindow;
        private ProgrammerView? _programmerView;

        public MemoryView()
        {
            InitializeComponent();
        }

        public void SetMainWindow(MainWindowView mainWindow)
        {
            _mainWindow = mainWindow;
            _programmerView = null;
        }

        public void SetProgrammerWindow(ProgrammerView programmerView)
        {
            _programmerView = programmerView;
            _mainWindow = null;
        }

        // Call this method to position the MemoryView on the left side of the window
        public void PositionRelativeToParent()
        {
            if (_mainWindow != null)
            {
                this.Left = _mainWindow.Left - this.Width;
                this.Top = _mainWindow.Top;
            }
            else if (_programmerView != null)
            {
                this.Left = _programmerView.Left - this.Width;
                this.Top = _programmerView.Top;
            }
        }

        /// <summary>
        /// Update the displayed memory items based on the provided memory string.
        /// </summary>
        /// <param name="memoryStackDisplay">A string with one memory value per line.</param>
        public void UpdateMemoryItems(string memoryStackDisplay)
        {
            MemoryItemsPanel.Children.Clear();
            var lines = memoryStackDisplay.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var line in lines)
            {
                var tb = new TextBlock
                {
                    Text = line,
                    Foreground = Brushes.White,
                    Margin = new Thickness(0, 5, 0, 5),
                    FontSize = 20
                };
                MemoryItemsPanel.Children.Add(tb);
            }
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            // Notify the parent window that the memory view is now hidden
            if (_mainWindow != null)
            {
                _mainWindow.SetMemoryViewState(false);
            }
            else if (_programmerView != null)
            {
                _programmerView.SetMemoryViewState(false);
            }
        }
    }
}