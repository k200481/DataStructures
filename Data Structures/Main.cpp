#include <iostream>
#include "AVLTree.h"

int main(void)
{
	AVLTree<int> t;

	t.Insert(5);
	t.Insert(7);
	t.Insert(19);
	t.Insert(12);
	t.Insert(10);
	t.Insert(15);
	t.Insert(18);
	t.Insert(20);
	t.Insert(25);
	t.Insert(23);
	t.Inorder();

	t.Delete(25);
	t.Delete(23);
	t.Inorder();

	return 0;
}