using System;

namespace Aplic1
{
    public class Program
    {
        static void Main(string[] args)
        {
            /*Console.ForegroundColor = ConsoleColor.Black;
            Console.BackgroundColor = ConsoleColor.White;
            Console.Clear();
            Console.WriteLine("Hello World!");
            */

            /*
            Console.Write("What is your name? ");
            string name = Console.ReadLine();
            Console.WriteLine($"Hello {name}!"); // {name} preia valoarea variabilei
                                                 // name de mai sus
            */

            bool canIVote = true; ///tipul bool

            /// tipul int
            Console.WriteLine("Biggest Integer : {0}",int.MaxValue );
            Console.WriteLine("Smallest Integer : {0}",int.MinValue );

            /// tipul long
            Console.WriteLine("Biggest Long : {0}",long.MaxValue );
            Console.WriteLine("Smallest Long : {0}",long.MinValue );

            /// tipul decimal
            decimal decPiVal = 3.1415926535897932384626433832M;
            decimal decBigNum = 3.00000000000000000000000000011M;

            Console.WriteLine("DEC : PI + BigNum = {0}", decPiVal + decBigNum);

            Console.WriteLine();

            Console.WriteLine("Biggest Decimal : {0}", Decimal.MaxValue);
            Console.WriteLine("Smallest Decimal : {0}", Decimal.MinValue);
            
            
            ///Double
            Console.WriteLine("Biggest Double : {0}", Double.MaxValue);
            Console.WriteLine("Smallest Double : {0}", Double.MinValue);

            double piVal = 3.14159265358979;
            double bigNum = 3.00000000000002;

            Console.WriteLine("DBL : PI + BigNum = {0}", piVal + bigNum);


            ///Float
            Console.WriteLine("Biggest Float : {0}", float.MaxValue);
            Console.WriteLine("Smallest Float : {0}", float.MinValue);

            double fpiVal = 3.141592F;
            double fbigNum = 3.000002F;

            Console.WriteLine("float : PI + BigNum = {0}", fpiVal + fbigNum);


            /**
             * Alte tipuri de date:
             * - byte: 8-biti , unsigned int de la 0 la 255
             * - char: 16-biti , caracter unicode
             * - sbyte: 8-biti , signed int de la 128 la 127
             * - short: 16-biti , signed int de la -32,768 la 32,767
             * - uint: 32-biti , unsigned int de la 0 la 4,294,967,295
             * - ulong: 64-biti , unsigned long de la 0 la 18,446,744,073,709,551,615
             * - ushort: 16-biti , unsigned short de la 0 la 65,535
             */

            bool boolFromStr = bool.Parse("true");
            int intFromStr = int.Parse("100");
            double doubleFromStr = double.Parse("1.234");
            string strVal = doubleFromStr.ToString();
            Console.WriteLine($"Data type : {strVal.GetType()}");

            double dblNum = 12.345;
            Console.WriteLine($"Integer : {(int)dblNum}");
            int intNum = 10;
            long longNum = intNum;


            Console.WriteLine("Currency : {0:c}", 23.455);
            Console.WriteLine("Pad with 0s : {0:d4}", 23);
            Console.WriteLine("3 Decimals : {0:f3}", 23.45555);
            Console.WriteLine("Commas : {0:n4}", 2300);






        }
    }
}
