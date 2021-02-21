#include "quicksort.h"
#include "insertionsort.h"
#include <iostream>
#include <random>

typedef unsigned long long ULL;

// generarea numere aleatorii https://stackoverflow.com/a/13445752
std::random_device dev;
std::mt19937_64 rng(dev());


ULL median3(std::vector<ULL>& nums, size_t start, size_t end)
{
	size_t mid = start + (end - start) / 2;

	if (nums[start] > nums[mid])
		std::swap(nums[start], nums[mid]);
	if (nums[start] > nums[end])
		std::swap(nums[start], nums[end]);
	if (nums[mid] > nums[end])
		std::swap(nums[mid], nums[end]);

	return nums[mid];
}

ULL random_piv(std::vector<ULL>& nums, size_t start, size_t end)
{
	std::uniform_int_distribution<ULL> distribution(start, end);
	return nums[distribution(rng)];
}

size_t partition(std::vector<ULL>& nums, size_t start, size_t end, bool option)
{
	const ULL pivot = option == 0 ? median3(nums, start, end) : random_piv(nums,start,end);

	while (1) {
		while (nums[start] < pivot)start++;
		while (nums[end] > pivot)end--;
		if (start >= end)
			return end;
		
		std::swap(nums[start], nums[end]);
		start++;
		end--;
	}
}


void quick_sort_median3(std::vector<ULL>&nums, size_t start, size_t end)
{ 
	if(start < end){
		size_t p = partition(nums, start, end, 0);

		quick_sort_median3(nums, start, p);
		quick_sort_median3(nums, p + 1, end);
	}
}

void quick_sort_random(std::vector<ULL>& nums, size_t start, size_t end)
{
	if (start < end) {
		size_t p = partition(nums, start, end, 1);

		quick_sort_random(nums, start, p);
		quick_sort_random(nums, p + 1, end);
	}
}
 