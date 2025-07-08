#pragma once

#include "Node.h"
#include "Iterator.h"

#include <functional>
#include <stdexcept>
#include <utility>

template<class T>
class List
{
public:
	using Compare = std::function<bool(const T&, const T&)>;

	List() = default;
	explicit List(Compare compare);

        List(const List& other);
        List& operator=(const List& other);

	List(List&& other) noexcept;
	List& operator=(List&& other) noexcept;

	~List();

	template <typename U>
	void push_front(U&& value);

	template <typename U>
	void push_back(U&& value);

	template <typename U>
	void insert(uint pos, U&& value);

	void remove_front();
	void remove_back();
	void remove(uint pos);

	void swap(uint pos1, uint pos2);
	void clear();

	T& front();
	const T& front() const;

	T& back();
	const T& back() const;

	T& at(uint pos);
	const T& at(uint pos) const;

	T& operator[](uint pos);
	const T& operator[](uint pos) const;

	T& find(const T& value);
	const T& find(const T& value) const;

	uint size() const;
	bool empty() const;

	Iterator<T> begin() { return Iterator<T>(head_); }
	Iterator<T> end() { return Iterator<T>(nullptr); }

private:
	Compare compare_{ nullptr };
	Node<T>* head_{ nullptr };
	Node<T>* tail_{ nullptr };
	uint length_{ 0 };
};

template<class T>
inline List<T>::List(Compare compare)
        : compare_(std::move(compare))
{
}

template<class T>
inline List<T>::List(const List& other)
        : compare_(other.compare_)
{
        Node<T>* current = other.head_;
        while (current)
        {
                push_back(current->data);
                current = current->next;
        }
}

template<class T>
inline List<T>::List(List&& other) noexcept
	: compare_(std::move(other.compare_))
	, head_(other.head_)
	, tail_(other.tail_)
	, length_(other.length_)
{
	other.head_ = nullptr;
	other.tail_ = nullptr;
	other.length_ = 0;
}

template<class T>
inline List<T>& List<T>::operator=(List<T>&& other) noexcept
{
        if (this != &other)
        {
                clear();
                compare_ = std::move(other.compare_);
                head_ = other.head_;
                tail_ = other.tail_;
                length_ = other.length_;

                other.head_ = nullptr;
                other.tail_ = nullptr;
                other.length_ = 0;
        }
        return *this;
}

template<class T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
        if (this != &other)
        {
                clear();
                compare_ = other.compare_;
                Node<T>* current = other.head_;
                while (current)
                {
                        push_back(current->data);
                        current = current->next;
                }
        }
        return *this;
}

template<class T>
inline List<T>::~List()
{
	clear();
}

template<class T>
template<typename U>
inline void List<T>::push_front(U&& value)
{
	head_ = new Node<T>(T(std::forward<U>(value)), head_);
	if (length_ == 0)
		tail_ = head_;
	++length_;
}

template<class T>
template<typename U>
inline void List<T>::push_back(U&& value)
{
	auto* node = new Node<T>(std::forward<U>(value));
	if (!head_)
		head_ = tail_ = node;
	else
	{
		tail_->next = node;
		tail_ = node;
	}
	++length_;
}

template<class T>
template<typename U>
inline void List<T>::insert(uint pos, U&& value)
{
	if (pos > length_)
		throw std::out_of_range("insert: invalid position");

	if (pos == 0)
		push_front(std::forward<U>(value));
	else if (pos == length_)
		push_back(std::forward<U>(value));
	else
	{
		Node<T>* prev = head_;
		for (uint i = 0; i < pos - 1; ++i)
			prev = prev->next;

		prev->next = new Node<T>(T(std::forward<U>(value)), prev->next);
		++length_;
	}
}

template<class T>
inline void List<T>::remove_front()
{
	if (!head_)
		throw std::runtime_error("List is empty");

	Node<T>* temp = head_;
	head_ = head_->next;
	delete temp;
	--length_;

	if (length_ == 0)
		tail_ = nullptr;
}

template<class T>
inline void List<T>::remove_back()
{
	if (!head_)
		throw std::runtime_error("List is empty");

	if (head_ == tail_)
	{
		delete head_;
		head_ = tail_ = nullptr;
	}
	else
	{
		Node<T>* current = head_;
		while (current->next != tail_)
			current = current->next;

		delete tail_;
		tail_ = current;
		tail_->next = nullptr;
	}
	--length_;
}

template<class T>
inline void List<T>::remove(uint pos)
{
	if (pos >= length_)
		throw std::out_of_range("remove: invalid position");

	if (pos == 0)
		remove_front();
	else
	{
		Node<T>* prev = head_;
		for (uint i = 0; i < pos - 1; ++i)
			prev = prev->next;

		Node<T>* temp = prev->next;
		prev->next = temp->next;

		if (temp == tail_)
			tail_ = prev;

		delete temp;
		--length_;
	}
}

template<class T>
inline void List<T>::swap(uint pos1, uint pos2)
{
	if (pos1 >= length_ || pos2 >= length_)
		throw std::out_of_range("swap: invalid positions");

	if (pos1 == pos2)
		return;

	if (pos1 > pos2)
		std::swap(pos1, pos2);

	Node<T>* a = head_;
	for (uint i = 0; i < pos1; ++i)
		a = a->next;

	Node<T>* b = a;
	for (uint i = pos1; i < pos2; ++i)
		b = b->next;

	std::swap(a->data, b->data);
}

template<class T>
inline void List<T>::clear()
{
	Node<T>* current = head_;
	while (current)
	{
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	head_ = tail_ = nullptr;
	length_ = 0;
}

template<class T>
inline T& List<T>::front()
{
	if (!head_)
		throw std::runtime_error("List is empty");

	return head_->data;
}

template<class T>
inline const T& List<T>::front() const
{
	if (!head_)
		throw std::runtime_error("List is empty");

	return head_->data;
}

template<class T>
inline T& List<T>::back()
{
	if (!tail_)
		throw std::runtime_error("List is empty");

	return tail_->data;
}

template<class T>
inline const T& List<T>::back() const
{
	if (!tail_)
		throw std::runtime_error("List is empty");

	return tail_->data;
}

template<class T>
inline T& List<T>::at(uint pos)
{
	if (pos >= length_)
		throw std::out_of_range("at: invalid position");

	Node<T>* current = head_;
	for (uint i = 0; i < pos; ++i)
		current = current->next;

	return current->data;
}

template<class T>
inline const T& List<T>::at(uint pos) const
{
	if (pos >= length_)
		throw std::out_of_range("at: invalid position");

	Node<T>* current = head_;
	for (uint i = 0; i < pos; ++i)
		current = current->next;

	return current->data;
}

template<class T>
inline T& List<T>::operator[](uint pos)
{
	return at(pos);
}

template<class T>
inline const T& List<T>::operator[](uint pos) const
{
	return at(pos);
}

template<class T>
inline T& List<T>::find(const T& value)
{
	Node<T>* current = head_;
	while (current)
	{
		if (compare_ ? compare_(current->data, value) : current->data == value)
			return current->data;
		current = current->next;
	}
	throw std::runtime_error("Value not found in list");
}

template<class T>
inline const T& List<T>::find(const T& value) const
{
	Node<T>* current = head_;
	while (current)
	{
		if (compare_ ? compare_(current->data, value) : current->data == value)
			return current->data;
		current = current->next;
	}
	throw std::runtime_error("Value not found in list");
}

template<class T>
inline uint List<T>::size() const
{
	return length_;
}

template<class T>
inline bool List<T>::empty() const
{
	return length_ == 0;
}