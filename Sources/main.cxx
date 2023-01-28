#include <set>
#include <iostream>

int main() {
	std::set<int> set;
	set.insert(2);
	set.insert(3);
	set.insert(4);
	std::cout << std::distance(set.begin(), set.end());
}
