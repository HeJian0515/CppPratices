#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>
using namespace std;


int main() {
	using  namespace std::literals;
	string s = "xx uu yy";
	
	for (auto pos = s.find(' '); pos != s.npos;) {
		s.replace(pos, 1, "%20");
	}
	cout << s;
	return 0;
}