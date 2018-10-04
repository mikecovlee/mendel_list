#pragma once
#include <stdexcept>
#include <utility>
#include <array>
namespace mendel {
	using size_t=unsigned long;
	template <typename T> class node final {
	public:
		T data;
		node *next=nullptr;
		node()=default;
		node(node* next_node):next(next_node) {}
		template<typename element_t>node(element_t&& e, node *n = nullptr):data(std::forward<X>(e)), next(n) {}
	};
	template <typename T> class linked_list final {
	public:
		using node_t=node<T>;
		node_t *data=nullptr;
		linked_list()=default;
		linked_list(const linked_list& list):data(list.copy()){}
		linked_list(linked_list&& list) noexcept{
			std::swap(data,list.data);
		}
		template<size_t length>
		linked_list(const std::array<T,length>& arr)
		{
			data=new node_t(arr[0]);
			for(size_t i=1;i<length;++i)
				data->next=new node_t(arr[i]);
		}
		~linked_list()
		{
			clear();
		}
		void clear()
		{
			while (data != nullptr) {
				node_t* curr = data;
				data = data->next;
				delete curr;
			}
			data=nullptr;
		}
		node_t* copy()
		{
			if(data==nullptr)
				return nullptr;
			node_t* new_data=new node_t(data->data);
			for(node_t* it=data->next;it!=nullptr;new_data=new_data->next, it=it->next)
				new_data->next=new node_t(it->data);
			return new_data;
		}
		template <typename T>
		T max(link<T> *p,int lenth)
		{
			T temp = p->next->data;
			for (int i = 0; i < lenth; i++)
			{
				if (temp > (p->next->data))
					p = p->next;
				else
				{
					temp = p->next->data;
					p = p->next;
				}
				if (p == nullptr)
					continue;
			}
			return temp;
		}
		template <typename T>
		link<T>* reserve(link<T> *data)
		{
			link<T> *p;
			link<T> *q = nullptr;
			link<T> *temp;
			p = data->next;
			data->next = nullptr;
			while (p != nullptr) {
				temp = p->next;
				p->next = q;
				q = p;
				p = temp;
			}
			data->next = q;
			return data;
		}
		template <typename T>
		link<T>* local(link<T> *p, int i,int lenth)
		{
			if (i > lenth)
				return nullptr;
			link<T>* m = p;
			for (int j = 0; j < i; j++)
				m = m->next;
			return m;

		}
		template <typename T>
		link<T>* tidyup(link<T>*data)
		{
			if (data == nullptr)return nullptr;
			link<T>*p;
			link<T>*q;
			link<T>*m;
			p = data->next;
			while (p != nullptr) {
				q = p;
				while (q->next != nullptr) {
					if (q->next->data == p->data) {
						m = q->next;
						q->next = m->next;
						delete(m);
					}
					else q = q->next;
				}
				p = p->next;
			}
			return data;
		}
		template <typename T>
		link<T>* mergelists(link<T>* head1,link<T>* head2)
		{
			head1 = sort(head1);
			head2 = sort(head2);
			link<T>*p = head1->next;
			while (p->next != nullptr)
				p = p->next;
			p->next = head2->next;
			delete head2;
			head1=sort(head1);
			return head1;
		}
		template <typename T>
		link<T>* sort(link<T>* data)
		{
			link<T> *p;
			link<T> *q;
			T temp;
			for(p=data->next; p!=nullptr; p=p->next)
				for(q=p->next; q!=nullptr; q=q->next)
					if (p->data > q->data) {
						temp = p->data;
						p->data = q->data;
						q->data = temp;
					}
			return data;
		}
	};
}