#include<iostream>
#include<stdlib.h>
#include"_list_.h"
#include"_ink_.h"
using namespace std;
int main()
{
	int a[6] = { 1,2,3,4,5,6 };
	int b[6] = { 6,5,4,3,2,1 };
	link<int> *p = creat(a,6);
	link<int> *q = creat(b, 6);

	cout << "链表中元素的最大值是" << max(p, 6) << endl;
	cout << "结点的地址是"<<local(p, 3, 6) << endl; 
	Print(mergelists(p, q));
	p = tidyup(p);
	Print(p);
	system("pause");
	return 0;
}
