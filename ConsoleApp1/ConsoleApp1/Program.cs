using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            string firstName = "Bogdan";
            var secondName = 2; // var aloca automat tipul de data asignat 


            /*
             *                  Tipuri de date in C#
             *                  
             *  + string -> pentru siruri de caractere, fiecare caracter din sir
             *              reprezinta un char;
             *  + char -> pentru caractere unice(i se aloca un singur caracter);
             *  + int -> tip intreg;
             *  + double -> tip real; 
             *  + bool -> tip boolean (true sau false);
             */

            string sentance = "Numele meu este Ernest!";
            char letter = 'c';

            int firstNumber = 1;
            double secondNumber = 1.2;
            float thirdNumber = 1.3f;

            bool condition = true;
            bool condition2 = false;

            /*
             *                        Operatori 
             *                        
             *  1. Aritmetici : +, -, *, /, %, ++, --;
             */
            double sum = firstNumber + secondNumber; // 1 + 1.2 = 2.2
            Console.WriteLine(sum);
            // firstNumber va lua valoarea 2 (1 + 1 = 2 )
            firstNumber++;
            // firstNumber va lua din nou valoarea 1
            firstNumber--;


            /*
             * 2. Operatorii relationali(de comparatie) : ==, !=, >, <, >=, <=;
             * 
             *  + == : firstNumber == secondNumber -> bool true/false;
             *  + != : firstNumber != secondNumber -> bool true/false;
             *  + >, <, >=, <= : exact ca in matematica;
             */

            /*
             * 3. Operatorii logici : &&(si), ||(sau), !(negatie)ș
             * firstNumber == secondNumber && secondNumber == thirdNumber
             *          ------> false
             *          
             * firstNumber == secondNumber || secondNumber == thirdNumber
             *          ------> false
             */

            /*
             * 4. Operatorii de atribuire sau asignare: +=, =, -=, /=, *=, %=;
             * 
             */
            firstNumber += 2;
            // firstNumber va avea valoare 1 + 2 = 3;

            firstNumber *= 2; // va avea valoarea 6;

            /*
             *               Secvente de flowcontrol
             *  + if(daca) ->
             *  + for(pentru) ->
             *  + foreach(pentru fiecare) ->
             *  + while(cat timp) ->
             *  + do/while(fa atat timp) ->
             *  + switch(schimba) ->
             *  
             */

            //-------if/else(daca/altfel)

            int number = 1;
            //if( number > 1 )
            //{ 
            //    Console.WriteLine("Numarul este mai mare ca 1.");
            //}
            //else
            //{
            //    Console.WriteLine("Numarul este mai mic sau egal cu 1.");
            //}

            //------for(pentru)

            //for(int i = 0; i < 10; i++)
            //{
            //    Console.WriteLine(i);
            //}

            //------foreach(pentru fiecare)

            //int[] numere = new int[] { 1, 2, 3 };
            //string[] cuvinte = new string[] { "unu", "doi", "trei" };
            //foreach(int i in numere)// pentru fiecare numar i in numere fa ceva
            //{
            //    Console.WriteLine(i);
            //}

            //foreach(string e in cuvinte)
            //{
            //    Console.WriteLine(e);
            //}


            //--------while(cat timp)

            //while( number < 10)
            //{
            //    Console.WriteLine(number);
            //    number++;
            //}


            //--------do/while(repeta pana cand)

            //do
            //{
            //    number++; 
            //    Console.WriteLine(number);
            //} while (number < 10);

            //--------switch(schimba)

            //switch(number)
            //{
            //    case 1: // daca val lui number este 1 
            //        Console.WriteLine("Number este 1");
            //        break;
            //    case 2: // daca val lui number este 2
            //        Console.WriteLine("Number este 2");
            //        break;
            //    case 3: // daca val lui number este 3  
            //        Console.WriteLine("Number este 3");
            //        break;
            //    case 4: // daca val lui number este 4 
            //        Console.WriteLine("Number este 4");
            //        break;
            //    case 5: // daca val lui number este 5 
            //        Console.WriteLine("Number este 5");
            //        break;
            //    case 6: // daca val lui number este 6 
            //        Console.WriteLine("Number este 6");
            //        break;
            //    case 7: // daca val lui number este 7 
            //        Console.WriteLine("Number este 7");
            //        break;
            //    case 8: // daca val lui number este 8 
            //        Console.WriteLine("Number este 8");
            //        break;
            //    case 9: // daca val lui number este 9 
            //        Console.WriteLine("Number este 9");
            //        break;
            //    case 10: // daca val lui number este 10 
            //        Console.WriteLine("Number este 10");
            //        break;
            //}

            Person person = new Person(19, "Ernest"); // instantierea unei clase

            // fara static
            person.DisplayPerson(); // Person name: Ernest, Age: 19 

            Calculator calculator = new Calculator();
            //calculator.Sum(1,2); - nu se poate 
            // static, metoda care nu poate fi accesata printr o instanta
            int suma = Calculator.Sum(1, 2);
            Console.WriteLine(suma);

            int div = Calculator.Divide(4,2);
            Console.WriteLine(div);

            int dif = Calculator.Difference(4, 3);
            Console.WriteLine(dif);

            int inmultire = Calculator.Multiply(4, 3);
            Console.WriteLine(inmultire);
        }
    }
 
    class Person
    {
        // variabilele instantei 

        // Getters and Setters
        //private int age;

        //public void setAge(int age)
        //{
        //    age = age;
        //}
        //public int getAge()
        //{
        //    return age; 
        //}
        // ce este mai sus e echivalentul la ce este sub
        public int Age { get; set; } // la asta
                                   
        // pentru a scrie acesti getters and setters putem scrie
        // prop si dupa apasam tab de 2 ori
        // prop + tab + tab
        public string Name { get; set; }

        // constructor
        public Person(int age, string name)
        {
            Age = age;
            Name = name;
        }
        
        //privat - apartine doar clasei respective, neputand fi utilizata in afara clasei
        //public - poate fi folosita si in afara clasei

        // metode
        public void DisplayPerson()
        {
            Console.WriteLine("Person name: " + Name + ", Age: " + Age);
        }
    }
}
