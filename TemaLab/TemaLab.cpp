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
#include <map>

#include "countingsort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "radixsort.h"
#include "introsort.h"
#include "mergesort.h"

typedef unsigned long long ULL;


struct Result {
	size_t size;
	ULL max_val;
	std::map < std::string, std::vector< std::pair<std::string, float> > >  subcase_info; // sort_name : vector<subcase_name, time>
	Result(size_t size, ULL max_val) : size(size), max_val(max_val) {}
};


std::vector<std::pair<size_t, ULL> > get_tests(const char* file_name); 

std::vector<ULL> get_random_nums(size_t size, ULL max_val, std::string option);	

void std_sort(std::vector<ULL>& nums, size_t start, size_t end); // functie pentru std::sort ca sa aiba aceeasi sintaxa ca ceilalti algoritmi

bool check_sort(const std::vector<ULL>& nums);

void print_result(Result& result, std::ostream& out);

int main() {
	std::ofstream output("output.txt");

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

	std::vector<std::string>sort_names{
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

	std::vector<std::string> subcases{ "Mixed", "Sorted", "Sorted (reverse)", "Duplicate values","Seesaw" };
	
	for (auto& test : get_tests("teste.txt"))
	{
		Result result(test.first, test.second);

		for (auto& subcase : subcases)
		{
			std::vector<ULL> initial_nums = get_random_nums(test.first, test.second, subcase);
			for (size_t i = 0; i < sorts.size(); ++i)
			{		
				std::cout << "Se calculeaza timpul pentru " << sort_names[i] << " cazul " << subcase << " " << test.first << " " << test.second << '\n';

				// daca dureaza prea mult sau nu este memorie suficienta(Counting sort)
				if (test.first > 200000)
				{
					if (sort_names[i] == "Insertion Sort" && subcase != "Sorted")
					{
						result.subcase_info[sort_names[i]].push_back({ subcase,-1 });
						continue;
					}
					if ((sort_names[i] == "Quick Sort (median 3)" || sort_names[i] == "Quick Sort (middle)") && subcase == "Seesaw")
					{
						result.subcase_info[sort_names[i]].push_back({ subcase,-1 });
						continue;
					}
				}
				else if (sort_names[i] == "Counting Sort" && !check_memory(initial_nums))
				{
					result.subcase_info[sort_names[i]].push_back({ subcase,-2 });
					continue;
				}

				std::vector<ULL> v;
				float avg = 0;

				// 10 iteratii pt fiecare sort si medie aritmetica
				for (int k = 0; k < 10; ++k)
				{
					v = initial_nums;

					// pentru masurat timp executie functie https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
					auto start = std::chrono::high_resolution_clock::now();
					sorts[i](v, 0, v.size() - 1);
					auto end = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

					avg += duration.count() / 1000.0;
				}
				avg /= 10;
				avg = round(avg * 100) / 100;
				if (check_sort(v))
					result.subcase_info[sort_names[i]].push_back({ subcase,avg });
				else
					result.subcase_info[sort_names[i]].push_back({ subcase,-3 });
			}
		}
		print_result(result, std::cout);
		print_result(result, output);
	}
	return 0;
}

std::vector<std::pair<size_t, ULL> > get_tests(const char* file_name)
{
	std::string input;
	std::ifstream fin(file_name);
	std::vector< std::pair<size_t, ULL> >tests;

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

std::vector<ULL> get_random_nums(size_t size, ULL max_val, std::string option)
{
	// generarea numere aleatorii https://stackoverflow.com/a/13445752
	std::random_device dev;
	std::mt19937_64 rng(dev());
	std::uniform_int_distribution<ULL> distribution(0, max_val - 1);

	std::vector<ULL> nums;
	nums.reserve(size);
	if (option == "Duplicate values")
	{
		for (size_t i = 0; i < 8; ++i)
			nums.push_back(distribution(rng));

		std::uniform_int_distribution<ULL> dist(0, 7);
		for (size_t i = 8; i < size; ++i)
			nums.push_back(nums[dist(rng)]);
	}
	else if (option == "Seesaw")
	{
		std::set<ULL> aux;
		while (aux.size() < size)aux.insert(distribution(rng));
		for (const ULL& x : aux)nums.push_back(x);

		for (size_t i = 1; i < size; ++i)
			std::swap(nums[i], nums[i / 2]);
	}
	else {
		for (size_t i = 0; i < size; ++i)
			nums.push_back(distribution(rng));
	}

	if (option == "Sorted")
		std::sort(nums.begin(), nums.end());

	else if (option == "Sorted (reverse)")
		std::sort(nums.begin(), nums.end(), std::greater<int>());

	return nums;
}

void std_sort(std::vector<ULL>& nums, size_t start, size_t end)
{
	std::sort(nums.begin() + start, nums.begin() + end + 1);
}

bool check_sort(const std::vector<ULL>& nums)
{
	for (size_t i = 1; i < nums.size(); ++i)
		if (nums[i - 1] > nums[i])return false;
	return true;
}

void print_result(Result& result, std::ostream& out)
{
	out << "\nN = " << result.size << " Max = " << result.max_val << '\n';
	out << "                       "; // spatiu inainte de nume prima coloana

	for (auto& subcase_info : result.subcase_info.begin()->second) // fiecare nume de coloana
		out << std::left << std::setw(16) << subcase_info.first << "|";
	out << "\n";

	for (auto& subcase_info : result.subcase_info)
	{
		// afis nume sort
		out << subcase_info.first << std::right << std::setw(23 - subcase_info.first.length()) << ": ";

		for (auto& info : subcase_info.second) // pereche (subcase - time)
		{
			if (info.second >= 0) // daca a fost ok sortarea
				out << "OK " << std::left << std::setw(11) << info.second << "ms|";
			else
			{
				std::string mesaj = "NOT OK"; // nu este sortat corect

				if (info.second == -1) // depasit timp la insertion sort
					mesaj = "Foarte incet";
				else if (info.second == -2) // depasit memorie la counting sort
					mesaj = "Memorie insuf.";

				out << std::left << std::setw(16) << mesaj << "|";
			}
		}
		out << '\n'; // gata linia curenta
	}
	out << "\n"; // gata tabelul
}