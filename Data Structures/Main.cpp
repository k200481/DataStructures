#include <iostream>
#include "HashMapAlts.h"

constexpr int size = 10;

size_t hasher(const int& i)
{
	return i % 10;
}

int main(void)
{
	HashMapSepChain<int, int> hm(size, hasher);

	std::cout << "Values inserted in order: \n";
	for (int i = 0; i < size; i++)
	{
		int num = rand() % 100;
		hm.Insert(i, num);
		std::cout << num << ' ';
	}
	std::cout << std::endl;

	std::cout << "Values in hash map, in order of keys/insertion\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << hm.Find(i)->second << ' ';
	}

	return 0;
}