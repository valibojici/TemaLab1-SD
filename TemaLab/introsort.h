#pragma once

#include <vector>
#include "quicksort.h"

typedef unsigned long long ULL;

void heap_sort(std::vector<ULL>&, unsigned, unsigned);
void heap_down(std::vector<ULL>&, unsigned,unsigned, unsigned);


void introsort_range(std::vector<ULL>&, unsigned, unsigned, int);
void introsort(std::vector<ULL>&, unsigned, unsigned);