#pragma once

using uint = unsigned int;

template<class T>
class Node
{
public:
	T data;
	Node* next = nullptr;

	Node() = default;

	explicit Node(const T& value, Node* nextNode = nullptr)
		: data{ value }, next{ nextNode } {}

	explicit Node(T&& value, Node* nextNode = nullptr)
		: data{ std::move(value) }, next{ nextNode } {}
};