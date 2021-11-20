#include <iostream>
#include "Sorting.h"
#include <random>

int main(void)
{
	DSA<int> arr(10);
	std::mt19937 rng((std::random_device())());
	
	for (size_t i = 0; i < 10; i++)
	{
		arr[i] = rng() % 100;
	}

	for (size_t i = 0; i < arr.GetSize(); i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;

	QuickSort(arr, 0, arr.GetSize() - 1);

	for (size_t i = 0; i < arr.GetSize(); i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;

	return 0;
}