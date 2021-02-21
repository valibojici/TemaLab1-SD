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
	unsigned int nr_tests = std::stoul(input);
	fin.get();

	for (unsigned int i = 0; i < nr_tests; ++i)
	{
		fin >> input;
		fin >> input;
		fin >> input;
		unsigned int size = std::stoul(input);
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

std::vector<ULL> get_random_nums(unsigned int size, ULL max_val)
{
	// generarea numere aleatorii https://stackoverflow.com/a/13445752
	std::random_device dev;
	std::mt19937_64 rng(dev());
	std::uniform_int_distribution<ULL> distribution(0, max_val - 1);

	std::vector<ULL> nums;
	nums.reserve(size);

	for (unsigned int i = 0; i < size; ++i)
		nums.push_back(distribution(rng));

	return nums;
}


bool check_sort(const std::vector<ULL>& nums)
{
	for (unsigned int i = 1; i < nums.size(); ++i)
		if (nums[i - 1] > nums[i])return false;
	return true;
}

void afis(const std::vector<ULL>& nums)
{
	for (const int& x : nums)
		std::cout << x << ' ';
	std::cout << '\n';
}


int main() {

	/*std::vector<ULL> nums = { 1,7,6,3,1,1,6,2,1,7,6,3,1,1,6,2 };
	std::cout << BFPRT(nums) << '\n';
	std::sort(nums.begin(),nums.end());
	afis(nums);*/

#if 1



	std::vector<std::pair<unsigned int, ULL> > tests = get_tests("teste.txt");

	// functii in vector https://en.cppreference.com/w/cpp/utility/functional/function
	std::vector<std::function<void(std::vector<ULL>&,size_t,size_t) > > sorts = {
		counting_sort,
		insertion_sort,
		quick_sort_median3,
		quick_sort_random
	};

	std::vector<std::string>sort_name{
		"Counting Sort",
		"Insertion Sort",
		"quick_sort_median3",
		"quick_sort_random"
	};

	for (auto& test : tests)
	{
		std::cout << "N = " << test.first << " Max = " << test.second << '\n';
		std::vector<ULL> nums = get_random_nums(test.first, test.second);

		for (unsigned int i = 0; i < sorts.size(); ++i)
		{
			if (i == 1 && test.first >= 100000)continue;
			std::vector<ULL> v;

			// 10 iteratii pt fiecare sort si medie aritmetica
			double avg = 0;
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
			avg = avg / 10;
			
			std::cout << sort_name[i] << " : ";

			if (check_sort(v))
				std::cout << "OK " << avg << "ms" << '\n';
			else
			{
				if (i == 0 && !check_memory(v))
				{
					std::cout << "Memorie insuficienta\n";
					continue;
				}
				std::cout << "NOT OK\n";
			}
		}

		double avg = 0;
		std::vector<ULL> v;
		for (int k = 0; k < 10; ++k)
		{
			v = nums;

			// pentru masurat timp executie functie https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
			auto start = std::chrono::high_resolution_clock::now();
			std::sort(v.begin(), v.end());
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

			avg += duration.count() / 1000.0;
		}
		avg = avg / 10;
		std::cout << "std::sort() : " << avg << "ms\n";

		std::cout << "\n\n";
	}
#endif
}