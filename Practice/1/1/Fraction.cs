#pragma warning disable CS0659
#pragma warning disable CS0661

using System;
using System.Collections.Generic;
using System.Numerics;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.Serialization;
using System.Text;

namespace _1
{
    public class Fraction : object, ICloneable, IEquatable<Fraction>, IComparable, IComparable<Fraction>
    {
        private BigInteger _numerator, _denominator;

        public Fraction(BigInteger a, BigInteger b) // fraction a/n
        {
            if (b == 0)
            {
                throw new ArithmeticException("Denominaror is zero!!!");
            }
            _numerator = BigInteger.Abs(a);
            _denominator = BigInteger.Abs(b);
            BigInteger GCD = BigInteger.GreatestCommonDivisor(_numerator, _denominator);
            _numerator /= GCD;
            _denominator /= GCD;
            if (a * b != BigInteger.Abs(a * b))
            {
                _numerator *= -1;
            }
        }

        public object Clone()
        {
            return new Fraction(this._numerator, this._denominator);
        }

        public static string ToDoubleString(Fraction first, int how_many)
        {
            if (first is null)
            {
                throw new ArgumentNullException("Smtf is null. Forbidden.");
            }
            if (how_many < 1)
            {
                throw new ArithmeticException("No. Only 1 and more.");
            }
            var sb = new StringBuilder();
            if (first._numerator < 0)
            {
                sb.Append("-");
            }
            sb.Append(BigInteger.Abs(first._numerator / first._denominator)); sb.Append(".");
            BigInteger numerator_copy;
            BigInteger multipler = 1;
            for (int i = 0; i < how_many; i++)
            {
                multipler *= 10;
                numerator_copy = BigInteger.Abs(first._numerator * multipler);

                sb.Append((numerator_copy / first._denominator) % 10);

            }
            return sb.ToString();
        }

        //internal static object Sqrt_Fraction(Fraction f2)
        //{
        //    throw new NotImplementedException();
        //}

        public override string ToString()
        {
            var sb = new StringBuilder();
            sb.Append(_numerator); sb.Append("/"); sb.Append(_denominator);
            return sb.ToString();
        }

        #region Arithmetic

        public static Fraction Sum(Fraction first, Fraction second)
        {
            if (first is null || second is null)
            {
                throw new ArgumentNullException("Smtf is null. Forbidden.");
            }
            Fraction result = new Fraction(first._numerator * second._denominator + second._numerator * first._denominator, first._denominator * second._denominator);
            return result;
        }

        public static Fraction operator +(Fraction first, Fraction second)
        {
            return Sum(first, second);
        }

        public static Fraction Sub(Fraction first, Fraction second)
        {
            if (first is null || second is null)
            {
                throw new ArgumentNullException("Smtf is null. Forbidden.");
            }
            Fraction result = new Fraction(first._numerator * second._denominator - second._numerator * first._denominator, first._denominator * second._denominator);
            return result;
        }

        public static Fraction operator -(Fraction first, Fraction second)
        {
            return Sub(first, second);
        }

        public static Fraction Mul(Fraction first, Fraction second)
        {
            if (first is null || second is null)
            {
                throw new ArgumentNullException("Smtf is null. Forbidden.");
            }
            Fraction result = new Fraction(first._numerator * second._numerator, first._denominator * second._denominator);
            return result;
        }

        public static Fraction operator *(Fraction first, Fraction second)
        {
            return Mul(first, second);
        }

        public static Fraction Div(Fraction first, Fraction second)
        {
            if (first is null || second is null)
            {
                throw new ArgumentNullException("Smtf is null. Forbidden.");
            }
            if (second._numerator == 0)
            {
                throw new ArithmeticException("Divided by zero");
            }
            Fraction result = new Fraction(first._numerator * second._denominator, first._denominator * second._numerator);
            return result;
        }

        public static Fraction operator /(Fraction first, Fraction second)
        {
            return Div(first, second);
        }

