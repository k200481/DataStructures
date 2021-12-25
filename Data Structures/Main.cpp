#include <iostream>
#include "Graph.h"

int main(void)
{
	Graph<int> g;

	g.AddEdge(0, 1);
	g.AddEdge(0, 2);
	g.AddEdge(0, 3);
	g.AddEdge(0, 4);
	g.AddEdge(0, 5);

	std::cout << "BFS\n";
	g.BFS(0);
	std::cout << "DFS\n";
	g.DFS(0);
	std::cout << "Bellman Ford\n";
	g.Bellmanford(0);

	return 0;
}