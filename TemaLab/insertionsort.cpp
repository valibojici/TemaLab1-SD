#include "insertionsort.h"

typedef unsigned long long ULL;
void insertion_sort(std::vector<ULL>& nums, size_t start, size_t end)
{
	for (unsigned int i = start+1; i <= end; ++i)
	{
		ULL x = nums[i];
		size_t j = i;
		while (j > 0 && nums[j-1] > x)
		{
			nums[j] = nums[j-1];
			j--;
		}
		nums[j] = x;
	}
}