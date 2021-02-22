#pragma once
#include <vector>

typedef unsigned long long ULL;

void radix_sort(std::vector<ULL>&, size_t, size_t, unsigned);

void radix_sort256(std::vector<ULL>&, size_t, size_t);
void radix_sort65536(std::vector<ULL>&, size_t, size_t);