#pragma warning disable CS0659 // Тип переопределяет Object.Equals(object o), но не переопределяет Object.GetHashCode()

using _1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace Complex
{
    public class Complex : ICloneable, IComparable, IComparable<Complex>, IEquatable<Complex>
    {
        private readonly Fraction _real;
        private readonly Fraction _imaginary;

        private readonly Fraction EPS = new Fraction(1, 100);
        private readonly Fraction PI = new Fraction(22, 7);
         
        public Complex(Fraction real, Fraction imag)
        {
            if (real is null)
            {
                throw new ArgumentNullException(nameof(real));
            }
            if (imag is null)
            {
                throw new ArgumentNullException(nameof(imag));
            }

            _real = real;
            _imaginary = imag;
        }

        public Complex(Fraction real) : this(real, new Fraction(0)) { }

      
        public Complex(Complex other) : this(other._real, other._imaginary) { }

        public override string ToString()
        {
            return $"({_real.ToString(5)}) + ({_imaginary.ToString(5)})i";
        }

        #region Interfaces

        public object Clone()
        {
            return new Complex(_real, _imaginary);
        }

        #region Equals

        public override bool Equals(object obj)
        {
            if (obj is null)
                throw new ArgumentNullException(nameof(obj));

            if (obj is Complex other)
                return Equals(other);

            return false;
        }

        public bool Equals(Complex other)
        {
            if (other is null)
                throw new ArgumentNullException(nameof(other));

            return (_real == other._real && _imaginary == other._imaginary);
        }

        #endregion

        #region CompareTo

        public int CompareTo(object obj)
        {
            if (obj is null)
            {
                throw new ArgumentNullException(nameof(obj));
            }
            if (obj is Complex other)
            {
                return CompareTo(other);
            }

            throw new ArgumentException("invalid type");
        }

        public int CompareTo(Complex other)
        {
            if (other is null)
            {
                throw new ArgumentNullException(nameof(other));
            }

            if (Equals(other))
            {
                return 0;
            }
            else if (_real > other._real)
            {
                return 1;
            }
            else if (_real < other._real)
            {
                return -1;
            }
            else if (_imaginary > other._imaginary)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }

        #endregion

        #endregion

        #region Arithmetics

        private static Complex SumOrSub(Complex first, Complex second, Func<Fraction, Fraction, Fraction> operation)
        {
            if (first is null)
            {
                throw new ArgumentNullException(nameof(first));
            }
            if (second is null)
            {
                throw new ArgumentNullException(nameof(second));
            }

            return new Complex(operation(first._real, second._real), operation(first._imaginary, second._imaginary));
        }

        private static Complex Multiply(Complex first, Complex second)
        {
            if (first is null)
            {
                throw new ArgumentNullException(nameof(first));
            }
            if (second is null)
            {
                throw new ArgumentNullException(nameof(second));
            }

            return new Complex(first._real * second._real - first._imaginary * second._imaginary,
                first._real * second._imaginary + first._imaginary * second._real);
        }

        private static Complex Divide(Complex first, Complex second)
        {
            if (first is null)
            {
                throw new ArgumentNullException(nameof(first));
            }
            if (second is null)
            {
                throw new ArgumentNullException(nameof(second));
            }

            return new Complex((first._real * second._real + first._imaginary * second._imaginary) /
                               (second._real.Pow(2) + second._imaginary.Pow(2)),
                        (first._imaginary * second._real - first._real * second._imaginary) /
                                (second._real.Pow(2) + second._imaginary.Pow(2)));
        }

        public Fraction Abs()
        {
            return (_real.Pow(2) + _imaginary.Pow(2)).Sqrt(EPS);
        }

        public Fraction Argument()
        {
            Fraction arg = new Fraction(_imaginary / _real);
            var x = _imaginary / _real;
            Fraction ptr = new Fraction(-1);
            Fraction sum = new Fraction(0);

            //невозможно разложить в ряд тангенс значение = 1
            if (x.Abs() == new Fraction(1))
                throw new ArithmeticException("There is no tg(x)");

            if (x.Abs() > new Fraction(1))
            {
                x = x.Flip();
                arg = x;

                for (int i = 3; i < Int32.MaxValue - 2; i += 2)
                {
                    arg += ptr * x.Pow(i) / i;
                    if ((arg.Abs() - sum.Abs()).Abs() < EPS)
                        break;
                    sum = arg;
                    ptr = ptr * (-1);
                }

                return new Fraction((PI / 2 - arg));
            }

            for (int i = 3; i < Int32.MaxValue - 2; i += 2)
            {
                arg += ptr * x.Pow(i) / i;
                if ((arg.Abs() - sum.Abs()).Abs() < EPS)
                    break;
                sum = arg;
                ptr = ptr * (-1);
            }

            return arg;
            
        }

        public Complex[] SqrtN(int pow)
        {
            if (pow < 0)
                throw new ArgumentException(nameof(pow));

            Complex[] arr = new Complex[pow];

            for (int i = 0; i < pow; i++)
            {
                arr[i] = new Complex((this.Abs().Sqrt(EPS, pow) + PI * 2 * i) * (this.Argument() / pow).Cos(EPS),
                    (this.Abs().Sqrt(EPS, pow) + PI * 2 * i) * (this.Argument() / pow).Sin(EPS));
            }

            return arr;
        }

        public Complex Pow(int pow)
        {
            if (pow < 0)
                throw new ArgumentException("Возведение в отрицательную степень невозможно");
            return new Complex(this.Abs().Pow(pow) * (this.Argument() * pow).Cos(EPS),
                              this.Abs().Pow(pow) * (this.Argument() * pow).Sin(EPS));
        }

        public static Complex operator +(Complex a, Complex b)
        {
            return SumOrSub(a, b, (Fraction x, Fraction y) => x + y);
        }

        public static Complex operator -(Complex a, Complex b)
        {
            return SumOrSub(a, b, (Fraction x, Fraction y) => x - y);
        }

        public static Complex operator *(Complex first, Complex second)
        {
            return Multiply(first, second);
        }

        public static Complex operator /(Complex first, Complex second)
        {
            return Divide(first, second);
        }

        #endregion

    }
}
