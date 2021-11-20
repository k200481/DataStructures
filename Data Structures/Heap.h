#pragma once
#include "DSA.h"

template <typename T>
class Heap
{
public:
	Heap() = default;
	Heap(size_t size)
		:
		arr(size)
	{}

	void Push(const T& val)
	{
		if (idx == arr.GetSize())
		{
			arr.PushBack(val);
			idx++;
			ShiftUp(idx - 1);
			return;
		}

		arr[idx++] = val;
		ShiftUp(idx - 1);
	}
	const T& Peek() const
	{
		if (idx == 0)
			throw std::exception("Heap is Empty");
		return arr[0];
	}
	void Pop()
	{
		if (idx == 0)
			throw std::exception("Heap is Empty");
		else if (idx == 1)
		{
			idx--;
			return;
		}

		idx--;
		std::swap(arr[0], arr[idx]);
		Heapify(0);
	}

	bool IsEmpty() const
	{
		return idx == 0;
	}

private:
	void Heapify(size_t i)
	{
		size_t l = i * i + 1;
		size_t r = i * i + 2;
		size_t largest = i;
		
		if (l < idx && arr[l] > arr[largest])
			largest = l;
		if (r < idx && arr[r] > arr[largest])
			largest = r;

		if (i != largest)
		{
			std::swap(arr[i], arr[largest]);
			Heapify(largest);
		}
	}
	void ShiftUp(size_t i)
	{
		size_t p;
		if (i % 2 == 1)
		{
			// left child
			p = (i - 1) / 2;
		}
		if (i % 2 == 0)
		{
			// left child
			p = (i - 2) / 2;
		}
		
		if (p < i && arr[i] > arr[p])
		{
			std::swap(arr[i], arr[p]);
			ShiftUp(p);
		}
	}

private:
	DSA<T> arr;
	size_t idx = 0;
};