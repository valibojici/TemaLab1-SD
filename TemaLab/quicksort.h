#pragma once
#include <vector>


typedef unsigned long long ULL;

size_t partition_median3(std::vector<ULL>& nums, size_t start, size_t end);
size_t partition_middle(std::vector<ULL>& nums, size_t start, size_t end);

void quick_sort_median3(std::vector<ULL>& nums, size_t start, size_t end);

void quick_sort_middle(std::vector<ULL>& nums, size_t start, size_t end);
