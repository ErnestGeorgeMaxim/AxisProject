using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AxisProject.Models
{
    public enum NumberSystem
    {
        HEX,
        DEC,
        OCT,
        BIN
    }

    public class ProgrammerCalculatorModel
    {
        // Properties
        public string CurrentInput { get; private set; } = "0";
        public string Expression { get; private set; } = "";
        public NumberSystem CurrentNumberSystem { get; private set; } = NumberSystem.DEC;

        // Private fields
        private List<long> _memoryStack = new List<long>();
        private long _currentValue = 0;
        private string _currentOperator = "";
        private bool _isNewOperation = true;
        private bool _hasCalculated = false;

        // Dictionary to track which buttons should be enabled for each number system
        private Dictionary<NumberSystem, HashSet<string>> _enabledButtons;

        public ProgrammerCalculatorModel()
        {
            InitializeEnabledButtons();
            // Set default number system to decimal
            CurrentNumberSystem = NumberSystem.DEC;
        }

        private void InitializeEnabledButtons()
        {
            _enabledButtons = new Dictionary<NumberSystem, HashSet<string>>
            {
                {
                    NumberSystem.HEX,
                    new HashSet<string> { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                                          "A", "B", "C", "D", "E", "F",
                                          "+", "−", "×", "÷", "%", "=", "CE", "Clear", "⌫", "±" }
                },
                {
                    NumberSystem.DEC,
                    new HashSet<string> { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".",
                                          "+", "−", "×", "÷", "%", "=", "CE", "Clear", "⌫", "±" }
                },
                {
                    NumberSystem.OCT,
                    new HashSet<string> { "0", "1", "2", "3", "4", "5", "6", "7",
                                          "+", "−", "×", "÷", "%", "=", "CE", "Clear", "⌫", "±" }
                },
                {
                    NumberSystem.BIN,
                    new HashSet<string> { "0", "1",
                                          "+", "−", "×", "÷", "%", "=", "CE", "Clear", "⌫", "±" }
                }
            };
        }

        public bool IsButtonEnabled(string buttonContent)
        {
            if (_enabledButtons.TryGetValue(CurrentNumberSystem, out var enabledSet))
            {
                return enabledSet.Contains(buttonContent);
            }
            return false;
        }

        // Conversion: Read the string in its current base and return a base‑10 (decimal) long
        private long ConvertToDecimal(string value, NumberSystem fromSystem)
        {
            if (string.IsNullOrEmpty(value))
                return 0;
            try
            {
                switch (fromSystem)
                {
                    case NumberSystem.HEX:
                        return Convert.ToInt64(value, 16);
                    case NumberSystem.DEC:
                        return Convert.ToInt64(value, 10);
                    case NumberSystem.OCT:
                        return Convert.ToInt64(value, 8);
                    case NumberSystem.BIN:
                        return Convert.ToInt64(value, 2);
                    default:
                        return 0;
                }
            }
            catch (Exception)
            {
                // On error, default to 0
                return 0;
            }
        }

        // Conversion: Convert a base‑10 (decimal) value into a string in the desired base
        private string ConvertFromDecimal(long value, NumberSystem toSystem)
        {
            try
            {
                switch (toSystem)
                {
                    case NumberSystem.HEX:
                        return value.ToString("X").ToUpper();
                    case NumberSystem.DEC:
                        return value.ToString();
                    case NumberSystem.OCT:
                        return Convert.ToString(value, 8);
                    case NumberSystem.BIN:
                        return Convert.ToString(value, 2);
                    default:
                        return "0";
                }
            }
            catch (Exception)
            {
                return "0";
            }
        }

        // Append a digit or decimal point (if in DEC mode)
        public void AppendNumber(string number)
        {
            if (!IsButtonEnabled(number))
                return;

            if (_hasCalculated)
            {
                Clear();
                _hasCalculated = false;
            }
            if (number == "." && CurrentNumberSystem != NumberSystem.DEC)
                return;
            if (number == "." && CurrentInput.Contains("."))
                return;

            if (CurrentInput == "0")
                CurrentInput = number;
            else
                CurrentInput += number;

            _isNewOperation = false;
        }

        // Set operator (mimicking CalculatorModel's approach)
        public void SetOperator(string op)
        {
            if (_hasCalculated)
            {
                Expression = "";
                _hasCalculated = false;
            }

            if (string.IsNullOrEmpty(Expression))
            {
                Expression = CurrentInput + op;
            }
            else if (_isNewOperation)
            {
                Expression = Expression.Substring(0, Expression.Length - 1) + op;
            }
            else
            {
                Expression += CurrentInput + op;
            }
            _currentOperator = op;
            _currentValue = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            CurrentInput = "0";
            _isNewOperation = true;
        }

        // Calculate the result in base‑10 then convert to the current base
        public string Calculate()
        {
            long secondOperand = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            long result = _currentValue;
            if (!_hasCalculated)
            {
                Expression += CurrentInput;
            }
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
                case "%":
                    if (secondOperand == 0)
                        return "Error";
                    result %= secondOperand;
                    break;
            }
            Expression = "";
            _hasCalculated = true;
            CurrentInput = ConvertFromDecimal(result, CurrentNumberSystem);
            return CurrentInput;
        }

        // Percentage operation mimics CalculatorModel: perform percentage calculation in base‑10
        public string ApplyPercentage()
        {
            long value = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            if (string.IsNullOrEmpty(_currentOperator))
                return CurrentInput;
            long result = 0;
            switch (_currentOperator)
            {
                case "+":
                case "−":
                    result = (long)(_currentValue * (value / 100.0));
                    break;
                case "×":
                case "÷":
                    result = (long)(value / 100.0);
                    break;
            }
            CurrentInput = ConvertFromDecimal(result, CurrentNumberSystem);
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
            long val = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            long result = val * val;
            CurrentInput = ConvertFromDecimal(result, CurrentNumberSystem);
            return CurrentInput;
        }

        public string SquareRoot()
        {
            long val = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            if (val < 0)
                return "Error";
            long result = (long)Math.Sqrt(val);
            CurrentInput = ConvertFromDecimal(result, CurrentNumberSystem);
            return CurrentInput;
        }

        public string Reciprocal()
        {
            // For programmer mode, reciprocal is only defined in DEC
            if (CurrentNumberSystem != NumberSystem.DEC)
                return CurrentInput;
            double value = double.Parse(CurrentInput);
            if (value == 0)
                return "Error";
            double result = 1 / value;
            CurrentInput = result.ToString("F6").TrimEnd('0').TrimEnd('.');
            return CurrentInput;
        }

        public string ToggleSign()
        {
            long val = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            long result = -val;
            CurrentInput = ConvertFromDecimal(result, CurrentNumberSystem);
            return CurrentInput;
        }

        public string GetDisplayText()
        {
            if (_hasCalculated)
                return CurrentInput;
            if (string.IsNullOrEmpty(Expression))
                return CurrentInput;
            if (!_isNewOperation && CurrentInput != "0")
            {
                long firstOperand = _currentValue;
                long secondOperand = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
                long runningResult = 0;
                switch (_currentOperator)
                {
                    case "+": runningResult = firstOperand + secondOperand; break;
                    case "−": runningResult = firstOperand - secondOperand; break;
                    case "×": runningResult = firstOperand * secondOperand; break;
                    case "÷":
                        if (secondOperand == 0)
                            return Expression + CurrentInput + "\nError";
                        runningResult = firstOperand / secondOperand;
                        break;
                    case "%":
                        if (secondOperand == 0)
                            return Expression + CurrentInput + "\nError";
                        runningResult = firstOperand % secondOperand;
                        break;
                }
                return Expression + CurrentInput + "\n" + ConvertFromDecimal(runningResult, CurrentNumberSystem);
            }
            return Expression + (_isNewOperation ? "" : CurrentInput);
        }

        public void ChangeNumberSystem(NumberSystem newSystem)
        {
            if (CurrentNumberSystem == newSystem)
                return;
            long decimalValue = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            CurrentNumberSystem = newSystem;
            CurrentInput = ConvertFromDecimal(decimalValue, newSystem);
        }

        #region Memory Functions

        // Memory Store (MS): Store the current value in the memory stack
        public void MemoryStore()
        {
            // Convert the current input to decimal (base-10) for storage
            long value = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            _memoryStack.Add(value);
        }

        // Memory Add (M+): Add the current value to the last value in memory stack
        public void MemoryAdd()
        {
            long value = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            if (_memoryStack.Any())
                _memoryStack[_memoryStack.Count - 1] += value;
            else
                _memoryStack.Add(value);
        }

        // Memory Subtract (M-): Subtract the current value from the last value in memory stack
        public void MemorySubtract()
        {
            long value = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            if (_memoryStack.Any())
                _memoryStack[_memoryStack.Count - 1] -= value;
            else
                _memoryStack.Add(-value);
        }

        // Memory Recall (MR): Recall the last value from memory stack
        public string MemoryRecall()
        {
            if (_memoryStack.Any())
            {
                // Convert from decimal (base-10) to the current number system for display
                CurrentInput = ConvertFromDecimal(_memoryStack.Last(), CurrentNumberSystem);
                return CurrentInput;
            }
            return "0";
        }

        // Memory Clear (MC): Clear all values from memory stack
        public void MemoryClear()
        {
            _memoryStack.Clear();
        }

        // Memory Stack Display (M˅): Show all values in the memory stack
        public string MemoryStackDisplay()
        {
            if (!_memoryStack.Any())
                return "No memory values stored.";

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < _memoryStack.Count; i++)
            {
                // Display memory values in the current number system
                string formattedValue = ConvertFromDecimal(_memoryStack[i], CurrentNumberSystem);
                sb.AppendLine($"{i + 1}: {formattedValue}");
            }
            return sb.ToString();
        }

        // Convert a specific memory entry to current number system format
        public string GetMemoryValueInCurrentSystem(int index)
        {
            if (index >= 0 && index < _memoryStack.Count)
            {
                return ConvertFromDecimal(_memoryStack[index], CurrentNumberSystem);
            }
            return "0";
        }

        // Get total number of items in memory stack
        public int GetMemoryCount()
        {
            return _memoryStack.Count;
        }

        #endregion

        // Additional display methods for programmer mode
        public string GetBinaryRepresentation()
        {
            long value = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            return Convert.ToString(value, 2).PadLeft(64, '0');
        }

        public string GetHexRepresentation()
        {
            long value = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            return value.ToString("X16");
        }

        public string GetOctalRepresentation()
        {
            long value = ConvertToDecimal(CurrentInput, CurrentNumberSystem);
            return Convert.ToString(value, 8);
        }
    }
}
