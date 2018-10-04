#include<iostream>
using namespace std;
template <typename T> class link
{
public:
	T element;
	link<T> *next;
	link(const T &e, link *n = NULL)
	{
		element = e;
		next = n;
	}
	link(link* nextval = NULL)
	{
		next = nextval;
	}
};