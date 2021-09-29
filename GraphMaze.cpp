#include <iostream>
#include <vector>
#include <queue>
#include <stack>

template <class C>
class Graph
{
public:
	// add a new vertex
	void AddVertex(const C& c)
	{
		verts.push_back(c);
		adj.push_back({});
	}
	// create an edge between two vertices
	// the second vertex doesn't need to exist at the time of creating the edge
	void AddEdge(int a, int b)
	{
		adj[a].push_back(b);
	}
	// print all edges for each vertex in the graph
	void PrintEdges() const
	{
		for (int i = 0; i < adj.size(); i++)
		{
			std::cout << verts[i] << ": ";
			for (int j = 0; j < adj[i].size(); j++)
			{
				std::cout << verts[adj[i][j]] << ' ';
			}
			std::cout << std::endl;
		}
	}

	void BFS(int goal) const
	{
		// initialise everything needed by the utility func
		std::vector<bool> visited(verts.size());
		std::vector<int> parents(verts.size());
		std::queue<int> q;
		q.push(0);

		// set the starting node to 'visited'
		visited[0] = true;

		// if the utility func can find a path through the maze
		if (_BFS(q, visited, parents, verts[goal]))
		{
			// fill up a 'path' stack by going backwards from the end of the maze
			// following the parents to the starting node
			std::stack<C> path;
			int i = goal;
			while (i != 0)
			{
				path.push(verts[i]);
				i = parents[i];
			}
			path.push(verts[0]);

			// print the stack
			while (!path.empty())
			{
				std::cout << path.top() << ' ';
				path.pop();
			}
		}
	}

private:
	// utility function
	bool _BFS(std::queue<int>& q, std::vector<bool>& visited, std::vector<int>& parents, const C& val) const
	{
		// as long as the queue is not empty
		if(!q.empty())
		{
			// retrueve the first val
			int f = q.front();
			q.pop();

			// if it is the goal, return
			if (verts[f] == val)
			{
				return true;
			}
			// iterate through all the adjacent nodes and add them to the queue
			// if they haven't already been visited
			for (auto i = adj[f].begin(); i != adj[f].end(); i++)
			{
				if (!visited[*i])
				{
					visited[*i] = true;
					q.push(*i);
					parents[*i] = f;
				}
			}
			// recursively call the utility func
			return _BFS(q, visited, parents, val);
		}
		// if the queue was found to be empty, there is no path to the target node
		return false;
	}
private:
	// vertices/nodes
	std::vector<C> verts;
	// adjacency list
	std::vector<std::vector<int>> adj;
};

// useful struct to manage and keep track of maze coordinates
struct Coordinates
{
	int x;
	int y;

	Coordinates operator+(const Coordinates& rhs)
	{
		return { x + rhs.x, y + rhs.y };
	}

	friend std::ostream& operator<<(std::ostream& out, const Coordinates& c)
	{
		out << '(' << c.x << ',' << c.y << ')';
		return out;
	}

	bool operator==(const Coordinates& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
};

int main(void)
{
	// maze
	// can be of any size, just has to be square or rectangle
	std::vector<std::vector<int>> verts =
	{
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,1,1,1},
		{1,0,1,0,0},
		{1,1,1,1,1},
	};


	// lambda to check if a node is on the maze and is accessible
	auto IsSafe = [&verts](Coordinates c) 
	{
		return c.y >= 0 && c.y < verts.size() && c.x >= 0 && c.x < verts[c.y].size() && verts[c.y][c.x];
	};
	// lambda to convert cartesian coords to vector indices
	// since the graph uses a single linear vector
	auto xytoi = [&verts](int x,  int y)
	{
		return verts[0].size() * y + x;
	};

	// the drections the rat can travel in
	// essentially no restrictions
	std::vector<Coordinates> dir = 
	{
		{ 1, 0 },
		{ 0, 1 },
		{ 0, -1 },
		{ -1, 0 },
	};

	// create and set up the graph structure
	Graph<Coordinates> g;
	// iterate through each node
	for (int y = 0; y < verts.size(); y++)
	{
		for (int x = 0; x < verts[y].size(); x++)
		{
			// add the node to the graph
			g.AddVertex({ x,y });
			if (IsSafe({ x, y }))
			{
				// iterate through all possible directions and add the ones 
				// that are accessible (not outside the maze or blocked) 
				// to the list of edges for each node
				for (int i = 0; i < dir.size(); i++)
				{
					Coordinates c = Coordinates{ x, y } + dir[i];
					if (IsSafe(c))
					{
						g.AddEdge(xytoi(x, y), xytoi(c.x, c.y));
					}
				}
			}
		}
	}

	// call bfs with the last node as the target
	// could be aany node
	g.BFS(xytoi(verts[verts.size() - 1].size() - 1, verts.size() - 1));

	return 0;
}