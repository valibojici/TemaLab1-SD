#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <chrono>
#include <random>
#include <fstream>
#include <functional>

#include "countingsort.h"
#include "insertionsort.h"
#include "quicksort.h"

typedef unsigned long long ULL;

std::vector<std::pair<unsigned int, ULL> > get_tests(const char* file)
{
	std::string input;
	std::ifstream fin(file);
	std::vector< std::pair<unsigned int, ULL> >tests;

	fin >> input;
	fin >> input;
	fin >> input;
	size_t nr_tests = std::stoull(input);
	fin.get();

	for (size_t i = 0; i < nr_tests; ++i)
	{
		fin >> input;
		fin >> input;
		fin >> input;
		size_t size = std::stoull(input);
		fin.get();

		fin >> input;
		fin >> input;
		fin >> input;
		ULL max_val = std::stoull(input);
		fin.get();

		tests.push_back({ size,max_val });
	}
	fin.close();
	return tests;
}

std::vector<ULL> get_random_nums(size_t size, ULL max_val)
{
	// generarea numere aleatorii https://stackoverflow.com/a/13445752
	std::random_device dev;
	std::mt19937_64 rng(dev());
	std::uniform_int_distribution<ULL> distribution(0, max_val - 1);

	std::vector<ULL> nums;
	nums.reserve(size);

	for (size_t i = 0; i < size; ++i)
		nums.push_back(distribution(rng));

	return nums;
}

bool check_sort(const std::vector<ULL>& nums)
{
	for (size_t i = 1; i < nums.size(); ++i)
		if (nums[i - 1] > nums[i])return false;
	return true;
}

void afis(const std::vector<ULL>& nums)
{
	for (const int& x : nums)
		std::cout << x << ' ';
	std::cout << '\n';
}

// functie pentru std::sort ca sa aiba aceeasi sintaxa ca ceilalti algoritmi
void std_sort(std::vector<ULL>& nums, size_t start, size_t end)
{
	std::sort(nums.begin() + start, nums.begin() + end + 1);
}


int main() {

	//std::vector<ULL> v = get_random_nums(100000000, 100000);
	//quick_sort_first(v, 0, v.size() - 1);

	//for (int i = 0; i < 10000; ++i)
	//{
	//	std::vector<ULL> v = get_random_nums(10000000, 50);
	//	std::sort(v.begin(), v.end());
	//	//afis(v);
	//	
	//	quick_sort_first(v,0,v.size()-1);
	//	if (check_sort(v))std::cout << "OK\n";
	//	else std::cout << "NU E eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeOK\n";
	//}

#if 1
	std::vector<std::pair<unsigned int, ULL> > tests = get_tests("teste.txt");

	// functii in vector https://en.cppreference.com/w/cpp/utility/functional/function
	std::vector<std::function<void(std::vector<ULL>&,size_t,size_t) > > sorts = {
		counting_sort,
		insertion_sort,
		quick_sort_median3,
		quick_sort_middle,
		std_sort
	};

	std::vector<std::string>sort_name{
		"Counting Sort",
		"Insertion Sort",
		"quick_sort_median3",
		"quick_sort_middle",
		"std::sort"
	};


	for (auto& test : tests)
	{
		std::cout << "N = " << test.first << " Max = " << test.second << '\n';
		std::vector<ULL> nums = get_random_nums(test.first, test.second);

		for (size_t i = 0; i < sorts.size(); ++i)
		{
			std::cout << sort_name[i] << " : ";
			if (i == 0 && !check_memory(nums))
			{
				std::cout << "Memorie insuficienta\n";
				continue;
			}
			if (i == 1)
			{
				std::cout << "Numar prea mare de elemente(dureaza prea mult)\n";
				continue;
			}

			std::vector<ULL> v;
			double avg = 0;
			
			// 10 iteratii pt fiecare sort si medie aritmetica
			for (int k = 0; k < 10; ++k)
			{
				v = nums;

				// pentru masurat timp executie functie https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
				auto start = std::chrono::high_resolution_clock::now();
				sorts[i](v,0,v.size()-1);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

				avg += duration.count() / 1000.0;
			}
			std::cout << (check_sort(v) ? "OK " : "NOT OK ") << avg / 10 << "ms" << '\n';
		}
		std::cout << "\n\n";
	}
#endif
}