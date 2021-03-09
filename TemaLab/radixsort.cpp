#include "radixsort.h"


void radix_sort(std::vector<ULL>& nums, unsigned start, unsigned end, unsigned exponent)
{
	const unsigned base = (1 << exponent);

	std::vector<std::vector<ULL> >buckets;
	buckets.resize(base);

	ULL maxi = nums[start];
	for (unsigned i = start + 1; i <= end; ++i)
		maxi = std::max(maxi, nums[i]);

	for (int k = 0; maxi; k+=exponent)
	{
		for (std::vector<ULL>& bucket : buckets)
			bucket.clear();

		for (unsigned i = start; i <= end; ++i)
			buckets[(nums[i] >> k) & (base - 1)].push_back(nums[i]);

		unsigned idx = start;
		for (unsigned i = 0; i < base; ++i)
			for (unsigned j = 0; j < buckets[i].size(); ++j)
			{
				nums[idx] = buckets[i][j];
				idx++;
			}
		maxi >>= exponent;
	}
}

void radix_sort16(std::vector<ULL>& nums, unsigned start, unsigned end)
{
	radix_sort(nums, start, end, 4);
}

void radix_sort256(std::vector<ULL>& nums, unsigned start, unsigned end)
{
	radix_sort(nums, start, end, 8);
}

void radix_sort2048(std::vector<ULL>& nums, unsigned start, unsigned end)
{
	radix_sort(nums, start, end, 11);
}