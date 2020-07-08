using System.Collections.Generic;


namespace Sorts
{
	public enum SortingMode
	{
		Increase = 1,
		Decrease = -1
	}

	public interface ISort<T>
	{
		void Sort(ref T[] arr, SortingMode mode, IComparer<T> obj, params object[] optional);
	}
}