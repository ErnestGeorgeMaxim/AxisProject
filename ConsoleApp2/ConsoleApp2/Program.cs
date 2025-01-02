using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp2
{
    class Program
    {
        static void Main(string[] args)
        {
            bool isRunning = true;

            while (isRunning)
            {
                Console.WriteLine("Selectati operatia pe care doriti sa o realizati");
                Console.WriteLine("1. Adunare");
                Console.WriteLine("2. Scadere");
                Console.WriteLine("3. Inmultire");
                Console.WriteLine("4. Impartire");
                Console.WriteLine("5. Iesire din aplicatie");

                string input = Console.ReadLine();// Citire

                int operation, firstNumber, secondNumber;
                int.TryParse(input, out operation);// TryParse verifica daca gaseste un numar intreg in cadrul sirului dar nu il aloca, spre deosebire
                                                   // de Parse. Daca TryParse gaseste numarul il va aloca intr o variabila separata cu comanda "out [numele variabilei]"

                if (operation == 5)
                {
                    Console.WriteLine("Calculatorul a fost oprit.");
                    return;
                }
                
                Console.WriteLine("Va rog sa introduceti primul numar : ");
                int.TryParse(Console.ReadLine(), out firstNumber);
                Console.WriteLine("Va rog sa introduceti al doilea numar : ");
                int.TryParse(Console.ReadLine(), out secondNumber);

                double result = 0; ;

                switch (operation)
                {
                    case 1:
                        {
                            result = Calculator.Sum(firstNumber, secondNumber);
                            break;
                        }
                    case 2:
                        {
                            result = Calculator.Difference(firstNumber, secondNumber);
                            break;
                        }
                    case 3:
                        {
                            result = Calculator.Multiply(firstNumber, secondNumber);
                            break;
                        }
                    case 4:
                        {
                            result = Calculator.Divide(firstNumber, secondNumber);
                            break;
                        }
                }

                Console.WriteLine($"Rezultatul este : {result}");
            }
        }
    }
}
