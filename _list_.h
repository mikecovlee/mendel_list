
#include <iostream>
#include "_ink_.h"
using namespace std;

template <typename T> class List :public link<T>
{
private:
	link<T> *head;
	link<T> *tail;
	link<T> *curr;
	void Removeall()
	{
		while (head != NULL)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}
public:
	~List() {
		Removeall();//destructor
	}
	void Clear()
	{
		Removeall();
	}
	
	
};

	template <typename T>
	link<T>* creat(T *a, int lenth)//传递数组首地址和数组长度
	{
		int cnt1 = 0;
		if (lenth == 0) return NULL;
		link<T> *p;
		link<T> *head = new link<T>;
		p = head;
		for (int i = 0; i < lenth; i++)//
		{
			p=p->next = new link<T>(a[i], NULL);
			cnt1++;
		}
		return head;
	}
	template <typename T>
	/*定义一个寻求最大值的函数，遍历链表所有元素，返回最大值
	参数p传递链表的head指针；参数lenth传递数组长度*/
	T max(link<T> *p,int lenth) 
	{
		T temp = p->next->element;
		for (int i = 0; i < lenth; i++) \
		{
			if (temp > (p->next->element))
				p = p->next;
			else 
			{
				temp = p->next->element;
				p = p->next;
			}
			if (p == NULL)
				continue;
		}
		return temp;
	}


	template <typename T>
	link<T>* reserve(link<T> *head)//参数head传递链表head结点的指针 
	{
		link<T> *p;
		link<T> *q = NULL;
		link<T> *temp;
		p = head->next;
		head->next = NULL;
		while (p != NULL)
		{
			temp = p->next;
			p->next = q;
			q = p;
			p = temp;
		}
		head->next = q;
		return head;
	}  
    template <typename T>
	//定义一个函数用于输出链表
	//head指针用于传递链表的head结点地址
	void Print(link<T> *head) {
		cout << "链表的元素是：";
		for (link<T> *p = head->next; p != NULL; p = p->next) {
			cout << p->element << '\t';
		}
		cout << endl;

	}

	template <typename T>
	/*指针p为头结点head接口，参数i为第几个结点，参数lenth为链表长度*/
	link<T>* local(link<T> *p, int i,int lenth)
	{
		if (i > lenth)
			return NULL;
		link<T>* m = p;
		for (int j = 0; j < i; j++)
			m = m->next;
		return m;

	}

	template <typename T>
	link<T>* tidyup(link<T>*head)
	{
		if (head == NULL)return NULL;
		//link<T>*meory;
		link<T>*p;
		link<T>*q;
		link<T>*m;
		p = head->next;
		while (p != NULL)
		{
			q = p;
			while (q->next != NULL)
			{
				if (q->next->element == p->element)
				{
					m = q->next;
					q->next = m->next;
					delete(m);
				}
				else q = q->next;
			}
			p = p->next;
		}
		return head;

	}

	template <typename T>
	link<T>* mergelists(link<T>* head1,link<T>* head2)
		// head指针是两链表head结点的接口
	{
		head1 = sort(head1);
		head2 = sort(head2);
		cout << "被排序后的第一个链表结果为：";
		Print(head1);
		cout << "被排序后的第二个链表结果为：";
		Print(head2);
		//link<T>*temp = head1;
		link<T>*p = head1->next;
		while (p->next != NULL)
			p = p->next;
		p->next = head2->next;
		delete head2;
		head1=sort(head1);
		return head1;
	}

	template <typename T>
	link<T>* sort(link<T>* head)
		//传入链表的head结点
	{
		link<T> *p;
		link<T> *q;
		T temp;
		for(p=head->next;p!=NULL;p=p->next)//冒泡排序
			for(q=p->next;q!=NULL;q=q->next)
				if (p->element > q->element)
				{
					temp = p->element;
					p->element = q->element;
					q->element = temp;
				}
		return head;
	}



	/*link<T>* reverse()
	{
	T *m = new T[cnt];
	curr = head;
	m[0] = curr->element;
	for (int i = 1; i < cnt; i++) {
	m[i] = curr->next->element;
	curr = curr->next;
	}
	for (int i = 0; i < cnt; i++)
	cout << m[i] << '\t';
	cout << endl;
	T temp = 0;
	for (int i = 0; i < cnt / 2; i++) {
	temp = m[i];
	m[i] = m[cnt - 1 - i];
	m[cnt - 1 - i] = temp;
	}
	for (int i = 0; i < cnt; i++)
	cout << m[i] << '\t';
	cout << endl;
	return m;
	}*/