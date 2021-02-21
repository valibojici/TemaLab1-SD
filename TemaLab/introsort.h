#pragma once

#include <vector>
#include "quicksort.h"

typedef unsigned long long ULL;

void heap_sort(std::vector<ULL>&, size_t, size_t);
void heap_down(std::vector<ULL>&, size_t,size_t, size_t);


void introsort_range(std::vector<ULL>&, size_t, size_t, int);
void introsort(std::vector<ULL>&, size_t, size_t);