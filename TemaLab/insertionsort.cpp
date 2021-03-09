#include "insertionsort.h"


void insertion_sort(std::vector<ULL>& nums, unsigned start, unsigned end)
{
	for (unsigned int i = start+1; i <= end; ++i)
	{
		ULL x = nums[i];
		unsigned j = i;
		while (j > 0 && nums[j-1] > x)
		{
			nums[j] = nums[j-1];
			j--;
		}
		nums[j] = x;
	}
}