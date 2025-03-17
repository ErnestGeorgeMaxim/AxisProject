using System;
using System.Windows.Input;

namespace AxisProject.Commands
{
    public class RelayCommands : ICommand
    {
        private readonly Action<object> execute;
        private readonly Predicate<object>? canExecute;

        public RelayCommands(Action<object> ExecuteMethod, Predicate<object>? CanExecuteMethod = null)
        {
            execute = ExecuteMethod ?? throw new ArgumentNullException(nameof(ExecuteMethod));
            canExecute = CanExecuteMethod;
        }

        public bool CanExecute(object? parameter) => canExecute == null || canExecute(parameter!);

        public void Execute(object? parameter) => execute(parameter!);

        public event EventHandler? CanExecuteChanged
        {
            add => CommandManager.RequerySuggested += value;
            remove => CommandManager.RequerySuggested -= value;
        }
    }
}