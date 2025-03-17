using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AxisProject.Models
{
    public class CalculatorModel
    {
        public string CurrentInput { get; private set; } = "0";
        public string Expression { get; private set; } = "";

        private List<double> _memoryStack = new List<double>();

        private double _currentValue = 0;
        private string _currentOperator = "";
        private bool _isNewOperation = true;
        private bool _hasCalculated = false;

        // Add property to track if digit grouping is enabled
        public bool IsDigitGroupingEnabled { get; set; } = false;

        // Format number with or without digit grouping based on current settings
        private string FormatNumber(double number)
        {
            if (IsDigitGroupingEnabled)
            {
                // Use current culture's number format for proper digit grouping
                CultureInfo currentCulture = CultureInfo.CurrentCulture;
                return number.ToString("N", currentCulture)
                    .TrimEnd('0').TrimEnd(currentCulture.NumberFormat.NumberDecimalSeparator[0]);
            }
            else
            {
                // Original format without grouping
                return number.ToString("F6").TrimEnd('0').TrimEnd('.');
            }
        }

        public void AppendNumber(string number)
        {
            if (_hasCalculated)
            {
                Clear();
                _hasCalculated = false;
            }

            if (number == ".")
            {
                // Use current culture's decimal separator
                string decimalSeparator = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
                if (CurrentInput.Contains(decimalSeparator))
                    return;

                CurrentInput += decimalSeparator;
                _isNewOperation = false;
                return;
            }

            if (CurrentInput == "0")
                CurrentInput = number;
            else
                CurrentInput += number;

            if (_isNewOperation)
            {
                _isNewOperation = false;
            }
        }

        public void SetOperator(string op)
        {
            if (_hasCalculated)
            {
                Expression = "";
                _hasCalculated = false;
            }

            // If it's not a new operation, perform the previous operation first
            if (!_isNewOperation && !string.IsNullOrEmpty(_currentOperator))
            {
                double secondOperand = double.Parse(CurrentInput, CultureInfo.InvariantCulture);

                switch (_currentOperator)
                {
                    case "+": _currentValue += secondOperand; break;
                    case "−": _currentValue -= secondOperand; break;
                    case "×": _currentValue *= secondOperand; break;
                    case "÷":
                        if (secondOperand == 0)
                        {
                            CurrentInput = "Error";
                            return;
                        }
                        _currentValue /= secondOperand;
                        break;
                }

                // Update the expression to show the running calculation
                Expression = FormatNumber(_currentValue) + op;
                CurrentInput = "0";
            }
            else
            {
                if (string.IsNullOrEmpty(Expression))
                {
                    Expression = FormatDisplayNumber(CurrentInput) + op;
                }
                else if (_isNewOperation)
                {
                    Expression = Expression.Substring(0, Expression.Length - 1) + op;
                }
                else
                {
                    Expression += FormatDisplayNumber(CurrentInput) + op;
                }

                _currentValue = double.Parse(CurrentInput, CultureInfo.InvariantCulture);
                CurrentInput = "0";
            }

            _currentOperator = op;
            _isNewOperation = true;
        }

        public string Calculate()
        {
            double secondOperand = double.Parse(CurrentInput, CultureInfo.InvariantCulture);
            double result = _currentValue;

            if (!_hasCalculated)
            {
                Expression += FormatDisplayNumber(CurrentInput);
            }

            if (CurrentInput.EndsWith("%"))
            {
                secondOperand = _currentValue * (double.Parse(CurrentInput.TrimEnd('%'), CultureInfo.InvariantCulture) / 100);
            }
            else
            {
                switch (_currentOperator)
                {
                    case "+": result += secondOperand; break;
                    case "−": result -= secondOperand; break;
                    case "×": result *= secondOperand; break;
                    case "÷":
                        if (secondOperand == 0)
                            return "Error";
                        result /= secondOperand;
                        break;
                }
            }

            Expression = "";
            _hasCalculated = true;
            CurrentInput = result.ToString(CultureInfo.InvariantCulture);
            return FormatDisplayNumber(CurrentInput);
        }

        public string ApplyPercentage()
        {
            double value = double.Parse(CurrentInput, CultureInfo.InvariantCulture);

            if (string.IsNullOrEmpty(_currentOperator))
            {
                return FormatDisplayNumber(CurrentInput);
            }

            switch (_currentOperator)
            {
                case "+":
                case "−":
                    value = _currentValue * (value / 100);
                    break;
                case "×":
                    value = value / 100;
                    break;
                case "÷":
                    value = value / 100;
                    break;
            }

            CurrentInput = value.ToString(CultureInfo.InvariantCulture);
            return GetDisplayText();
        }

        public void Clear()
        {
            CurrentInput = "0";
            Expression = "";
            _currentValue = 0;
            _currentOperator = "";
            _isNewOperation = true;
            _hasCalculated = false;
        }

        public void ClearEntry()
        {
            CurrentInput = "0";
        }

        public void Backspace()
        {
            if (CurrentInput.Length > 1)
                CurrentInput = CurrentInput[..^1];
            else
                CurrentInput = "0";
        }

        public string Square()
        {
            string originalInput = FormatDisplayNumber(CurrentInput);
            double result = double.Parse(CurrentInput, CultureInfo.InvariantCulture) * double.Parse(CurrentInput, CultureInfo.InvariantCulture);
            if (!string.IsNullOrEmpty(_currentOperator) && !_isNewOperation)
            {
                CurrentInput = result.ToString(CultureInfo.InvariantCulture);
                return GetDisplayText();
            }
            else
            {
                Expression = $"{originalInput}² = ";
                _hasCalculated = true;
                CurrentInput = result.ToString(CultureInfo.InvariantCulture);
                return FormatDisplayNumber(CurrentInput);
            }
        }

        public string SquareRoot()
        {
            string originalInput = FormatDisplayNumber(CurrentInput);
            double result = Math.Sqrt(double.Parse(CurrentInput, CultureInfo.InvariantCulture));

            if (!string.IsNullOrEmpty(_currentOperator) && !_isNewOperation)
            {
                CurrentInput = result.ToString(CultureInfo.InvariantCulture);
                return GetDisplayText();
            }
            else
            {
                Expression = $"√{originalInput} = ";
                _hasCalculated = true;
                CurrentInput = result.ToString(CultureInfo.InvariantCulture);
                return FormatDisplayNumber(CurrentInput);
            }
        }

        public string Reciprocal()
        {
            string originalInput = FormatDisplayNumber(CurrentInput);

            if (double.Parse(CurrentInput, CultureInfo.InvariantCulture) == 0)
                return "Error";

            double result = 1 / double.Parse(CurrentInput, CultureInfo.InvariantCulture);

            if (!string.IsNullOrEmpty(_currentOperator) && !_isNewOperation)
            {
                CurrentInput = result.ToString(CultureInfo.InvariantCulture);
                return GetDisplayText();
            }
            else
            {
                Expression = $"1/{originalInput} = ";
                _hasCalculated = true;
                CurrentInput = result.ToString(CultureInfo.InvariantCulture);
                return FormatDisplayNumber(CurrentInput);
            }
        }

        public string ToggleSign()
        {
            double result = -double.Parse(CurrentInput, CultureInfo.InvariantCulture);
            CurrentInput = result.ToString(CultureInfo.InvariantCulture);
            return FormatDisplayNumber(CurrentInput);
        }

        // Format the display number with or without digit grouping
        private string FormatDisplayNumber(string number)
        {
            if (double.TryParse(number, CultureInfo.InvariantCulture, out double parsedNumber))
            {
                return FormatNumber(parsedNumber);
            }
            return number; // Return as is if not a valid number (e.g., "Error")
        }

        public string GetDisplayText()
        {
            if (_hasCalculated)
            {
                return FormatDisplayNumber(CurrentInput);
            }
            else if (string.IsNullOrEmpty(Expression))
            {
                return FormatDisplayNumber(CurrentInput);
            }
            else
            {
                if (!_isNewOperation && CurrentInput != "0")
                {
                    // Calculate and display the running result
                    double firstOperand = _currentValue;
                    double secondOperand = double.Parse(CurrentInput, CultureInfo.InvariantCulture);
                    double runningResult = 0;

                    switch (_currentOperator)
                    {
                        case "+": runningResult = firstOperand + secondOperand; break;
                        case "−": runningResult = firstOperand - secondOperand; break;
                        case "×": runningResult = firstOperand * secondOperand; break;
                        case "÷":
                            if (secondOperand == 0)
                                return "Error";  // Prevent division by zero
                            runningResult = firstOperand / secondOperand;
                            break;
                    }

                    // Show both the expression and the running result
                    return Expression + FormatDisplayNumber(CurrentInput) + "\n" + FormatNumber(runningResult);
                }
                else
                {
                    // Just show the expression if we're starting a new operation
                    return Expression + (_isNewOperation ? "" : FormatDisplayNumber(CurrentInput));
                }
            }
        }

        // Toggle digit grouping
        public void ToggleDigitGrouping()
        {
            IsDigitGroupingEnabled = !IsDigitGroupingEnabled;
        }

        #region Memory Functions

        // Memory Store (MS): Push the current display value onto the memory stack.
        public void MemoryStore()
        {
            double value = double.Parse(CurrentInput, CultureInfo.InvariantCulture);
            _memoryStack.Add(value);
        }

        // Memory Add (M+): Add the current display value to the last stored memory value,
        // or store it if the memory stack is empty.
        public void MemoryAdd()
        {
            double value = double.Parse(CurrentInput, CultureInfo.InvariantCulture);
            if (_memoryStack.Any())
                _memoryStack[_memoryStack.Count - 1] += value;
            else
                _memoryStack.Add(value);
        }

        // Memory Subtract (M-): Subtract the current display value from the last stored memory value,
        // or store the negative value if the memory stack is empty.
        public void MemorySubtract()
        {
            double value = double.Parse(CurrentInput, CultureInfo.InvariantCulture);
            if (_memoryStack.Any())
                _memoryStack[_memoryStack.Count - 1] -= value;
            else
                _memoryStack.Add(-value);
        }

        // Memory Recall (MR): Return the last stored memory value and update the display.
        public string MemoryRecall()
        {
            if (_memoryStack.Any())
            {
                CurrentInput = _memoryStack.Last().ToString(CultureInfo.InvariantCulture);
                return FormatDisplayNumber(CurrentInput);
            }
            return "0";
        }

        // Memory Clear (MC): Clear the memory stack.
        public void MemoryClear()
        {
            _memoryStack.Clear();
        }

        // Memory Stack Display (M˅): Return a string showing all stored memory values.
        public string MemoryStackDisplay()
        {
            if (!_memoryStack.Any())
                return "No memory values stored.";

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < _memoryStack.Count; i++)
            {
                sb.AppendLine($"{i + 1}: {FormatNumber(_memoryStack[i])}");
            }
            return sb.ToString();
        }

        #endregion
    }
}