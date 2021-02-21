#pragma once
#include <vector>


typedef unsigned long long ULL;

ULL median3(std::vector<ULL>& nums, size_t start, size_t end);

ULL random_piv(std::vector<ULL>& nums, size_t start, size_t end);

size_t partition(std::vector<ULL>& nums, size_t start, size_t end, bool option);

void quick_sort_median3(std::vector<ULL>& nums, size_t start, size_t end);

void quick_sort_random(std::vector<ULL>& nums, size_t start, size_t end);
