#include <span>
#include <iostream>
#include <vector>
#include <array>
#include <string>

void print_ints(std::span<const int> ints)
{
	for (const auto& n : ints)
	{
		std::cout << n << std::endl;
	}
}

void test_01()
{
	print_ints(std::vector {1, 2, 3});
	print_ints(std::array<int, 5>{1, 2, 3, 4, 5});

	int a[10] = {0};
	print_ints(a);
}


void print_three_ints(std::span<const int, 3> ints)
{
	for (const auto n : ints)
	{
		std::cout << n << std::endl;
	}
}

void test_02()
{
	// print_three_ints(std::vector {1, 2, 3});
	// print_three_ints(std::array<int, 5> {1, 2, 3, 4, 5});
	int a[10] = {0};
	// print_three_ints(a);

	std::array<int, 3> b = {1, 2, 3};
	print_three_ints(b);

	std::vector c{1, 2, 3};
	print_three_ints(std::span<const int, 3> {c.data(), 3});
	print_three_ints(std::span<const int, 3>{c.cbegin(), c.cend()});
}


int main()
{
	// test_01();
	test_02();
	return 0;
	std::cout << std::to_string(12);
}