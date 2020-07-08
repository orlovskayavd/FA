using System;
using System.Collections.Generic;

namespace Sorts
{
    class Context<T>
    {
        private ISort<T> _sort;

        public Context() { }

        public Context(ISort<T> sort)
        {
            if (sort is null)
                throw new ArgumentNullException(nameof(sort));

            this._sort = sort;
        }

        public void SetSort(ISort<T> sort)
        {
            if (sort is null)
                throw new ArgumentNullException(nameof(sort));

            this._sort = sort;
        }

        public void SortSmth(ref T[] array, SortingMode mode, IComparer<T> obj, params object[] optional)
        {
            if (array is null)
                throw new ArgumentNullException(nameof(array));

            if (obj is null)
                throw new ArgumentNullException(nameof(obj));

            T[] newArray = (T[])array.Clone();
            _sort.Sort(ref array, mode, obj, optional);
            array = newArray;
        }
    }

    #region Sorts
    public class HeapSort<T> : ISort<T>
    {
        public void Sort(ref T[] array, SortingMode mode, IComparer<T> obj, params object[] optional)
        {
            if (array is null)
                throw new ArgumentNullException(nameof(array));

            if (obj is null)
                throw new ArgumentNullException(nameof(obj));

            int count = array.Length;
            for (int i = count / 2 - 1; i >= 0; i--)
                Heap(ref array, count, i, obj, mode);

            for (int i = count - 1; i >= 0; i--)
            {
                Swap(ref array[0], ref array[i]);
                Heap(ref array, i, 0, obj, mode);
            }
        }

        private void Heap(ref T[] array, int count, int i, IComparer<T> obj, SortingMode mode)
        {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < count && obj.Compare(array[left], array[largest]) == (int)mode)
                largest = left;

            if (right < count && obj.Compare(array[right], array[largest]) == (int)mode)
                largest = right;

            if (largest != i)
            {
                Swap(ref array[i], ref array[largest]);
                Heap(ref array, count, largest, obj, mode);
            }
        }

        private void Swap(ref T a, ref T b)
        {
            T temp = a;
            a = b;
            b = temp;
        }
    }

    public class ShellSort<T> : ISort<T>
    {
        public void Sort(ref T[] array, SortingMode mode, IComparer<T> obj, params object[] optional)
        {
            if (array is null)
                throw new ArgumentNullException(nameof(array));

            if (obj is null)
                throw new ArgumentNullException(nameof(obj));

            if (optional.Length == 0)
                throw new ArgumentException("Invalid step");

            if ((int)optional[0] < 1 && (int)optional[0] >= array.Length)
                throw new ArgumentException("Invalid step");

            int step = (int)optional[0];

            while (step > 0)
            {
                for (int i = step; i < array.Length; i++)
                {
                    int j;
                    var value = array[i];

                    for (j = i - step; (j >= 0) && obj.Compare(array[j], value) == (int)mode; j -= step)
                        array[j + step] = array[j];
                    array[j + step] = value;
                }
                step /= 2;
            }
        }
    }

    #endregion
}