using System;

namespace Valid
{
    class Program
    {
        public class Test
        {
            public int _number;
            public string _word;
        }
        static void Main(string[] args)
        {
            var valid = Validator<Test>.CreateBuilder().AddRule(data => data._number > 18 && data._number % 2 < 22)
                .AddRule(data => data._word.Length > 5 && data._word.StartsWith("Hello Word"))
                .GetValidator();

            try
            {
                valid.Validate(new Test() { _number = 19, _word = "Hello Word" });
                Console.WriteLine("the object is correct");
            }
            catch (ArgumentException error)
            {
                Console.WriteLine(error);
            }

            try
            {
                valid.Validate(new Test() { _number = 17, _word = "Hello Word" });
                Console.WriteLine("the object is correct");
            }
            catch (ArgumentException error)
            {
                Console.WriteLine(error);
            }
        }
    }
}