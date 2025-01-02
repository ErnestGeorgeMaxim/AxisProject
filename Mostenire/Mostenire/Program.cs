using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mostenire
{
    partial class Program
    {
        //Mostenire = capabilitatea de a extinde, modifica sau reutiliza codul deja scris in alte clase
        static void Main(string[] args)
        {
            Dog dog = new Dog();
            dog.Walk();
            dog.MakeSound();

            Cat cat = new Cat();
            cat.Walk();
            cat.MakeSound();
        }
    }
}
