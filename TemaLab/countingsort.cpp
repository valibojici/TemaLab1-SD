#include "countingsort.h"

typedef unsigned long long ULL;

bool check_memory(const std::vector<ULL>& nums)
{
	ULL mini = nums[0], maxi = nums[0];
	for (int i = 1; i < nums.size(); ++i)
		mini = std::min(mini, nums[i]), maxi = std::max(maxi, nums[i]);
	
	if (maxi - mini + 1 > 1000000000)
		return false;
	return true;
}


void counting_sort(std::vector<ULL>& nums,unsigned start, unsigned end)
{
	ULL mini = nums[start], maxi = nums[start];
	for (int i = start + 1; i <= end; ++i)
		mini = std::min(mini, nums[i]), maxi = std::max(maxi, nums[i]);

	// daca sunt prea multe numere depasesc memoria
	if (maxi - mini + 1 > 1000000000) {
		return;
	}

	std::vector<ULL> count(maxi - mini + 1, 0);
	for (unsigned i = start; i <= end; ++i)
		count[nums[i] - mini]++;

	unsigned poz = start;
	for (ULL i = 0; i < maxi - mini + 1; ++i)
		for (unsigned j = 0; j < count[i]; ++j)
			nums[poz++] = i + mini;
}