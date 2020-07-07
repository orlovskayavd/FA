using System;
using System.Xml.Schema;
using _1;

namespace _3
{
    class Program
    {
        public static Fraction func1(Fraction first)
        {
            Fraction some_constant = new Fraction(3, 1);
            return first - some_constant;
        }

        public static Fraction func2(Fraction first)
        {
            Fraction some_constant = new Fraction(4, 1);
            return first = first - some_constant;
        }

        public delegate Fraction AddDelegate(Fraction first);

        public static Fraction Solution_of_this_lab(Fraction left, Fraction right, AddDelegate func, Fraction eps)
        {
            Fraction frac_zero = new Fraction(0, 1);

            if (func(left) * func(right) > frac_zero)
            {
                throw new Exception("Wrong interval: func(left) * func(right) > frac_zero!");
            }
            if (left >= right)
            {
                throw new Exception("Wrong interval: left >= right!");
            }
            Fraction two = new Fraction(2, 1);
            Fraction minus_one = new Fraction(-1, 1);
            Fraction middle = (left + right) / two;
            Fraction length = right - left;
            
            if ((func(middle) < eps) && (func(middle) * minus_one < eps))
            {
                return middle;
            }
            if (length < eps)
            {
                Console.WriteLine("length < eps");
                return middle;
            }
            if (func(middle) * func(left) <= frac_zero)
            {
                return Solution_of_this_lab(left, middle, func, eps);
            }
            else
            {
                return Solution_of_this_lab(middle, right, func, eps);
            }
        }

        static void Main(string[] args)
        {
            AddDelegate del1 = new AddDelegate(func1);
            Fraction left_border1 = new Fraction(0, 1);
            Fraction right_border1 = new Fraction(4, 1);
            Fraction eps1 = new Fraction(1, 10000000); // 10^(-7)
            Console.WriteLine("First root is {0} \n", Solution_of_this_lab(left_border1, right_border1, del1, eps1));


            AddDelegate del2 = new AddDelegate(func2);
            Fraction left_border2 = new Fraction(-2, 1);
            Fraction right_border2 = new Fraction(6, 1);
            Fraction eps2 = new Fraction(1, 1000000); // 10^(-6)
            Console.WriteLine("Second root is {0} \n", Solution_of_this_lab(left_border2, right_border2, del2, eps2));
        }
    }
}
