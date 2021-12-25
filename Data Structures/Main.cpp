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

	g.BFS(0);
	g.DFS(0);
	g.Bellmanford(0);

	return 0;
}