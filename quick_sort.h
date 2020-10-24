#include <cassert>

#include "utils.h"
#include "insertion_sort.h"
#include "random.h"

template <typename T>
class quick_sort
{
	public:
		static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>())
		{
			std_random<T> rand;
			rand.shuffle(arr, n);
			sort(arr, 0, n-1, comp);
			assert(is_sorted(arr, n, comp));
		}

	private:
		static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp)
		{
			if(high <= low){return;}
			size_t j = partition(arr, low, high, comp);
			sort(arr, low, j-1, comp);
			sort(arr, j+1, high, comp);
			assert(is_sorted(arr, low, high, comp));
		}

		static size_t partition(T* arr, size_t low, size_t high, const comparator<T>& comp)
		{
			size_t i = low, 
				   j = high+1;

			T part_elem = arr[low];
			while(true)
			{
				while(less(arr[++i],part_elem,comp))
				{ if(i == high){break;} }

				while(less(part_elem,arr[--j],comp))
				{ if(j == low){break;} }

				if(i >= j){ break; }
				exchange(arr, i, j);
			}
			exchange(arr, low, j);
			return j;
		}

};

template <typename T>
class quick_sort_3way
{
	static const int CUTOFF_ = 5;

	public:

		static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>())
		{
			std_random<T> rand;
			rand.shuffle(arr, n);
			sort(arr, 0, n-1, comp);
			assert(is_sorted(arr, n, comp));
		}

	private:

		static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp)
		{
			if(high <= low){return;}

			insertion_sort<T> insert;
		    if(high <= low + CUTOFF_ - 1) 
		    {
		      insert.sort(arr, low, high, comp);
		      return;
		    }

			size_t lt = low, 
				   i  = low+1, 
				   gt = high;
		    T other = arr[low];

			while(i <= gt)
			{
				if(less(arr[i], other, comp))
				{
					exchange(arr, lt++, i++);
				} 
				else if(less(other, arr[i], comp)) 
				{
					exchange(arr, i, gt); 
					if (gt != 0) { --gt; } 
				} 
				else 
				{ 
					++i; 
				}
			} //end of while loop
			sort(arr, low, (lt == 0 ? 0 : lt - 1), comp); //sort(arr, low, lt-1, comp);
			sort(arr, gt+1, high, comp);
			assert(is_sorted(arr, low, high, comp));
		}
};