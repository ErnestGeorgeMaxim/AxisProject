using System;

namespace ConsoleApp1
{
    // Alt + Enter pe numele clasei daca nu este declarata separat, pentru a fi copiata intr un fisier nou dedicat acestei clase,
    // sau alt + "."
    class Calculator
    {

        // static are rolul de a crea o functie de sine statoare fara utilizarea
        // variabilelor declarate din clasa respectiva
        // functie a clasei intr-un fel...
        public static int Sum(int firstNumber, int secondNumber)
        {
            return firstNumber + secondNumber;
        }

        // Tratarea exceptiilor
        public static int Divide(int firstNumber, int secondNumber)
        {
            try
            {
                //Incearca
                return firstNumber / secondNumber;
            } catch (DivideByZeroException)
            {
                Console.WriteLine("Diviziunea nu a fost posibila, secondNumber a fost 0.");
                return 0;
                //Daca se arunca DivideByZeroException fa asta
            }
        }

        public static int Multiply(int firstNumber, int secondNumber)
        {
            return firstNumber * secondNumber;
        }

        public static int Difference(int firstNumber, int secondNumber)
        {
            if (firstNumber > secondNumber)
                return firstNumber - secondNumber;
            else
                return secondNumber - firstNumber;
        }
    }
}
