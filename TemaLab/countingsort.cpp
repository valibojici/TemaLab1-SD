#include "countingsort.h"

typedef unsigned long long ULL;

bool counting_sort(std::vector<ULL>& nums)
{
	ULL mini = nums[0], maxi = nums[0];
	for (unsigned int i = 1; i < nums.size(); ++i)
		mini = std::min(mini, nums[i]), maxi = std::max(maxi, nums[i]);

	// daca sunt prea multe numere depasesc memoria
	if (maxi - mini + 1 > 1500000000)return false;

	std::vector<unsigned int> count(maxi - mini + 1, 0);
	for (unsigned int i = 0; i < nums.size(); ++i)
		count[nums[i] - mini]++;

	unsigned int poz = 0;
	for (unsigned int i = 0; i < maxi - mini + 1; ++i)
		for (unsigned int j = 0; j < count[i]; ++j)
			nums[poz++] = i + mini;

	return true;
}