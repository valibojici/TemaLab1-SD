#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <chrono>
#include <random>
#include <fstream>
#include <set>
#include <functional>
#include <iomanip>

#include "countingsort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "radixsort.h"
#include "introsort.h"
#include "mergesort.h"

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

std::vector<ULL> get_random_nums(size_t size, ULL max_val,std::string option)
{
	// generarea numere aleatorii https://stackoverflow.com/a/13445752
	std::random_device dev;
	std::mt19937_64 rng(dev());
	std::uniform_int_distribution<ULL> distribution(0, max_val - 1);

	std::vector<ULL> nums;
	nums.reserve(size);
	if (option == "Few distinct values")
	{
		for (size_t i = 0; i < size/8; ++i)
			nums.push_back(distribution(rng));

		std::uniform_int_distribution<ULL> dist(0, 9);
		for(size_t i = size / 8;i<size;++i)
			nums.push_back(dist(rng));
	}
	else{
		for (size_t i = 0; i < size; ++i)
			nums.push_back(distribution(rng));
	}
	
	if (option == "Sorted")
		std::sort(nums.begin(), nums.end());
	
	else if(option == "Sorted (reverse)")
		std::sort(nums.begin(), nums.end(),std::greater<int>());

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
	for (size_t i=0;i<nums.size();++i)
		std::cout << nums[i] << ' ';
	std::cout << '\n';
}


// functie pentru std::sort ca sa aiba aceeasi sintaxa ca ceilalti algoritmi
void std_sort(std::vector<ULL>& nums, size_t start, size_t end)
{
	std::sort(nums.begin() + start, nums.begin() + end + 1);
}


int main() {
	std::ofstream output("output.txt");

	std::vector<std::pair<unsigned int, ULL> > tests = get_tests("teste.txt");
	 
	// functii in vector https://en.cppreference.com/w/cpp/utility/functional/function
	std::vector<std::function<void(std::vector<ULL>&, size_t, size_t) > > sorts = {
		counting_sort,
		insertion_sort,
		quick_sort_median3,
		quick_sort_middle,
		merge_sort,
		merge_sort_optimized,
		radix_sort16,
		radix_sort256,
		radix_sort2048,
		introsort,
		std_sort
	};

	std::vector<std::string>sort_name{
		"Counting Sort",
		"Insertion Sort",
		"Quick Sort (median 3)",
		"Quick Sort (middle)",
		"Merge Sort",
		"Merge Sort(optimized)",
		"Radix_16",
		"Radix_256",
		"Radix_2048",
		"Introsort",
		"std::sort"
	};
	
	std::vector<std::string> subcases{
		"Mixed",
		"Sorted",
		"Sorted (reverse)",
		"Duplicate values",
	};


	for (auto& test : tests)
	{
		std::cout << "\nN = " << test.first << " Max = " << test.second << "\n\n";
		output << "\nN = " << test.first << " Max = " << test.second << "\n\n";

		// nume coloane
		std::cout << "                       ";
		output << "                       ";
		for(auto &subcase : subcases)
		{
			std::cout << std::left << std::setw(16) << subcase << "|";
			output << std::left << std::setw(16) << subcase << "|";
		}
		output << '\n';
		std::cout << '\n';

		for (size_t i = 0; i < sorts.size(); ++i)
		{
			// nume sortare
			std::cout << sort_name[i] << std::right << std::setw(23 - sort_name[i].length()) << ": ";
			output << sort_name[i] << std::right << std::setw(23 - sort_name[i].length()) << ": ";

			for (auto& subcase : subcases)
			{
				std::vector<ULL> nums = get_random_nums(test.first, test.second, subcase);

				if (sort_name[i] == "Counting Sort" && !check_memory(nums)) // counting sort
				{
					std::cout << std::left << std::setw(16) << "Memorie insuf." << "|";
					output << std::left << std::setw(16) << "Memorie insuf." << "|";
					continue;
				}
				if (sort_name[i] == "Insertion Sort" && test.first >= 150000) // insertion sort
				{
					std::cout << std::left << std::setw(16) << "Foarte incet" << "|";
					output << std::left << std::setw(16) << "Foarte incet" << "|";
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
					sorts[i](v, 0, v.size() - 1);
					auto end = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

					avg += duration.count() / 1000.0;
				}
				std::cout << (check_sort(v) ? "OK " : "NOT OK ") << std::left <<  std::setw(11) << round(avg / 10 * 100) / 100 << "ms|";
				output << (check_sort(v) ? "OK " : "NOT OK ") << std::left <<  std::setw(11) << round(avg / 10 * 100) / 100 << "ms|";
			}
			std::cout << '\n';
			output << '\n';
		}
	}

	return 0;



	for (auto& test : tests)
	{
		std::cout << "N = " << test.first << " Max = " << test.second << '\n';
		output << "N = " << test.first << " Max = " << test.second << '\n';

		
		for (std::string subcase : subcases)
		{
			std::cout << "\n" << subcase << "\n-------------\n";
			output << "\n" << subcase << "\n-------------\n";
			
			std::vector<ULL> nums = get_random_nums(test.first, test.second, subcase);

			for (size_t i = 0; i < sorts.size(); ++i)
			{
				std::cout << sort_name[i] << std::setw(25 - sort_name[i].length()) << ": ";
				output << sort_name[i] << std::setw(25 - sort_name[i].length()) << ": ";

				if (i == 0 && !check_memory(nums)) // counting sort
				{
					std::cout << "Mem. Insf.\n";
					output << "Mem. Insf.\n";
					continue;
				}
				if (i == 1 && test.first >=100000) // insertion sort
				{
					std::cout << "Foarte incet\n";
					output << "Foarte incet\n";
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
					sorts[i](v, 0, v.size() - 1);
					auto end = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

					avg += duration.count() / 1000.0;
				}
				std::cout << (check_sort(v) ? "OK " : "NOT OK ") << avg / 10 << "ms" << '\n';
				output << (check_sort(v) ? "OK " : "NOT OK ") << avg / 10 << "ms" << '\n';
			}
		}
		std::cout << "\n###########################################################################\n";
		output << "\n###########################################################################\n";
	}
}