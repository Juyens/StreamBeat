#pragma once

#include "Node.h"

#include <stdexcept>
#include <utility>

template<class T>
class Stack
{
public:
	Stack() = default;
	~Stack();

	Stack(const Stack& other) = delete;
	Stack& operator=(const Stack& other) = delete;

	Stack(Stack&& other) noexcept;
	Stack& operator=(Stack&& other) noexcept;

	template <typename U>
	void push(U&& value);

	void pop();
	const T& peek() const;

	bool empty() const;
	uint size() const;

	void clear();

private:
	Node<T>* top_{ nullptr };
	uint size_{ 0 };
};

template<class T>
inline Stack<T>::~Stack()
{
	clear();
}

template<class T>
inline Stack<T>::Stack(Stack&& other) noexcept
	: top_(other.top_), size_(other.size_)
{
	other.top_ = nullptr;
	other.size_ = 0;
}

template<class T>
inline Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
	if (this != &other)
	{
		clear();
		top_ = other.top_;
		size_ = other.size_;

		other.top_ = nullptr;
		other.size_ = 0;
	}
	return *this;
}

template<class T>
template <typename U>
inline void Stack<T>::push(U&& value)
{
	top_ = new Node<T>(T(std::forward<U>(value)), top_);
	++size_;
}

template<class T>
inline void Stack<T>::pop()
{
	if (empty())
		throw std::runtime_error("Stack is empty");

	Node<T>* temp = top_;
	top_ = top_->next;
	delete temp;
	--size_;
}

template<class T>
inline const T& Stack<T>::peek() const
{
	if (empty())
		throw std::runtime_error("Stack is empty");

	return top_->data;
}

template<class T>
inline bool Stack<T>::empty() const
{
	return top_ == nullptr;
}

template<class T>
inline uint Stack<T>::size() const
{
	return size_;
}

template<class T>
inline void Stack<T>::clear()
{
	while (top_)
	{
		Node<T>* temp = top_;
		top_ = top_->next;
		delete temp;
	}
	size_ = 0;
}