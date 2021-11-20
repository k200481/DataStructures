#pragma once
#include "DSA.h"

template <typename T>
class ArrayQueue
{
public:
	ArrayQueue() = default;
	ArrayQueue(size_t size)
		:
		arr(size)
	{}

	void Push(const T& val)
	{
		if (tail >= arr.GetSize())
		{
			arr.PushBack(val);
			tail++;
			return;
		}
		arr[tail++] = val;
	}
	const T& Peek() const
	{
		if (tail == 0)
		{
			throw std::exception("Queue Underflow");
		}
		return arr[head];
	}
	void Pop()
	{
		if (tail == 0)
		{
			throw std::exception("Queue Underflow");
		}
		
		tail--;
		for (size_t i = 0; i < tail; i++)
		{
			arr[i] = arr[i + 1];
		}
	}

	bool IsEmpty() const
	{
		return tail == 0;
	}

private:
	DSA<T> arr;
	size_t head = 0, tail = 0;
};

template <typename T>
class CircularQueue
{
public:
	CircularQueue(size_t size)
		:
		arr(size)
	{}

	void Push(const T& val)
	{
		if (tail == 0)
		{
			arr[tail] = val;
		}
		else if (tail < arr.GetSize())
		{
			if (tail == head)
			{
				// full
				return;
			}
			arr[tail] = val;
		}
		else if (tail == arr.GetSize())
		{
			if (head == 0)
			{
				// full
				return;
			}
			tail = 0;
			arr[tail] = val;
		}
		tail++;
	}
	const T& Peek() const
	{
		if (IsEmpty())
		{
			throw std::exception("Queue Underflow");
		}
		return arr[head];
	}
	void Pop()
	{
		if (head == 0)
		{
			if (tail == 0)
			{
				throw std::exception("Queue Underflow");
			}
			else if (tail == arr.GetSize())
			{
				head++;
				tail = 0;
				return;
			}
		}
		head = (head + 1) % arr.GetSize();
		if (head == tail)
		{
			head = 0;
			tail = 0;
		}
	}

	bool IsEmpty() const
	{
		return tail == 0 && head == 0;
	}

private:
	DSA<T> arr;
	size_t head = 0, tail = 0;
};

template <typename T>
class LinkedListQueue
{
	struct Node
	{
		T val;
		Node* next = nullptr;
		Node(const T& val)
			:
			val(val)
		{}
		~Node()
		{
			delete next;
		}
	};
public:
	LinkedListQueue() = default;
	LinkedListQueue(const LinkedListQueue& rhs)
	{
		*this = rhs;
	}
	LinkedListQueue& operator=(const LinkedListQueue& rhs)
	{
		if (this == &rhs)
			return *this;
		delete head;
		
		Node* ptr = rhs.head;
		while (ptr != nullptr)
		{
			Push(ptr->val);
			ptr = ptr->next;
		}
	}

	void Push(const T& val)
	{
		if (head == nullptr)
		{
			head = new Node(val);
			tail = head;
			return;
		}
		tail->next = new Node(val);
		tail = tail->next;
	}
	const T& Peek() const
	{
		return head->val;
	}
	void Pop()
	{
		if (head == tail)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}
		Node* temp = head;
		head = head->next;
		temp->next = nullptr;
		delete temp;
	}

	bool IsEmpty() const
	{
		return head == nullptr;
	}

private:
	Node* head = nullptr;
	Node* tail = nullptr;
};