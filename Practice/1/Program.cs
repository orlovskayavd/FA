using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using Fractions;
using _1;

namespace Complex
{
    class Program
    {
        static void Main(string[] args)
        {
            Fraction f1 = new Fraction(2, -6);
            Fraction f2 = new Fraction(1, 2);
            Complex a = new Complex(f1, f2);
            Complex b = new Complex(f2, f1);
            Console.WriteLine("First is {0} \n", a);
            Console.WriteLine("Second is {0} \n", b);
            Console.WriteLine("Sum: a + b is {0} \n", a + b);
            Console.WriteLine("Sub: a - b is {0} \n", a - b);
            Console.WriteLine("Mult: a * b is {0} \n", a * b);

            try
            {
                Console.WriteLine("Div: a / b is {0} \n", a / b);
            }
            catch (DivideByZeroException ex)
            {
                Console.WriteLine(ex.Message);
            }

            Console.WriteLine("First^2 is {0} \n", a.Pow(2));
            Console.WriteLine("First arg is {0} \n", b, b.Argument().ToString(20));

            Console.WriteLine("Abs: {0} = {1}", a, a.Abs().ToString(10));
            //Complex a = new Complex(new Fraction(1, -2), new Fraction(1, 8)), b = new Complex(new Fraction(1, 2), new Fraction(1, 6));

            //Console.WriteLine("Sum: {0} + {1} = {2}", a, b, a + b);
            //Console.WriteLine("Sub: {0} - {1} = {2}", a, b, a - b);
            //Console.WriteLine("Mult: {0} * {1} = {2}", a, b, a * b);

            //try
            //{
            //    Console.WriteLine("Div: {0} / {1} = {2}", a, b, a / b);
            //}
            //catch (DivideByZeroException ex)
            //{
            //    Console.WriteLine(ex.Message);
            //}

            //Console.WriteLine("Arg: {0} = {1}", b, b.Argument().ToString(20));
            //Console.WriteLine("Abs: {0} = {1}", a, a.Abs().ToString(10));
            //Console.WriteLine("Pow: ({0})^10 = {1}", a, a.Pow(10));

            //var pow = 5;
            //Complex[] arr = a.SqrtN(pow);

            //try
            //{
            //    for (int i = 0; i < pow; i++)
            //        Console.WriteLine("Sqrt number - {0}: {1}", i, arr[i]);
            //}
            //catch (ArgumentException ex)
            //{
            //    Console.WriteLine(ex.Message);
            //}
            //Console.WriteLine("({0}).CompareTo({1}) = {2}", a, b, a.CompareTo(b));
            //Console.WriteLine("Equals: {0} and {1} - {2}", a, b, a.Equals(b));
        }
    }
}
