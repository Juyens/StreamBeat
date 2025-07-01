#pragma once

#include <string>
#include <type_traits>

template <typename K>
class DefaultHash
{
public:
	unsigned int operator()(const K&) const
	{
		static_assert(sizeof(K) == 0, "DefaultHash only supports int and std::string. Please specialize it for your type.");
		return 0;
	}
};

template <>
class DefaultHash<int>
{
public:
	unsigned int operator()(int key) const
	{
		return static_cast<unsigned int>(key);
	}
};

template <>
class DefaultHash<std::string>
{
public:
	unsigned int operator()(const std::string& key) const
	{
		unsigned int hash = 0;
		for (char c : key) {
			hash = 31 * hash + static_cast<unsigned int>(c);
		}
		return hash;
	}
};