#include <iostream>
#include <format>
#include <compare>
using namespace std;

#pragma region 三向比较运算符测试1
struct foo {
    int a;
    bool b;
    char c;

    // 比较会按成员顺序进行，即先比较a，再比较b，最后比较c
    auto operator<=>(const foo&) const = default;
};

void test_foo() {
    foo f1{0, false, 'a'};
    foo f2{0, true, 'b'};

    cout << std::format("f1 < f2: {}\n", f1 < f2);
    cout << std::format("f1 == f2: {}\n", f1 == f2);
    cout << std::format("f1 >= f2: {}\n", f1 >= f2);
}
#pragma endregion


#pragma region 三向比较运算符测试2

// strong_ordering 适用于总是可以完全比较的类型
// weak_ordering 允许等价但不等值（如字符串不区分大小写）
// partial_ordering 允许不可比较情况（如浮点数的NaN）

#pragma endregion

int main() {
    test_foo();
    return 0;
}