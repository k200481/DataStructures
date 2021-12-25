#pragma once
#include "DSA.h"

template <typename T>
class ArrayStack
{
public:
	ArrayStack() = default;
	ArrayStack(size_t size)
		:
		arr(size)
	{
		if (size == 0)
			throw std::invalid_argument("Size must be grater than 0");
	}
	
	void push(const T& val)
	{
		if (top >= arr.GetSize())
		{
			arr.PushBack(val);
			top++;
			return;
		}
		arr[top++] = val;
	}
	const T& top() const
	{
		if (top == 0)
		{
			throw std::exception("Stack Underflow");
		}
		return arr[top - 1];
	}
	void pop()
	{
		if (top > 0)
			top--;
	}
	bool empty() const
	{
		return top == 0;
	}

private:
	DSA<T> arr;
	size_t top = 0;
};

template <typename T>
class LinkedListStack
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
	LinkedListStack() = default;
	~LinkedListStack()
	{
		delete top;
	}
	LinkedListStack(const LinkedListStack& rhs)
	{
		*this = rhs;
	}
	LinkedListStack& operator=(const LinkedListStack& rhs)
	{
		if (this == &rhs)
			return *this;
		delete top;
		Node* ptr = rhs.top;
		while (ptr != nullptr)
		{
			push(ptr->val);
			ptr = ptr->next;
		}
	}

	void push(const T& val)
	{
		if (top == nullptr)
		{
			top = new Node(val);
			return;
		}
		Node* ptr = top;
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
		}
		ptr->next = new Node(val);
	}
	const T& top()
	{
		if (top == nullptr)
		{
			throw std::exception("Stack Underflow");
		}
		return top->val;
	}
	void pop()
	{
		if (top == nullptr)
		{
			throw std::exception("Stack Underflow");
		}
		Node* temp = top;
		top = top->next;
		temp->next = nullptr;
		delete temp;
	}
	bool empty() const
	{
		return top == nullptr;
	}

private:
	Node* top = nullptr;
};