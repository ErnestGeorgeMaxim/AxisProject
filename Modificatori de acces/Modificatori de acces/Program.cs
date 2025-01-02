using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AnotherAsembly;

namespace Modificatori_de_acces
{
    // programele declarate cu namespace pot fi declarate numai cu public sau internal
    internal class Program
    {
        static void Main(string[] args)
        {
            // public , private, protected, internal, protected internal, private protected


            Car car = new Car();
        }

        protected class Test
        {

        }
    }
}
