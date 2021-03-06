#include "mergesort.h"

void mergesort(std::vector<ULL>& nums, std::vector<ULL>&aux, unsigned start, unsigned end, bool optimize = false)
{
	if (start < end)
	{
		if (optimize && end - start + 1 <= 24)
		{
			// insertion sort 
			for (unsigned i = start + 1; i <= end; ++i)
			{
				ULL x = nums[i];
				unsigned j = i;
				while (j > start && nums[j - 1] > x)
				{
					nums[j] = nums[j - 1];
					j--;
				}
				nums[j] = x;
			}
			return;
		}

		unsigned mid = start + (end - start) / 2;
		mergesort(nums, aux, start, mid, optimize);
		mergesort(nums, aux, mid + 1, end, optimize);

		unsigned i = start, j = mid + 1,k=0;
		while (i <= mid && j <= end)
		{
			if (nums[i] < nums[j])aux[k++] = nums[i++];
			else aux[k++] = nums[j++];
		}
		while (i <= mid)aux[k++] = nums[i++];
		while (j <= end)aux[k++] = nums[j++];

		for (unsigned i = start; i <= end; ++i)
			nums[i] = aux[i - start];
	}
}

void merge_sort(std::vector<ULL>& nums, unsigned start, unsigned end)
{
	std::vector<ULL> aux(end - start + 1, 0);
	mergesort(nums, aux, start, end, false);
}

void merge_sort_optimized(std::vector<ULL>& nums, unsigned start, unsigned end)
{
	std::vector<ULL> aux(end - start + 1, 0);
	mergesort(nums, aux, start, end, true);
}