#pragma once
#include <vector>


typedef unsigned long long ULL;

int partition_median3(std::vector<ULL>& nums, int start, int end);
int partition_middle(std::vector<ULL>& nums, int start, int end);

void quick_sort_median3(std::vector<ULL>& nums, int start, int end);

void quick_sort_middle(std::vector<ULL>& nums, int start, int end);
