#include "mergesort.h";

void mergesort(std::vector<ULL>& nums, std::vector<ULL>&aux, size_t start, size_t end)
{
	if (start < end)
	{
		if (end - start + 1 <= 16)
		{
			// insertion sort
			for (size_t i = start + 1; i <= end; ++i)
			{
				ULL x = nums[i];
				size_t j = i;
				while (j > start && nums[j - 1] > x)
				{
					nums[j] = nums[j - 1];
					j--;
				}
				nums[j] = x;
			}
			return;
		}

		size_t mid = start + (end - start) / 2;
		mergesort(nums, aux, start, mid);
		mergesort(nums, aux, mid + 1, end);

		size_t i = start, j = mid + 1,k=0;
		while (i <= mid && j <= end)
		{
			if (nums[i] < nums[j])aux[k++] = nums[i++];
			else aux[k++] = nums[j++];
		}
		while (i <= mid)aux[k++] = nums[i++];
		while (j <= end)aux[k++] = nums[j++];

		for (size_t i = start; i <= end; ++i)
			nums[i] = aux[i - start];
	}
}

void merge_sort(std::vector<ULL>& nums, size_t start, size_t end)
{
	std::vector<ULL> aux(end - start + 1, 0);
	mergesort(nums, aux, start, end);
}