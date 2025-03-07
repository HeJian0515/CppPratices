#include <algorithm>
#include <iostream>
#include <vector>

void useIterator_for_each()
{
	std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto it1 = data.begin();
	auto it2 = it1 + 2;
	std::for_each(it1, it2, [](int el)
	{
		std::cout << el << ", ";
	});
	// 1, 2,

	std::cout << std::endl;

	auto it3 = data.begin() + 5;
	auto it4 = data.end();
	std::for_each(it3, it4, [](int el)
	{
		std::cout << el << ", ";
	});
	// 6, 7, 8, 9,
}

/*void useRange_for_each()
{
	std::vector data = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	struct Sentinel
	{
		using iter_t = std::vector<int>::iterator;
		iter_t begin;
		std::iter_difference_t<iter_t> cnt;

		bool operator==(const iter_t& l) const
		{
			return std::distance(begin, l) >= cnt;
		}
	};

	auto it1 = data.begin();
	std::ranges::for_each(it1, Sentinel{it1, 5}, [](int el)
	{
		std::cout << el << ", ";
	});
	// 1, 2, 3, 4, 5,
}*/

void sort_iterator_range()
{
	std::vector<int> data{1, 4, 5, 7, 9, 2, 3};

	auto result = std::is_sorted_until(data.begin(), data.end());
	// 最长的有序范围
	for (auto it = data.begin(); it != result; ++it)
	{
		std::cout << *it << ", ";
	}
	// 1, 4, 5, 7, 9

	std::cout << '\n';

	for (auto v : std::ranges::subrange(data.begin(), result))
	{
		std::cout << v << ", ";
	}
	// 1, 4, 5, 7, 9
}

int main()
{
	useIterator_for_each();

	std::cout << std::endl;

	//useRange_for_each();

	sort_iterator_range();
}