using System;
using System.Linq;
using System.Collections.Generic;
using System.Reflection.Metadata.Ecma335;

namespace Sorts
{
    class Program
    {

        private static Random random = new Random();
        public static string RandomString(int length)
        {
            const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            return new string(Enumerable.Repeat(chars, length)
                .Select(s => s[random.Next(s.Length)]).ToArray());
        }
        static void Main(string[] args)
        {
            Random rnd = new Random();

            var arr1 = new string[10];
            for (int i = 0; i < 10; i++)
                arr1[i] = RandomString(rnd.Next() % 5 + 1);
            Console.WriteLine("Start array:");
            for (int i = 0; i < 10; i++)
                Console.Write("{0} ", arr1[i]);
            Console.WriteLine();
            Console.WriteLine("Sort array::");
            var context2 = new Context<string>();
            context2.SetSort(new HeapSort<string>());
            context2.SortSmth(ref arr1, SortingMode.Increase, new CompareString(), arr1.Length / 2);
            for (int i = 0; i < 10; i++)
                Console.Write("{0} ", arr1[i]);
            Console.WriteLine();


            var arr3 = new int[10];
            for (int i = 0; i < 10; i++)
                arr3[i] = rnd.Next() % 100;
            Console.WriteLine("Start array:");
            for (int i = 0; i < 10; i++)
                Console.Write("{0} ", arr3[i]);
            Console.WriteLine();
            Console.WriteLine("Sort array: :");
            var context3 = new Context<int>();
            context3.SetSort(new HeapSort<int>());
            context3.SortSmth(ref arr3, SortingMode.Decrease, new CompareInt(), arr3.Length / 2);
            for (int i = 0; i < 10; i++)
                Console.Write("{0} ", arr3[i]);
            Console.WriteLine();
        }
        

        public class CompareInt : IComparer<int>
        {
            public int Compare(int a, int b)
            {
                return a.CompareTo(b);
            }
        }

        public class CompareString : IComparer<string>
        {
            public int Compare(string a, string b)
            {
                return a.CompareTo(b);
            }
        }
    }
}