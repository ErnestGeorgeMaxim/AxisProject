using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Aplic3_Array
{
    class Program
    {
        // -------------Functii----------------


        static void PrintArray(int[] intArray, string mess)
        {
            foreach(int k in intArray)
            {
                Console.WriteLine("{0} : {1}", mess, k);
            }
        }
        // -------------Finalul Functiilor----------------
        static void Main(string[] args)
        {
            int[] favNum = new int[3];
            favNum[0] = 23;
            Console.WriteLine("favNum 0 : {0}", favNum[0]);

            string[] customers = { "Bob", "Sally", "Sue" };

            var employees = new[] { "Mike", "Jordan", "Stromy", "Culture" };
            object[] randomArray = { "Jordan", 45, 1.234 };
            Console.WriteLine("randomArray 0 : {0}", randomArray[0].GetType());
            Console.WriteLine("randomArray 1 : {0}", randomArray[1].GetType());
            Console.WriteLine("randomArray 2 : {0}", randomArray[2].GetType());
            Console.WriteLine("Array Size : {0}", randomArray.Length);
            for (int j = 0; j < randomArray.Length; j++)
            {
                Console.WriteLine("Array : {0} Value : {1}", j, randomArray[j]);
            }

                                                    //   0       1
            string[,] custNames = new string[2, 2] { { "Bob", "Smith" }, /// 0
                                                    { "Sally", "Smith" } }; /// 1
            Console.WriteLine("MultiDimensional Value : {0}", custNames.GetValue(1,1));
            /// GetValue(1,1) ---> Smith(i = 1, j = 1);
            
            for( int i = 0; i < custNames.GetLength(0); i++)
            {
                for (int j = 0; j < custNames.GetLength(0); j++)
                {
                    Console.WriteLine("{0}", custNames[i,j]);
                }
                Console.WriteLine();
            }

            int[] randNums = { 1, 4, 9, 2};// Sortat : 1, 2, 4, 9
            PrintArray(randNums, "foreach");

            Array.Sort(randNums);// sortare
            PrintArray(randNums, "Sort");

            Array.Reverse(randNums); // sortare inversa
            PrintArray(randNums, "Reverse");

            Console.WriteLine("1 at index of : {0}", Array.IndexOf(randNums, 1));
            randNums.SetValue(0, 1);// Inlocuieste o valoare din sir 
            PrintArray(randNums, "Set");
            int[] srcArray = { 1, 2, 3 };
            int[] dstArray = new int[2];
            int startInd = 0;
            int length = 2;
            Array.Copy(srcArray, startInd, dstArray, 0, length);
            PrintArray(dstArray, "Copy");
            Array anotherArray = Array.CreateInstance(typeof(int), 10);
            srcArray.CopyTo(anotherArray, 5);
            foreach(int m in anotherArray)
            {
                Console.WriteLine("CopyTo : {0}", m);
            }
            int[] numArray = { 1, 11, 22 };


             

        }
    }
}
