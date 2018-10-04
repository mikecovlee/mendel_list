#include <iostream>
#include <array>
#include "linked_list.hpp"
int main()
{
	std::array<int, 6> a{{1, 2, 3, 4, 5, 6}};
	std::array<int, 8> b{{8, 7, 6, 5, 4, 3, 2, 1}};
	mendel::linked_list<int> p(a);
	std::cout << "List A:\n"
	          << p << std::endl;
	mendel::linked_list<int> q(b);
	std::cout << "List B:\n"
	          << q << std::endl;
	std::cout << "Max:" << p.max() << std::endl;
	std::cout << "Index=3:" << p.locate(3) << std::endl;
	p.merge(q);
	std::cout << "Merge A and B:\n"
	          << p << std::endl;
	p.sort();
	std::cout << "Sort A:\n"
	          << p << std::endl;
	p.sort([](const int &a, const int &b) {
		return a < b;
	});
	std::cout << "Reverse sort A:\n"
	          << p << std::endl;
	p.tidy_up();
	std::cout << "Tidy up A:\n"
	          << p << std::endl;
	p.reverse();
	std::cout << "Reverse A:\n"
	          << p << std::endl;
	return 0;
}