using AxisProject.Models;
using AxisProject.Views;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace AxisProject.Commands
{
    public class InputHandlerProgrammer
    {
        private readonly TextBox _displayTextBox;
        private readonly ProgrammerCalculatorModel _calculator;
        private readonly ProgrammerView _programmerView;

        public InputHandlerProgrammer(TextBox displayTextBox, ProgrammerCalculatorModel calculator, ProgrammerView programmerView)
        {
            _displayTextBox = displayTextBox;
            _calculator = calculator;
            _programmerView = programmerView;
        }

        public void ButtonClickHandler(object sender, RoutedEventArgs e)
        {
            if (sender is Button button)
            {
                string content = button.Content.ToString();

                if (!_calculator.IsButtonEnabled(content))
                {
                    return;
                }

                HandleButtonContent(content);
            }
        }

        public void KeyPressHandler(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.NumPad0:
                case Key.D0:
                    if (_calculator.IsButtonEnabled("0"))
                        HandleButtonContent("0");
                    break;
                case Key.NumPad1:
                case Key.D1:
                    if (_calculator.IsButtonEnabled("1"))
                        HandleButtonContent("1");
                    break;
                case Key.NumPad2:
                case Key.D2:
                    if (_calculator.IsButtonEnabled("2"))
                        HandleButtonContent("2");
                    break;
                case Key.NumPad3:
                case Key.D3:
                    if (_calculator.IsButtonEnabled("3"))
                        HandleButtonContent("3");
                    break;
                case Key.NumPad4:
                case Key.D4:
                    if (_calculator.IsButtonEnabled("4"))
                        HandleButtonContent("4");
                    break;
                case Key.NumPad5:
                case Key.D5:
                    if (_calculator.IsButtonEnabled("5"))
                        HandleButtonContent("5");
                    break;
                case Key.NumPad6:
                case Key.D6:
                    if (_calculator.IsButtonEnabled("6"))
                        HandleButtonContent("6");
                    break;
                case Key.NumPad7:
                case Key.D7:
                    if (_calculator.IsButtonEnabled("7"))
                        HandleButtonContent("7");
                    break;
                case Key.NumPad8:
                case Key.D8:
                    if (_calculator.IsButtonEnabled("8"))
                        HandleButtonContent("8");
                    break;
                case Key.NumPad9:
                case Key.D9:
                    if (_calculator.IsButtonEnabled("9"))
                        HandleButtonContent("9");
                    break;
                case Key.A:
                    if (_calculator.IsButtonEnabled("A"))
                        HandleButtonContent("A");
                    break;
                case Key.B:
                    if (_calculator.IsButtonEnabled("B"))
                        HandleButtonContent("B");
                    break;
                case Key.C:
                    if (_calculator.CurrentNumberSystem == NumberSystem.HEX && _calculator.IsButtonEnabled("C"))
                        HandleButtonContent("C");
                    else
                        HandleButtonContent("Clear");
                    break;
                case Key.D:
                    if (_calculator.IsButtonEnabled("D"))
                        HandleButtonContent("D");
                    break;
                case Key.E:
                    if (_calculator.IsButtonEnabled("E"))
                        HandleButtonContent("E");
                    break;
                case Key.F:
                    if (_calculator.IsButtonEnabled("F"))
                        HandleButtonContent("F");
                    break;
                case Key.Add:
                    HandleButtonContent("+");
                    break;
                case Key.Subtract:
                    HandleButtonContent("−");
                    break;
                case Key.Multiply:
                    HandleButtonContent("×");
                    break;
                case Key.Divide:
                    HandleButtonContent("÷");
                    break;
                case Key.Enter:
                    HandleButtonContent("=");
                    break;
                case Key.Back:
                    HandleButtonContent("⌫");
                    break;
                case Key.Delete:
                    HandleButtonContent("Clear");
                    break;
                case Key.Decimal:
                case Key.OemPeriod:
                    if (_calculator.IsButtonEnabled("."))
                        HandleButtonContent(".");
                    break;
                case Key.M:
                    _programmerView.ToggleMemoryView();
                    break;
            }
        }

        private void HandleButtonContent(string content)
        {
            if (content == "C" && _calculator.CurrentNumberSystem == NumberSystem.HEX && _calculator.IsButtonEnabled("C"))
            {
                _calculator.AppendNumber("C");
                _displayTextBox.Text = _calculator.GetDisplayText();
                return;
            }

            switch (content)
            {
                case "0":
                case "1":
                case "2":
                case "3":
                case "4":
                case "5":
                case "6":
                case "7":
                case "8":
                case "9":
                case "A":
                case "B":
                case "D":
                case "E":
                case "F":
                case ".":
                    _calculator.AppendNumber(content);
                    break;
                case "+":
                    _calculator.SetOperator("+");
                    break;
                case "−":
                    _calculator.SetOperator("−");
                    break;
                case "×":
                    _calculator.SetOperator("×");
                    break;
                case "÷":
                    _calculator.SetOperator("÷");
                    break;
                case "%":
                    _calculator.SetOperator("%");
                    break;
                case "=":
                    _calculator.Calculate();
                    break;
                case "CE":
                    _calculator.ClearEntry();
                    break;
                case "Clear":
                    _calculator.Clear();
                    break;
                case "⌫":
                    _calculator.Backspace();
                    break;
                case "±":
                    _calculator.ToggleSign();
                    break;
                case "⅟𝑥":
                    _calculator.Reciprocal();
                    break;
                case "𝑥²":
                    _calculator.Square();
                    break;
                case "√𝑥":
                    _calculator.SquareRoot();
                    break;
                case "HEX":
                    _calculator.ChangeNumberSystem(NumberSystem.HEX);
                    UpdateButtonStates();
                    break;
                case "DEC":
                    _calculator.ChangeNumberSystem(NumberSystem.DEC);
                    UpdateButtonStates();
                    break;
                case "OCT":
                    _calculator.ChangeNumberSystem(NumberSystem.OCT);
                    UpdateButtonStates();
                    break;
                case "BIN":
                    _calculator.ChangeNumberSystem(NumberSystem.BIN);
                    UpdateButtonStates();
                    break;
                case "MC":
                    _calculator.MemoryClear();
                    _programmerView.UpdateMemoryViewDisplay();
                    break;
                case "MR":
                    _calculator.MemoryRecall();
                    break;
                case "M+":
                    _calculator.MemoryAdd();
                    _programmerView.UpdateMemoryViewDisplay();
                    break;
                case "M-":
                    _calculator.MemorySubtract();
                    _programmerView.UpdateMemoryViewDisplay();
                    break;
                case "MS":
                    _calculator.MemoryStore();
                    _programmerView.UpdateMemoryViewDisplay();
                    break;
                case "M˅":
                    _programmerView.ToggleMemoryView();
                    break;
            }

            _displayTextBox.Text = _calculator.GetDisplayText();
        }

        public void UpdateButtonStates()
        {
            NumberSystem currentSystem = _calculator.CurrentNumberSystem;

            foreach (var child in _programmerView.ButtonGrid.Children)
            {
                if (child is Grid grid)
                {
                    UpdateButtonsInGrid(grid, currentSystem);
                }
                else if (child is Button button)
                {
                    UpdateButtonState(button, currentSystem);
                }
            }
        }

        private void UpdateButtonsInGrid(Grid grid, NumberSystem currentSystem)
        {
            foreach (var gridChild in grid.Children)
            {
                if (gridChild is Button button)
                {
                    UpdateButtonState(button, currentSystem);
                }
            }
        }

        private void UpdateButtonState(Button button, NumberSystem currentSystem)
        {
            string? content = button.Content?.ToString();
            if (string.IsNullOrEmpty(content))
                return;

            if (content == "+" || content == "−" || content == "×" || content == "÷" ||
                content == "=" || content == "%" || content == "CE" || content == "Clear" ||
                content == "⌫" || content == "±" || content == "." || content == "☰" ||
                content == "HEX" || content == "DEC" || content == "OCT" || content == "BIN" ||
                content == "MC" || content == "MR" || content == "M+" || content == "M-" ||
                content == "MS" || content == "M˅" || content == "M∨")
            {
                button.IsEnabled = true;
                button.Opacity = 1.0;
                return;
            }

            switch (currentSystem)
            {
                case NumberSystem.BIN:
                    button.IsEnabled = content == "0" || content == "1";
                    break;

                case NumberSystem.OCT:
                    button.IsEnabled = content == "0" || content == "1" || content == "2" ||
                                      content == "3" || content == "4" || content == "5" ||
                                      content == "6" || content == "7";
                    break;

                case NumberSystem.DEC:
                    button.IsEnabled = content == "0" || content == "1" || content == "2" ||
                                      content == "3" || content == "4" || content == "5" ||
                                      content == "6" || content == "7" || content == "8" ||
                                      content == "9";
                    break;

                case NumberSystem.HEX:
                    button.IsEnabled = content == "0" || content == "1" || content == "2" ||
                                      content == "3" || content == "4" || content == "5" ||
                                      content == "6" || content == "7" || content == "8" ||
                                      content == "9" || content == "A" || content == "B" ||
                                      content == "C" || content == "D" || content == "E" ||
                                      content == "F";
                    break;
            }
            button.Opacity = button.IsEnabled ? 1.0 : 0.5;
        }

        private void UpdateButtonIfNeeded(object element)
        {
            if (element is Button button && button.Content is string content)
            {
                bool isEnabled = _calculator.IsButtonEnabled(content);
                button.IsEnabled = isEnabled;
                button.Opacity = isEnabled ? 1.0 : 0.3;
            }
        }
    }
}