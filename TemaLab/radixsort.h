#pragma once
#include <vector>

typedef unsigned long long ULL;

void radix_sort(std::vector<ULL>&, unsigned, unsigned, unsigned);
void radix_sort16(std::vector<ULL>&, unsigned, unsigned);
void radix_sort256(std::vector<ULL>&, unsigned, unsigned);
void radix_sort2048(std::vector<ULL>&, unsigned, unsigned);