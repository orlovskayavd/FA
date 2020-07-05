using System;
using System.ComponentModel.Design;
using System.IO;
using System.Numerics;

namespace _1
{
    class Program
    {
        static void Main(string[] args)
        {
            Fraction eps = new Fraction(1, 10);
            Fraction f1 = new Fraction(2, -6);
            Console.WriteLine("First is {0} \n", f1);
            Fraction f2 = new Fraction(1, 2);
            Console.WriteLine("Second is {0} \n", f2);
            Fraction f3 = f1 + f2;
            Console.WriteLine("Sum of first and second {0} \n", f3);
            Fraction f4 = f1 - f2;
            Console.WriteLine("Sub of first and second {0} \n", f4);
            Fraction f5 = f1 * f2;
            Console.WriteLine("Mul of first and second {0} \n", f5);            
            try
            {
                Fraction f6 = f1 / new Fraction(0, 1);
                Console.WriteLine("Div of first and second; {0} \n, f6");
            }
            catch (ArithmeticException ex)
            {
                Console.WriteLine(ex.Message);
            }
            Fraction f7 = Fraction.Pow(f1, 2);
            Console.WriteLine("First^2 is {0} \n", f7);
            Fraction f8 = Fraction.Pow(f1, -3);
            Console.WriteLine("First^(-3) is {0} \n", f8);
            string str = Fraction.ToDoubleString(f1, 4);
            Console.WriteLine("First is {0} \n", str);
            Console.WriteLine("Sqrt from {0} is {1} \n", f2, Fraction.ToDoubleString(Fraction.Sqrt_Fraction(f2, Fraction.Pow(eps, 1000)), 1000));
            Console.WriteLine("f1 == f2 is {0} \n", f1 == f2);
            //Console.WriteLine("f2 == f2 is {0} \n", f2 == f2);
            Console.WriteLine("f1 > f2 is {0} \n", f1 > f2);

        }
    }
}
