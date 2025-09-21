#include <iostream>
#include <cppcoro/generator.hpp>

using namespace cppcoro;

generator<int> range(int start, int end) {
    while (start < end) {
        co_yield start;
        start++;
    }
}

void test_range() {
    for (const auto& n : range(0, 10)) {
        std::cout << n << std::endl;
    }
}

int main() {
    test_range();
    return 0;
}