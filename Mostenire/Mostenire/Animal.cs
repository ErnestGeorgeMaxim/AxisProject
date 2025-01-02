using System;

namespace Mostenire
{

    // sealed = sigilat
    // nu mai putem extinde aceasta clasa, adica nu mai poate avea mostenitori
    public /*sealed*/ class Animal
   {
        // virtual = ajuta la suprascrierea unei clase parinte intr una copil
        // fara acest virtual clasa mostenitoarea nu poate sa faca override
        public virtual void Walk()
        {
            Console.WriteLine("Starts walking ...");
        }

        public virtual void MakeSound()
        {
            Console.WriteLine("Makes generic animal sound. "); 
        }
    
   }
}
