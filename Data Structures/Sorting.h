#pragma once
#include "DSA.h"

template <typename T>
void InsertionSort(DSA<T>& arr)
{
	auto size = arr.cur_size();
	for (size_t i = 1; i < size; i++)
	{
		size_t pos = i;
		auto temp = arr[pos];
		while (pos > 0 && arr[pos - 1] > temp)
		{
			arr[pos] = arr[pos - 1];
			pos--;
		}
		arr[pos] = temp;
	}
}

template <typename T>
void ShellSort(DSA<T>& arr)
{
	const auto size = arr.cur_size();
	auto N = arr.cur_size() / 3;
	// get the window size
	size_t h = 1;
	while (h < N)
		h = h * 3 + 1;

	// 'h-sort' the array whil decreasing the window-size
	while (h >= 1)
	{
		// insertion sort pairs of elements h indices apart
		for (size_t i = 0; i < size - h; i++)
		{
			for (auto j = i + h; j >= h && arr[j - h] > arr[j]; j -= h)
			{
				if (arr[j - h] > arr[j])
				{
					std::swap(arr[j - h], arr[j]);
				}
			}
		}
		h /= 3;
	}
}

template <typename T>
size_t Partition(DSA<T>& arr, size_t l, size_t r)
{
	std::swap(arr[r], arr[(r + l) / 2]);
	auto p = arr[r];
	// loop until p - 1 to find all 
	size_t k = l;
	for (auto i = l; i < r; i++)
	{
		if (arr[i] < p)
		{
			std::swap(arr[i], arr[k++]);
		}
	}
	std::swap(arr[k], arr[r]);
	return k;
}
template <typename T>
void QuickSort(DSA<T>& arr, size_t l, size_t r)
{
	if (l >= r)
		return;

	auto mid = Partition(arr, l, r);
	QuickSort(arr, l, mid - 1);
	QuickSort(arr, mid + 1, r);
}

template <typename T>
void Merge(DSA<T>& arr, size_t l, size_t mid, size_t r)
{
	DSA<T> left(mid - l + 1);
	DSA<T> right(r - mid);

	for (size_t i = l; i <= mid; i++)
	{
		left[i - l] = arr[i];
	}
	for (size_t i = mid + 1; i <= r; i++)
	{
		right[i - mid - 1] = arr[i];
	}

	size_t i = 0, j = 0, k = l;
	auto ls = left.cur_size(), rs = right.cur_size();
	while (i < ls && j < rs)
	{
		if (left[i] < right[j])
		{
			arr[k++] = left[i++];
		}
		else
		{
			arr[k++] = right[j++];
		}
	}

	while (i < ls)
	{
		arr[k++] = left[i++];
	}
	while (j < rs)
	{
		arr[k++] = right[j++];
	}
}
template <typename T>
void MergeSort(DSA<T>& arr, size_t l, size_t r)
{
	if (l >= r)
		return;

	auto mid = (l + r) / 2;
	MergeSort(arr, l, mid);
	MergeSort(arr, mid + 1, r);
	Merge(arr, l, mid, r);
}

template <typename T>
void Heapify(DSA<T>& arr, size_t i, size_t n)
{
	auto l = 2 * i + 1;
	auto r = 2 * i + 2;
	auto largest = i;
	
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		std::swap(arr[i], arr[largest]);
		Heapify(arr, largest, n);
	}
}
template <typename T>
void HeapSort(DSA<T>& arr)
{
	auto n = arr.cur_size();
	for (size_t i = n / 2 - 1; i >= 0 && i < n; i--)
		Heapify(arr, i, n);

	for (size_t i = n - 1; i > 0; i--)
	{
		std::swap(arr[0], arr[i]);
		Heapify(arr, 0, i);
	}
}
