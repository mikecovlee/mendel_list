#pragma once
#include <stdexcept>
#include <ostream>
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
		bool empty() const
		{
			return data==nullptr;
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
		node_t* copy() const
		{
			if(data==nullptr)
				return nullptr;
			node_t* new_data=new node_t(data->data);
			for(node_t* it=data->next;it!=nullptr;new_data=new_data->next, it=it->next)
				new_data->next=new node_t(it->data);
			return new_data;
		}
		T& max()
		{
			if(data==nullptr)
				throw std::logic_error("Container is empty.");
			node_t* dat=data;
			for(node_t* it=data->next;it!=nullptr;it=it->next)
				if(it->data>dat->data)
					dat=it;
			return dat->data;
		}
		const T& max() const
		{
			return const_cast<linked_list*>(this)->max();
		}
		void reserve()
		{
			if(data!=nullptr)
			{
				node_t* new_data=new node_t(data->data);
				for(node_t* it=data->next;it!=nullptr;it=it->next)
					new_data=new node_t(it->data, new_data);
				clear();
				data=new_data;
			}
		}
		T& locate(size_t index)
		{
			node_t* dat=data;
			for(size_t i=0;dat!=nullptr;dat=dat->next,++i)
				if(i==index)
					return dat->data;
			throw std::out_of_range("Index out of range.");
		}
		const T& locate(size_t index) const
		{
			const_cast<linked_list*>(this)->locate(index);
		}
		void tidy_up()
		{
			node_t* target=nullptr;
			for(node_t* e=data;e!=nullptr;e=e->next)
			{
				for(node* it=e;it!=nullptr;it=it->next)
				{
					if(e->data==it->data)
					{
						target=e;
						break;
					}
				}
			}
			if(target!=nullptr)
			{
				for(node_t *previous=target, *it=target->next;it!=nullptr;)
				{
					if(target->data==it->data)
					{
						previous->next=it;
						delete it;
						it=previous->next;
					}else
					{
						previous=prvious->next;
						it=it->next;
					}
				}
				tidy_up();
			}
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
template<typename T>
std::ostream& operator<<(std::ostream& o,const mendel::linked_list<T>& list)
{
	using node_t=mendel::linked_list<T>::node_t;
	for(node_t* it=list.data;it!=nullptr;it=it->next)
		o<<it->data<<"\t";
	o<<std::flush;
	return o;
}