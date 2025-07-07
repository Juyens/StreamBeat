#pragma once

#include "Node.h"

#include <stdexcept>

template<class T>
class Queue
{
public:
	Queue() = default;
	~Queue();

	Queue(const Queue& other) = delete;
	Queue& operator=(const Queue& other) = delete;

	Queue(Queue&& other) noexcept;
	Queue& operator=(Queue&& other) noexcept;

	template <typename U>
	void enqueue(U&& value);

	void dequeue();
	const T& peek() const;

	bool empty() const;
	uint size() const;

	void clear();

private:
	Node<T>* front_{ nullptr };
	Node<T>* tail_{ nullptr };
	uint size_{ 0 };
};

template<class T>
inline Queue<T>::~Queue()
{
	clear();
}

template<class T>
inline Queue<T>::Queue(Queue&& other) noexcept
	: front_(other.front_), tail_(other.tail_), size_(other.size_)
{
	other.front_ = nullptr;
	other.tail_ = nullptr;
	other.size_ = 0;
}

template<class T>
inline Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept
{
	if (this != &other)
	{
		clear();

		front_ = other.front_;
		tail_ = other.tail_;
		size_ = other.size_;

		other.front_ = nullptr;
		other.tail_ = nullptr;
		other.size_ = 0;
	}
	return *this;
}

template<class T>
template <typename U>
inline void Queue<T>::enqueue(U&& value)
{
	Node<T>* node = new Node<T>(T(std::forward<U>(value)));

	if (!tail_)
		front_ = tail_ = node;
	else
	{
		tail_->next = node;
		tail_ = node;
	}
	++size_;
}

template<class T>
inline void Queue<T>::dequeue()
{
	if (empty())
		throw std::runtime_error("Queue is empty");

	Node<T>* temp = front_;
	front_ = front_->next;
	delete temp;
	--size_;

	if (size_ == 0)
		tail_ = nullptr;
}

template<class T>
inline const T& Queue<T>::peek() const
{
	if (empty())
		throw std::runtime_error("Queue is empty");

	return front_->data;
}

template<class T>
inline bool Queue<T>::empty() const
{
	return size_ == 0;
}

template<class T>
inline uint Queue<T>::size() const
{
	return size_;
}

template<class T>
inline void Queue<T>::clear()
{
	while (front_)
	{
		Node<T>* temp = front_;
		front_ = front_->next;
		delete temp;
	}
	tail_ = nullptr;
	size_ = 0;
}