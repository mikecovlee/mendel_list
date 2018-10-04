#pragma once
#include <stdexcept>
#include <ostream>
#include <utility>
#include <array>
namespace mendel {
	using size_t = unsigned long;
	template <typename T>
	class node final {
	public:
		T data;
		node *next = nullptr;
		node() = default;
		node(node *next_node) : next(next_node) {}
		template <typename element_t>
		node(element_t &&e, node *n = nullptr) : data(std::forward<element_t>(e)), next(n) {}
	};
	template <typename T>
	class linked_list final {
	public:
		using node_t = node<T>;
		node_t *data = nullptr;
		linked_list() = default;
		linked_list(const linked_list &list) : data(list.copy()) {}
		linked_list(linked_list &&list) noexcept
		{
			std::swap(data, list.data);
		}
		template <std::size_t length>
		linked_list(const std::array<T, length> &arr)
		{
			node_t *new_data = new node_t(arr[0]);
			data = new_data;
			for (size_t i = 1; i < length; new_data = new_data->next, ++i)
				new_data->next = new node_t(arr[i]);
		}
		~linked_list()
		{
			clear();
		}
		bool empty() const
		{
			return data == nullptr;
		}
		void clear()
		{
			while (data != nullptr) {
				node_t *curr = data;
				data = data->next;
				delete curr;
			}
			data = nullptr;
		}
		node_t *copy() const
		{
			if (data == nullptr)
				return nullptr;
			node_t *new_data = new node_t(data->data);
			for (node_t *e = data->next, *it = new_data; e != nullptr; e = e->next, it = it->next)
				it->next = new node_t(e->data);
			return new_data;
		}
		T &max()
		{
			if (data == nullptr)
				throw std::logic_error("Container is empty.");
			node_t *dat = data;
			for (node_t *it = data->next; it != nullptr; it = it->next)
				if (it->data > dat->data)
					dat = it;
			return dat->data;
		}
		const T &max() const
		{
			return const_cast<linked_list *>(this)->max();
		}
		void reserve()
		{
			if (data != nullptr) {
				node_t *new_data = new node_t(data->data);
				for (node_t *it = data->next; it != nullptr; it = it->next)
					new_data = new node_t(it->data, new_data);
				clear();
				data = new_data;
			}
		}
		T &locate(size_t index)
		{
			node_t *dat = data;
			for (size_t i = 0; dat != nullptr; dat = dat->next, ++i)
				if (i == index)
					return dat->data;
			throw std::out_of_range("Index out of range.");
		}
		const T &locate(size_t index) const
		{
			const_cast<linked_list *>(this)->locate(index);
		}
		void tidy_up()
		{
			node_t *target = nullptr;
			for (node_t *it = data; it != nullptr; it = it->next) {
				for (node_t *matched = it->next; matched != nullptr; matched = matched->next) {
					if (matched->data == it->data) {
						target = it;
						break;
					}
				}
				if (target != nullptr)
					break;
			}
			if (target != nullptr) {
				for (node_t *previous = target, *it = target->next; it != nullptr;) {
					if (target->data == it->data) {
						previous->next = it->next;
						delete it;
						it = previous->next;
					}
					else {
						previous = previous->next;
						it = it->next;
					}
				}
				tidy_up();
			}
		}
		void merge(const linked_list &list)
		{
			if (&list == this)
				throw std::logic_error("Self merge.");
			if (data != nullptr) {
				node_t *tail = data;
				for (; tail->next != nullptr; tail = tail->next)
					;
				tail->next = list.copy();
			}
			else
				data = list.copy();
			sort();
		}
		void sort()
		{
			// TODO
		}
	};
} // namespace mendel
template <typename T>
std::ostream &operator<<(std::ostream &o, const mendel::linked_list<T> &list)
{
	using node_t = typename mendel::linked_list<T>::node_t;
	for (node_t *it = list.data; it != nullptr; it = it->next)
		o << it->data << "\t";
	o << std::flush;
	return o;
}