using System;

namespace Aplic2_String_
{
    class Program
    {
        static void Main(string[] args)
        {
            string randString = "This is a string";
            Console.WriteLine("String Length : {0}", randString.Length);// Lungimea
            Console.WriteLine("String Contains is : {0}", randString.Contains("is"));// Contine is? (True or False)
            Console.WriteLine("Index of is : {0}", randString.IndexOf("is"));// Numarul de aparitii ale lui is in string
            Console.WriteLine("Remove String : {0}", randString.Remove(10,6));// Elimina 
            Console.WriteLine("Insert String : {0}", randString.Insert(10, "short"));//Inseraza
            Console.WriteLine("Replace String : {0}", randString.Replace("string", "sentance"));// Inlocuieste string cu sentance
            Console.WriteLine("Compare A to B : {0}", String.Compare("A", "B", StringComparison.OrdinalIgnoreCase));// Compara
            Console.WriteLine();
            Console.WriteLine();

            /**
             * Comparatia stringurilor sau cazul de ignorecase :
             * - <0 : str1 e mai mare decat str2
             * - = : egalitate
             * - >0 : str2 e mai mare decat str1
             */
            Console.WriteLine("A = a : {0}",String.Equals("A","a",StringComparison.OrdinalIgnoreCase));//verifica valoarea de adevar
            Console.WriteLine("Pad Left : {0}", randString.PadLeft(20, '.')); // ....cuv
            Console.WriteLine("Pad Right : {0}", randString.PadRight(20, '.')); // cuv....
            Console.WriteLine("Trim : {0}", randString.Trim());
            Console.WriteLine("Uppercase : {0}", randString.ToUpper());//Transforma toate literele in uppercase
            Console.WriteLine("Lowercase : {0}", randString.ToLower());//Transforma toate literele in lowercase

            string newString = String.Format("{0} saw a {1} {2} in the {3}",
                "Paul", "rabbit", "eating", "field");//formateaza stringul 
            Console.Write(newString + "\n");
            // Caracter escape : \' \" \\ \t \a 

            Console.WriteLine(@"Exactly what i typed\n");


            /// ------------------- ARRAYS -----------------------------

           
        }
    }
}
