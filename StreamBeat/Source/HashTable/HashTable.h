#pragma once

#include "List.h"
#include "HashEntry.h"
#include "HashFunction.h"

#include <utility>
#include <stdexcept>

template <typename K, typename V, typename Hash = DefaultHash<K>>
class HashTable
{
private:
	List<HashEntry<K, V>>* buckets = nullptr;
	unsigned int capacity = 0;
	unsigned int count = 0;
	Hash hashFunction;

	inline unsigned int getIndex(const K& key) const
	{
		return hashFunction(key) % capacity;
	}

public:
	explicit HashTable(unsigned int initialCapacity = 16);
	~HashTable();

	HashTable(const HashTable&) = delete;
	HashTable& operator=(const HashTable&) = delete;

	HashTable(HashTable&& other) noexcept;
	HashTable& operator=(HashTable&& other) noexcept;

	template <typename U>
	void insert(const K& key, U&& value);

	void erase(const K& key);
	V* find(const K& key);
	V& operator[](const K& key);

	void clear();

	inline unsigned int size() const { return count; }
	inline bool empty() const { return count == 0; }
};

template <typename K, typename V, typename Hash>
inline HashTable<K, V, Hash>::HashTable(unsigned int initialCapacity)
	: capacity(initialCapacity), count(0)
{
	buckets = new List<HashEntry<K, V>>[capacity];
}

template <typename K, typename V, typename Hash>
inline HashTable<K, V, Hash>::~HashTable()
{
	clear();
	delete[] buckets;
}

template <typename K, typename V, typename Hash>
inline HashTable<K, V, Hash>::HashTable(HashTable&& other) noexcept
	: buckets(other.buckets)
	, capacity(other.capacity)
	, count(other.count)
	, hashFunction(std::move(other.hashFunction))
{
	other.buckets = nullptr;
	other.capacity = 0;
	other.count = 0;
}

template <typename K, typename V, typename Hash>
inline HashTable<K, V, Hash>& HashTable<K, V, Hash>::operator=(HashTable&& other) noexcept
{
	if (this != &other)
	{
		clear();
		delete[] buckets;

		buckets = other.buckets;
		capacity = other.capacity;
		count = other.count;
		hashFunction = std::move(other.hashFunction);

		other.buckets = nullptr;
		other.capacity = 0;
		other.count = 0;
	}
	return *this;
}

template <typename K, typename V, typename Hash>
template <typename U>
inline void HashTable<K, V, Hash>::insert(const K& key, U&& value)
{
	unsigned int index = getIndex(key);
	List<HashEntry<K, V>>& bucket = buckets[index];

	for (unsigned int i = 0; i < bucket.size(); ++i)
	{
		HashEntry<K, V>& entry = bucket[i];
		if (entry.key == key)
		{
			entry.value = std::forward<U>(value);
			return;
		}
	}

	bucket.push_back(HashEntry<K, V>(key, std::forward<U>(value)));
	++count;
}

template <typename K, typename V, typename Hash>
inline void HashTable<K, V, Hash>::erase(const K& key)
{
	unsigned int index = getIndex(key);
	List<HashEntry<K, V>>& bucket = buckets[index];

	for (unsigned int i = 0; i < bucket.size(); ++i)
	{
		if (bucket[i].key == key)
		{
			bucket.remove(i);
			--count;
			return;
		}
	}
}

template <typename K, typename V, typename Hash>
inline V* HashTable<K, V, Hash>::find(const K& key)
{
	unsigned int index = getIndex(key);
	List<HashEntry<K, V>>& bucket = buckets[index];

	for (unsigned int i = 0; i < bucket.size(); ++i)
	{
		HashEntry<K, V>& entry = bucket[i];
		if (entry.key == key)
			return &entry.value;
	}
	return nullptr;
}

template <typename K, typename V, typename Hash>
inline V& HashTable<K, V, Hash>::operator[](const K& key)
{
	V* found = find(key);
	if (found)
		return *found;

	insert(key, V{});
	return *find(key);
}

template <typename K, typename V, typename Hash>
inline void HashTable<K, V, Hash>::clear()
{
	if (!buckets) return;
	for (unsigned int i = 0; i < capacity; ++i)
		buckets[i].clear();
	count = 0;
}