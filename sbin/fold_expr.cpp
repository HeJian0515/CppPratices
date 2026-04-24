#include <iostream>
#include <algorithm>
#include <print>
#include <vector>

using namespace std;

void print() {
  cout << "Done!" << endl;
}

template<typename T, typename... Args>
void print(T value, Args... args) {
    cout << "Value: " << value << endl;
    print(args...); // 将剩余参数包解包并传入下一次调用
}

// 使用 sizeof... 运算符可以获取参数包中元素的数量。
template<typename... Args>
void countArgs(Args... args) {
    cout << "Number of arguments: " << sizeof...(args) << endl;
}

template<typename... Args>
auto sum_left(Args... args) {
    return (... + args); // 使用 fold expression 来计算参数包中所有元素的和。
}

template<typename... Args>
auto sum_right(Args... args) {
    return (args + ...); // 使用 fold expression 来计算参数包中所有元素的和。
}


template<typename... Args>
auto print_left(Args... args) {
    (cout << ... << args) << endl; // 使用 fold expression 来打印参数包中的所有元素。
}

/*
模式匹配： 展开操作 args... 会对包里的每个元素应用其左侧的模式。例如 func(std::forward<Args>(args)...) 会对每一个参数执行一次 forward。
*/

template<typename... Args>
auto left_minus(Args... args) {
    return (... - args); // 使用 fold expression 来计算参数包中所有元素的差。
}

template<typename... Args>
auto right_minus(Args... args) {
    return (args - ...); // 使用 fold expression 来计算参数包中所有元素的差。
}


template<typename... Args>
void printAll(Args... args) {
    // 使用逗号运算符，依次执行 std::cout << args
    ((cout << args << ","),  ... ) << endl;
}

template<typename Function, typename... Args>
void excute(Function func, Args... args) {
    // 对每个参数调用 func()
    (func(args), ...);
}

template<typename...Args>
bool allTrue(Args... args) {
    return (... && args);
}

template<typename...Args>
void pushToVector(vector<int>& vec, Args... args) {
    (vec.push_back(std::forward<Args>(args)), ...);
}


int main() {
    // print(1, 2.5, "Hello", 'A'); // 输出每个参数的值，最后输出 "Done!"

    // countArgs(1, 2.5, "Hello", 'A');

    // cout << "Sum (left fold): " << sum_left(1, 2.5, 3) << endl; // 输出 6.5
    // cout << "Sum (right fold): " << sum_right(1, 2.5, 3) << endl; // 输出 6.5

    /* cout << "Print (left fold): ";
    print_left(1, 2.5, "Hello", 'A'); */

    // cout << "Left minus: " << left_minus(1, 2, 3) << endl; // 输出 -4 (1 - 2 - 3)
    // cout << "Right minus: " << right_minus(1, 2, 3) << endl;  // 输出 2 (1 - (2 - 3))
    
    // printAll(1, 2.5, "Hello", 'A');

    return 0;
}