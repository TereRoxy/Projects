using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EnvSetupSE
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ulong suma = 0;
            for (ulong i=1; i<=100_000_001; i++)
            {
                if(i % 2 == 1)
                {
                    suma = suma + i * i - (i - 1) +  i * i ;
                }
                else
                {
                    suma = suma + i * i - i + 1 + i * i + 1;
                }
            }
            suma = suma - 1;
            //print result
            Console.WriteLine("Suma: " + suma);
            Console.ReadLine();
        }
    }
}
