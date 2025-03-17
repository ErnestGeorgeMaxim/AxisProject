using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using AxisProject.Models;
using AxisProject.Views;

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
                // Number keys (top row)
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

                // Numpad numbers
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

                // Operations (both standard and numpad)
                Key.Add => "+",
                Key.OemPlus => "+", // For + without shift
                Key.Subtract => "−",
                Key.OemMinus => "−", // For - without shift
                Key.Multiply => "×",
                Key.Divide => "÷",
                Key.OemQuestion => "÷", // For / key

                // Special keys
                Key.Decimal => ".",
                Key.OemPeriod => ".", // For . key
                Key.Enter => "=",
                Key.Back => "⌫",
                Key.Delete => "C",
                Key.Escape => "C", // Escape also clears

                // Function key mappings
                Key.F9 => "±", // F9 for toggle sign (+/-)
                Key.R => "1/x", // R for reciprocal
                Key.Q => "√x", // Q for square root
                Key.S => "x²", // S for square
                Key.P => "%", // P for percent

                _ => ""
            };

            if (!string.IsNullOrEmpty(input))
            {
                ProcessInput(input);
                e.Handled = true; // Mark event as handled to prevent default behavior
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
                // Toggle the memory view when M˅ is pressed.
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