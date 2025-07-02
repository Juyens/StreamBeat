#pragma once

template <typename K, typename V>
class HashEntry
{
public:
	K key;
	V value;

	HashEntry() = default;

	HashEntry(const K& key, V&& value)
		: key(key), value(std::move(value)) {}

	HashEntry(const K& key, const V& value)
		: key(key), value(value) {}
};