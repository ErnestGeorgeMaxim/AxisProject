using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AnotherAsembly
{
    public class Car
    {
        private protected CarEngine Engine { get; set; }
        public int CurrentGear { get; set; }

        public void StartEngine()
        { Engine.Start(); }

        protected internal void ChangeGear(int gear)
        {
            if(gear > 6 )
            {
                throw new AugmentException();
            }
            CurrentGear = gear;
            Console.WriteLine($"Gear changed to: {gear}");
        }

        internal void Drive()
        {
            if( Engine.IsStarted)
            {

            }
        }
    }
}
