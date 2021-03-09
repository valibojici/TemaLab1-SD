#pragma once
#include <vector>


typedef unsigned long long ULL;

unsigned partition_median3(std::vector<ULL>& nums, unsigned start, unsigned end);
unsigned partition_middle(std::vector<ULL>& nums, unsigned start, unsigned end);

void quick_sort_median3(std::vector<ULL>& nums, unsigned start, unsigned end);

void quick_sort_middle(std::vector<ULL>& nums, unsigned start, unsigned end);
