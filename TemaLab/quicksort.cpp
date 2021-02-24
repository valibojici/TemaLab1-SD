#include "quicksort.h"
#include "insertionsort.h"
#include <iostream>
#include <random>

typedef unsigned long long ULL;


size_t partition_median3(std::vector<ULL>& nums, size_t start, size_t end)
{
	size_t mid = start + (end - start) / 2;
	if (nums[start] > nums[mid])
		std::swap(nums[start], nums[mid]);
	if (nums[start] > nums[end])
		std::swap(nums[start], nums[end]);
	if (nums[mid] > nums[end])
		std::swap(nums[mid], nums[end]);
	
	ULL pivot = nums[mid];
	
	while (1) {
		while (nums[start] < pivot)++start;
		while (nums[end] > pivot)--end;
		if (start >= end)
			return end;

		std::swap(nums[start], nums[end]);
		++start;
		--end;
	}
}

size_t partition_middle(std::vector<ULL>& nums, size_t start, size_t end)
{
	size_t mid = start + (end - start) / 2;
	 
	ULL pivot = nums[mid];
	size_t lo = start, hi = end;


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
		size_t p = partition_median3(nums, start, end);

		// apel recursiv la jumatatea mai mica si dupa tail call altfel stack overflow?
		if (p - start + 1 < end - p)
		{
			quick_sort_median3(nums, start, p);
			quick_sort_median3(nums, p + 1, end);
		}
		else
		{
			quick_sort_median3(nums, p + 1, end);
			quick_sort_median3(nums, start, p);
		}
	}
}

void quick_sort_middle(std::vector<ULL>& nums, size_t start, size_t end)
{
	if (start < end) {
		size_t p = partition_middle(nums, start, end);
		// apel recursiv la jumatatea mai mica si dupa tail call altfel stack overflow?
		if(p - start + 1 < end - p)
		{
			quick_sort_middle(nums, start, p);
			quick_sort_middle(nums, p + 1, end);
		}
		else
		{
			quick_sort_middle(nums, p + 1, end);
			quick_sort_middle(nums, start, p);
		}
	}
}
 