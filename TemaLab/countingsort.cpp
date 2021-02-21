#include "countingsort.h"
#include <iostream>

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


void counting_sort(std::vector<ULL>& nums,size_t start, size_t end)
{
	ULL mini = nums[start], maxi = nums[start];
	for (int i = start + 1; i <= end; ++i)
		mini = std::min(mini, nums[i]), maxi = std::max(maxi, nums[i]);

	// daca sunt prea multe numere depasesc memoria
	if (maxi - mini + 1 > 1500000000) {
		return;
	}

	std::vector<int> count(maxi - mini + 1, 0);
	for (int i = start; i <= end; ++i)
		count[nums[i] - mini]++;

	int poz = start;
	for (int i = 0; i < maxi - mini + 1; ++i)
		for (int j = 0; j < count[i]; ++j)
			nums[poz++] = i + mini;
}