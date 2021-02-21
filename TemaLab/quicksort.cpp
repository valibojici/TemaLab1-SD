#include "quicksort.h"
#include "insertionsort.h"
#include <iostream>
#include <random>

typedef unsigned long long ULL;


inline int partition_median3(std::vector<ULL>& nums, int start, int end)
{
	int mid = start + (end - start) / 2;

	if (nums[start] > nums[mid])
		std::swap(nums[start], nums[mid]);
	if (nums[start] > nums[end])
		std::swap(nums[start], nums[end]);
	if (nums[mid] > nums[end])
		std::swap(nums[mid], nums[end]);

	ULL pivot = nums[mid];
	 
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

inline int partition_middle(std::vector<ULL>& nums, int start, int end)
{
	int mid = start + (end - start) / 2;

	ULL pivot = nums[mid];

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

void quick_sort_median3(std::vector<ULL>&nums, int start, int end)
{ 
	if(start < end){
		int p = partition_median3(nums, start, end);

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

void quick_sort_middle(std::vector<ULL>& nums, int start, int end)
{
	if (start < end) {
		int p = partition_middle(nums, start, end);

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
 