        public static Fraction Pow(Fraction first, int pow)
        {
            if (first is null)
            {
                throw new ArgumentNullException("Null in some pow. Forbidden.");
            }
            if (pow < 0)
            {
                Fraction res = new Fraction(BigInteger.Pow(first._denominator, Math.Abs(pow)), BigInteger.Pow(first._numerator, Math.Abs(pow)));
                return res;
            }
            Fraction result = new Fraction(BigInteger.Pow(first._numerator, pow), BigInteger.Pow(first._denominator, pow));
            return result;
        }

        //public static double Sqrt(Fraction first)
        //{
        //    if (first._numerator < 0)
        //    {
        //        throw new ArithmeticException("Fraction < 0, error. Complex square root.");
        //    }
        //    const double EPS = 1E-10;
        //    double to_double = (double)first._numerator / (double)first._denominator;
        //    double x = 1;
        //    int count = 0;
        //    for (; ; )
        //    {
        //        count++;
        //        double nx = (x + to_double / x) / 2;
        //        if (Math.Abs((x - nx)) < EPS) break;
        //        x = nx;
        //        if (count > 10000)
        //            throw new ArithmeticException("We can`t find sqrt");
        //    }
        //    return x;
        //}

        public static Fraction Sqrt_Fraction(Fraction first, Fraction eps)
        {
            if (first._numerator < 0)
            {
                throw new ArithmeticException("Fraction < 0, error. Complex square root.");
            }
            Fraction x = new Fraction(1, 1);
            Fraction two = new Fraction(2, 1);
            for (; ; )
            {
                Fraction nx = (x + first / x) / two;
                if (x - nx < eps && nx - x < eps) break;
                x = nx;
            }
            return x;
        }
        #endregion

        #region Equals and comparables

        // Matrix a, b;
        // a.Equals(b);
        public override bool Equals(object obj)
        {
            if (obj is null)
            {
                return false;
            }

            if (obj is Fraction)
            {
                return Equals(obj as Fraction);
            }

            return false;
        }

        public bool Equals(Fraction obj)
        {
            if (obj is null)
            {
                return false;
            }

            if (_numerator != obj._numerator || _denominator != obj._denominator)
            {
                return false;
            }

            return true;
        }

        public static bool operator ==(Fraction first, Fraction second)
        {
            if (ReferenceEquals(first, null) && second is null)
            {
                return true;
            }
            else if (first is object && second is null)
            {
                return first.Equals(second);
            }
            else
            {
                return second.Equals(first);
            }
        }

        public static bool operator !=(Fraction first, Fraction second)
        {
            return !(first == second);
        }


        public int CompareTo(object obj)
        {
            if (obj is null)
            {
                throw new ArgumentNullException(paramName: "obj can't be null");
            }
            if (obj is Fraction)
            {
                return CompareTo(obj as Fraction);
            }
            else throw new ArgumentException("Object is not a fraction");
        }

      
        public int CompareTo(Fraction obj)
        {
            if (obj is null)
            {
                throw new ArgumentNullException(paramName: "Fraction can't be null");
            }
            if (this._numerator * obj._denominator > obj._numerator * this._denominator)
            {
                return 1;
            }
            if (this._numerator * obj._denominator == obj._numerator * this._denominator)
            {
                return 0;
            }
            return -1;
        }
        

        // Define the is greater than operator.
        public static bool operator >(Fraction operand1, Fraction operand2)
        {
            return operand1.CompareTo(operand2) == 1;
        }

        // Define the is less than operator.
        public static bool operator <(Fraction operand1, Fraction operand2)
        {
            return operand1.CompareTo(operand2) == -1;
        }

        // Define the is greater than or equal to operator.
        public static bool operator >=(Fraction operand1, Fraction operand2)
        {
            return operand1.CompareTo(operand2) >= 0;
        }

        // Define the is less than or equal to operator.
        public static bool operator <=(Fraction operand1, Fraction operand2)
        {
            return operand1.CompareTo(operand2) <= 0;
        }

        #endregion
    }
}

