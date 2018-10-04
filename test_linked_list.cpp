#include <iostream>
#include <array>
#include "linked_list.hpp"
int main()
{
	std::array<int, 6> a{{1, 2, 3, 4, 5, 6}};
	std::array<int, 8> b{{8, 7, 6, 5, 4, 3, 2, 1}};
	mendel::linked_list<int> p(a);
	mendel::linked_list<int> q(b);
	std::cout << p << std::endl;
	std::cout << q << std::endl;
	std::cout << p.max() << std::endl;
	std::cout << p.locate(3) << std::endl;
	p.merge(q);
	std::cout << p << std::endl;
	p.tidy_up();
	std::cout << p << std::endl;
	return 0;
}
