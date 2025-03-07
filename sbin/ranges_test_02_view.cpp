#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <format>
#include <unordered_map>
#include <string>

int test1()
{
	std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
	auto results = numbers | std::views::filter([](int n) { return n % 2 == 0;})
		| std::views::transform([](int n) { return n * 2;});

	// 4 8 12
	for (const auto v : results)
	{
		std::cout << v << " ";
	}

	// 左值
	std::ranges::drop_view firstFour{numbers, 4};

	return 0;
}

int test2()
{
	std::vector vec {1, 3, 5, 2, 3, 5, 6, 7, 8, 9, 67, 5, 23, 4, 2, 6456, 4};
	//std::sort(vec.begin(), vec.end());
	std::ranges::sort(vec);
	for (auto v : vec)
	{
		std::cout << v << std::endl;
	}
	return 0;
}


struct Student
{
	std::string name;
	int id;
};

void printStudent(const std::vector<Student>& students)
{
	for (const auto& student : students)
	{
		std::cout << std::format(" ({}, {}) ", student.name, student.id);
	}
	std::cout << "\n\n";
}

int test3()
{
	std::vector<Student> students{{"jack", 10086},
						          {"black", 10010},
					              {"trump", 12345},
                                  {"job", 143235}};
	std::ranges::sort(students, {}, &Student::name);
	printStudent(students);

	std::ranges::sort(students, std::ranges::greater(), &Student::name);
	printStudent(students);

	std::ranges::sort(students, std::ranges::greater(), &Student::id);
	printStudent(students);

	std::ranges::sort(students, std::ranges::greater{}, [](auto p)
	{
		return std::to_string(p.id) + p.name;
	});
	printStudent(students);

	return 0;
}


int main4()
{
	std::unordered_map<std::string, int> m{{"jack", 10086},
						                   {"black", 10010},
					                       {"trump", 12345},
                                           {"job", 143235}};

	auto names = std::views::keys(m);
	for (const auto& name : names)
	{
		std::cout << name << " ";
	}
	std::cout << "\n";

	auto values = std::views::values(m);
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}
	std::cout << "\n";
	
	return 0;
}

int main5()
{
	std::unordered_map<std::string, int> m{{"jack", 10086},
						                   {"black", 10010},
					                       {"trump", 12345},
                                           {"job", 143235}};

	auto firstb = [](const std::string& name)
	{
		return name[0] == 'b';
	};
	for (const auto& name : std::views::keys(m) |
		 std::views::reverse | std::views::take(4) |
		 std::views::filter(firstb))
	{
		std::cout << name << std::endl;
	}
	
	return 0;
}


bool isPrime(int i)
{
	for (int j = 2; j * j <= i; ++j)
	{
		if (i % j == 0) return false;
	}
	return true;
}

auto odd = [](int i) { return i % 2 == 1;};

int main()
{
	std::cout << std::boolalpha;

	std::vector<int> vec;
	std::vector<int> vec2;

	for (int i : std::views::iota(0, 10))
	{
		vec.push_back(i);
	}

	for (int i : std::views::iota(0) | std::views::take(10))
	{
		vec2.push_back(i);
	}
	std::cout << "vec == vec2: " << (vec == vec2) << '\n';

	for (int i : vec)
	{
		std::cout << i << " ";
	}

	std::cout << "求质数" << std::endl;

	for (int i : std::views::iota(1'000'000)
		| std::views::filter(odd) 
		| std::views::filter(isPrime) 
		| std::views::take(20))
	{

		std::cout << i << std::endl;
	}



	return 0;
}


