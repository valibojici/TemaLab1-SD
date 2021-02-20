#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <chrono>
#include <random>
#include <fstream>
#include <functional>

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
	std::uniform_int_distribution<ULL> distribution(0, max_val-1);


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

bool counting_sort(std::vector<ULL>& nums)
{
	ULL mini = nums[0], maxi = nums[0];
	for (unsigned int i = 1; i < nums.size(); ++i)
		mini = std::min(mini, nums[i]), maxi = std::max(maxi, nums[i]);

	// daca sunt prea multe numere depasesc memoria
	if (maxi - mini + 1 > 1500000000)return false;


	std::vector<unsigned int> count(maxi - mini + 1, 0);
	for (unsigned int i = 0; i < nums.size(); ++i)
		count[nums[i] - mini]++;

	unsigned int poz = 0;
	for (unsigned int i = 0; i < maxi - mini + 1; ++i)
		for (unsigned int j = 0; j < count[i]; ++j)
			nums[poz++] = i + mini;
	
	return true;
}


int main() {
	std::vector<std::pair<unsigned int, ULL> > tests = get_tests("teste.txt");

	// functii in vector https://stackoverflow.com/a/53725982
	std::vector<std::function<bool(std::vector<ULL>&) > > sorts;


	sorts.push_back(counting_sort);


	for (auto& test : tests)
	{
		std::cout << "N = " << test.first << " Max = " << test.second << '\n';
		std::vector<ULL> v = get_random_nums(test.first, test.second);

		for (auto& sort : sorts)
		{
			bool ok;

			// pentru masurat timp executie functie https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
			auto start = std::chrono::high_resolution_clock::now();
			ok = sort(v);
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			std::cout << duration.count() << "us    " << duration.count()/1000.0 << "ms"<< '\n';
		}
	}
}