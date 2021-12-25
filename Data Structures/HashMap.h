#pragma once
#include "DSA.h"

// only using linear probing
// the other two aren't different enough to be worth re-implementing the whole class
template<typename K, typename T>
class HashMap
{
	struct Node
	{
		K key;
		T val;
		Node(const K& key, const T& val)
			:
			key(key),
			val(val)
		{}
	};
public:
	HashMap(size_t size)
		:
		arr(size, nullptr)
	{}
	HashMap(const HashMap& rhs)
	{
		*this = rhs;
	}
	HashMap& operator=(const HashMap& rhs)
	{
		// self assignment
		if (this == &rhs)
			return *this;
		// free old memory
		for (int i = 0; i < arr.cur_size(); i++)
			delete arr[i];
		// reset size and creat a new dsa 
		// the old one will be automatically freed by the overloaded operator= in dsa
		size = 0;
		arr = DSA<Node*>(rhs.arr.cur_size(), nullptr);
		// just insert all non-null values into the map
		// we don't really care about the ordeer they are inserted in
		// if we did, we can also just copy over the array in a loop
		// while allocating new memory for the ptrs of course
		for (size_t i = 0; i < rhs.arr.cur_size(); i++)
		{
			if(rhs.arr[i] != nullptr)
				Insert(rhs.arr[i]->key, rhs.arr[i]->val);
		}
		return *this;
	}
	~HashMap()
	{
		for (size_t i = 0; i < arr.cur_size(); i++)
			delete arr[i];
	}

	void Insert(const K& key, const T& val)
	{
		// if the map is full, reallocate memory
		if (size == arr.cur_size())
		{
			// copy the dsa in a temp location
			auto temp = arr;
			// create a new dsa with 2x the size and copy over all its data
			arr = DSA<Node*>(arr.cur_size() * 2, nullptr);
			for (size_t i = 0; i < arr.cur_size(); i++)
			{
				Insert(temp[i]->key, temp[i]->val);
				// delete the ptrs in the old one
				// could alternatively copy the pointers over
				// but can't use the insert func for that, I prefer this for simplicity
				delete temp[i];
			}
		}
		// calculate the hash index and store it there if a spot is availiable
		// or use linear pobing to find an available spot
		size_t idx = Hash(key);
		while (arr[idx] != nullptr)
		{
			idx = (idx + 1) % arr.cur_size();
		}
		arr[idx] = new Node(key, val);
		size++;
	}
	const T& Search(const K& key) const
	{
		// check if the value is at the base hashed index
		size_t idx_base = Hash(key);
		// if nothing is there, the value definitely havn't been entered
		if(arr[idx_base] == nullptr)
			throw std::exception("Invalid argument, value does not exist");
		// if it is there, return ref to val
		if (arr[idx_base]->key == key)
		{
			return arr[idx_base]->val;
		}
		// if there is something there but no the desired val
		// search using linear probing
		size_t idx = (idx_base + 1) % arr.cur_size();
		while (arr[idx] != nullptr && arr[idx]->key != key && idx != idx_base)
		{
			idx = (idx + 1) % arr.cur_size();
		}
		// throw excep if not found
		if (idx == idx_base || arr[idx] == nullptr)
		{
			throw std::exception("Invalid argument, value does not exist");
		}
		// return ref
		return arr[idx]->val;
	}
	T& Search(const K& key)
	{
		return const_cast<T&>(((const HashMap*)this)->Search(key));
	}

private:
	size_t Hash(const K& key) const
	{
		// simple mod
		return key % arr.cur_size();
	}

private:
	// array of pointers to make it possible to have "Unassigned" values
	// would be easier to just use a struct with a bool 'assigned' member
	DSA<Node*> arr;
	size_t size = 0;
};