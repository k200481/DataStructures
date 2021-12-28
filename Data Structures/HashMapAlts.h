#pragma once
#include "DSA.h"
#include "LinkedList.h"

template <typename K, typename T>
class HashMapLinProb
{
	struct Node
	{
		std::pair<K, T> data;
		enum class State
		{
			Empty,
			Occupied,
			Deleted
		} state = State::Empty;
	};
public:
	HashMapLinProb(size_t size, size_t(*hasher)(const K&))
		:
		size(size),
		arr(size),
		hasher(hasher)
	{}

	void Insert(const K& key, const T& data)
	{
		// this should really be an exception
		assert(count < size && "Inserting into full table");

		size_t idx = hasher(key);
		while (arr[idx % size].state == Node::State::Occupied)
		{
			idx++;
		}

		arr[idx % size].data = { key, data };
		arr[idx % size].state = Node::State::Occupied;
		count++;
	}

	std::pair<K, T>* Find(const K& key)
	{
		if (count == 0)
		{
			return nullptr;
		}

		size_t idx = hasher(key);

		if (arr[idx % size].state == Node::State::Empty)
			return nullptr;
		else if (arr[idx % size].state == Node::State::Occupied && arr[idx % size].data.first == key)
			return &arr[idx % size].data;

		auto iter_idx = idx + 1;
		while (iter_idx != idx && arr[iter_idx % size].state != Node::State::Empty)
		{
			if (arr[iter_idx % size].state == Node::State::Occupied && arr[iter_idx % size].data.first == key)
			{
				return &arr[iter_idx % size].data;
			}
			iter_idx++;
		}

		return nullptr;
	}

	void Delete(const K& key)
	{
		size_t idx = hasher(key);

		if (arr[idx % size].state == Node::State::Empty)
		{
			throw std::exception("Attempted to delete a non-existent record");
		}
		else if (arr[idx % size].state == Node::State::Occupied && arr[idx % size].data.first == key)
		{
			arr[idx % size].state = Node::State::Deleted;
			count--;
			return;
		}

		auto iter_idx = idx + 1;
		while (iter_idx != idx && arr[iter_idx % size].state != Node::State::Empty)
		{
			if (arr[iter_idx % size].state == Node::State::Occupied && arr[iter_idx % size].data.first == key)
			{
				arr[iter_idx % size].state = Node::State::Deleted;
				count--;
				return;
			}
			iter_idx++;
		}

		throw std::exception("Attempted to delete a non-existent record");
	}

	bool IsEmpty() const
	{
		return count == 0;
	}

	size_t GetSize() const
	{
		return count;
	}

private:
	size_t size;
	DSA<Node> arr;
	size_t(*hasher)(const K&) = nullptr;
	size_t count = 0;
};

template <typename K, typename T>
class HashMapSepChain
{
	// a neat trick to locally overload == and != for std::pair :D
	struct Node
	{
		std::pair<K, T> data;
		Node(const K& key, const T& data)
			:
			data({ key, data })
		{}
		bool operator==(const Node& rhs) const
		{
			return data.first == rhs.data.first;
		}
		bool operator!=(const Node& rhs) const
		{
			return !(*this == rhs);
		}
	};

public:
	HashMapSepChain(size_t size, size_t(*hasher)(const K&))
		:
		size(size),
		arr(size),
		hasher(hasher)
	{}

	void Insert(const K& key, const T& data)
	{
		size_t idx = hasher(key);
		arr[idx % size].push_back({ key, data });
		count++;
	}

	std::pair<K, T>* Find(const K& key)
	{
		if (count == 0)
		{
			return nullptr;
		}

		size_t idx = hasher(key);
		return &arr[idx % size].find(Node(key, T{}))->data;
	}

	void Delete(const K& key)
	{
		size_t idx = hasher(key);
		arr[idx % size].Delete(Node{ key, "" });
		count--;
	}

	bool IsEmpty() const
	{
		return count == 0;
	}

	size_t GetSize() const
	{
		return count;
	}

private:
	size_t size;
	DSA<SinglyLinkedList<Node>> arr;
	size_t(*hasher)(const K&) = nullptr;
	size_t count = 0;
};