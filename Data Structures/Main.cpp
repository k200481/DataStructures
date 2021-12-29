#include <iostream>
#include "Graph.h"

int main(void)
{
	Graph<char> g;

	g.AddEdge('A', 'B');
	g.AddEdge('A', 'C');
	g.AddEdge('A', 'D');
	g.AddEdge('A', 'E');

	g.AddEdge('F', 'A');
	g.AddEdge('G', 'A');

	g.AddEdge('H', 'B');

	g.TopSort();

	return 0;
}