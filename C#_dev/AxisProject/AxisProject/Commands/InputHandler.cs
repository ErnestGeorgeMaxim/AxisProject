using AxisProject.Models;
using AxisProject.Views;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace AxisProject.Commands
{
    public class InputHandler
    {
        private readonly TextBox _display;
        private readonly CalculatorModel _calculator;
        private readonly MainWindowView _mainWindowView;
        private readonly ProgrammerView _programmerView;

        public InputHandler(TextBox display, CalculatorModel calculator, MainWindowView mainWindowView)
        {
            _display = display ?? throw new ArgumentNullException(nameof(display));
            _calculator = calculator ?? throw new ArgumentNullException(nameof(calculator));
            _mainWindowView = mainWindowView ?? throw new ArgumentNullException(nameof(mainWindowView));

        }

        public InputHandler(TextBox display, CalculatorModel calculator, ProgrammerView programmerView)
        {
            _display = display ?? throw new ArgumentNullException(nameof(display));
            _calculator = calculator ?? throw new ArgumentNullException(nameof(calculator));
            _programmerView = programmerView ?? throw new ArgumentNullException(nameof(programmerView));

        }

        public void ButtonClickHandler(Object sender, RoutedEventArgs e)
        {
            if (sender is Button button)
            {
                string input = button.Content.ToString();
                ProcessInput(input);
            }
        }

        public void KeyPressHandler(Object sender, KeyEventArgs e)
        {
            string input = e.Key switch
            {
                Key.D0 => "0",
                Key.D1 => "1",
                Key.D2 => "2",
                Key.D3 => "3",
                Key.D4 => "4",
                Key.D5 => "5",
                Key.D6 => "6",
                Key.D7 => "7",
                Key.D8 => "8",
                Key.D9 => "9",

                Key.NumPad0 => "0",
                Key.NumPad1 => "1",
                Key.NumPad2 => "2",
                Key.NumPad3 => "3",
                Key.NumPad4 => "4",
                Key.NumPad5 => "5",
                Key.NumPad6 => "6",
                Key.NumPad7 => "7",
                Key.NumPad8 => "8",
                Key.NumPad9 => "9",

                Key.Add => "+",
                Key.OemPlus => "+",
                Key.Subtract => "−",
                Key.OemMinus => "−",
                Key.Multiply => "×",
                Key.Divide => "÷",
                Key.OemQuestion => "÷",

                // Special keys
                Key.Decimal => ".",
                Key.OemPeriod => ".",
                Key.Enter => "=",
                Key.Back => "⌫",
                Key.Delete => "C",
                Key.Escape => "C",

                Key.F9 => "±",
                Key.R => "1/x",
                Key.Q => "√x",
                Key.S => "x²",
                Key.P => "%",

                _ => ""
            };

            if (!string.IsNullOrEmpty(input))
            {
                ProcessInput(input);
                e.Handled = true;
            }
        }

        private void ProcessInput(string input)
        {
            switch (input)
            {
                case "C":
                    _calculator.Clear();
                    _display.Text = "0";
                    break;
                case "CE":
                    _calculator.ClearEntry();
                    _display.Text = "0";
                    break;
                case "⌫":
                    _calculator.Backspace();
                    _display.Text = _calculator.GetDisplayText();
                    break;
                case "=":
                    _calculator.Calculate();
                    _display.Text = _calculator.GetDisplayText();
                    break;
                case "+":
                    _calculator.SetOperator(input);
                    _display.Text = _calculator.GetDisplayText();
                    break;
                case "−":
                    _calculator.SetOperator(input);
                    _display.Text = _calculator.GetDisplayText();
                    break;
                case "×":
                    _calculator.SetOperator(input);
                    _display.Text = _calculator.GetDisplayText();
                    break;
                case "÷":
                    _calculator.SetOperator(input);
                    _display.Text = _calculator.GetDisplayText();
                    break;
                case "%":
                    _display.Text = _calculator.ApplyPercentage();
                    break;
                case "𝑥²":
                case "x²":
                    _display.Text = _calculator.Square();
                    break;
                case "√𝑥":
                case "√x":
                    _display.Text = _calculator.SquareRoot();
                    break;
                case "⅟𝑥":
                case "1/x":
                    _display.Text = _calculator.Reciprocal();
                    break;
                case "±":
                    _display.Text = _calculator.ToggleSign();
                    break;
                case "MC":
                    _calculator.MemoryClear();
                    _mainWindowView.UpdateMemoryViewDisplay();
                    break;
                case "MR":
                    _display.Text = _calculator.MemoryRecall();
                    _mainWindowView.UpdateMemoryViewDisplay();
                    break;
                case "M+":
                    _calculator.MemoryAdd();
                    _mainWindowView.UpdateMemoryViewDisplay();
                    break;
                case "M-":
                    _calculator.MemorySubtract();
                    _mainWindowView.UpdateMemoryViewDisplay();
                    break;
                case "MS":
                    _calculator.MemoryStore();
                    _mainWindowView.UpdateMemoryViewDisplay();
                    break;
                case "M˅":
                    _mainWindowView.ToggleMemoryView();
                    break;
                case "Thousands Separator":
                    _calculator.ToggleDigitGrouping();
                    _display.Text = _calculator.GetDisplayText();
                    break;
                default:
                    _calculator.AppendNumber(input);
                    _display.Text = _calculator.GetDisplayText();
                    break;
            }
        }
    }
}