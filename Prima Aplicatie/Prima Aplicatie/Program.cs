using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Prima_Aplicatie
{
    class Program
    {
        public struct Complex
        {
            public double Real { get; set; }
            public double Imaginar { get; set; }
        }
        public static Complex operator +(Complex c1, Complex c2)
        {
            return new Complex
            {
                Real = c1.Real + c2.Real,
                Imaginar = c1.Imaginar + c2.Imaginar
            };
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");
            Console.Read();

            string s = @"The path is:
            C:\Windows\System32"; // Secventa Escape - ia in seama spatiile

            Complex a = new Complex() { Real = 1, Imaginar = 2 };
            Complex b = new Complex() { Real = 4, Imaginar = 8 };
            Complex c = a + b;
            
        }
    }
}
