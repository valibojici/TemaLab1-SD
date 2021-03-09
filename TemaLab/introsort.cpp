#include "introsort.h"

void heap_sort(std::vector<ULL>& nums, unsigned start, unsigned end)
{
	unsigned size = end - start + 1;
	for (unsigned i = size / 2; i > 0; --i)
		heap_down(nums, i - 1, start, end);

	for (unsigned i = end; i > start; --i)
	{
		std::swap(nums[start], nums[i]);
		heap_down(nums, 0 ,start, i - 1);
	}
}

void heap_down(std::vector<ULL>& nums, unsigned index, unsigned start, unsigned end)
{
	if (start + index * 2 + 1 > end)return;
	
	unsigned child_idx = index * 2 + 2;
	if (start + child_idx > end || nums[start + index * 2 + 1] > nums[start + child_idx])
		child_idx = index * 2 + 1;

	if (nums[start + index] < nums[start + child_idx])
	{
		std::swap(nums[start + index], nums[start + child_idx]);
		heap_down(nums, child_idx, start, end);
	}
}


void introsort_range(std::vector<ULL>& nums, unsigned start, unsigned end, int depth)
{
	if (start < end)
	{
		if (end - start + 1 <= 24)
		{
			for (unsigned i = start + 1; i <= end; ++i)
			{
				ULL x = nums[i];
				unsigned j = i;
				while (j > 0 && nums[j - 1] > x)
				{
					nums[j] = nums[j - 1];
					j--;
				}
				nums[j] = x;
			}
			return;
		}

		if (depth == 0)
		{
			heap_sort(nums, start, end);
			return;
		}

		unsigned p = partition_median3(nums, start, end);
	
		if(p - start +  1 < end - p)
		{
			introsort_range(nums, start, p, depth - 1);
			introsort_range(nums, p + 1, end, depth - 1);
		}
		else
		{
			introsort_range(nums, p + 1, end, depth - 1);
			introsort_range(nums, start, p, depth - 1);
		}
	}
}
void introsort(std::vector<ULL>& nums, unsigned start, unsigned end)
{
	introsort_range(nums, start, end,2*int(log2(nums.size())));
}