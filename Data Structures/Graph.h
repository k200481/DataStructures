#pragma once

#include <iostream>
#include "LinkedList.h"
#include "DSA.h"
#include "Queue.h"
#include "Stack.h"

template <typename T>
class Graph
{
private:
	struct Edge
	{
		size_t src;
		size_t dst;
		int weight;
	};

public:
	Graph() = default;

	void AddVertex(size_t val)
	{
		verts.push_back(val);
		edges.push_back(SinglyLinkedList<Edge>());
	}

	void AddEdge(const T& src, const T& dst, int weight = 1)
	{
		size_t verts_size = verts.size();
		size_t src_idx = GetVertIdx(src);
		size_t dst_idx = GetVertIdx(dst);

		if (src_idx == verts_size)
		{
			AddVertex(src);
			src_idx = verts.size() - 1;
		}
		if (dst_idx == verts_size)
		{
			AddVertex(dst);
			dst_idx = verts.size() - 1;
		}

		edges[src_idx].push_back({ src_idx, dst_idx, weight });
		edges[dst_idx].push_back({ dst_idx, src_idx, weight });
	}

	void BFS(const T& src)
	{
		auto src_idx = GetVertIdx(src);
		if (src_idx == verts.size())
		{
			throw std::exception("Vertex does not exist");
			return;
		}

		LinkedListQueue<DSA<size_t>> q;
		q.push(DSA<size_t>{ 1, src_idx });

		while (!q.empty())
		{
			auto f = q.front();
			q.pop();

			bool completed = true;
			for (auto& e : edges[f.back()])
			{
				if (!f.Has(e.dst))
				{
					auto temp = f;
					temp.push_back(e.dst);
					q.push(temp);
					completed = false;
				}
			}

			if (completed)
			{
				for (auto& idx : f)
				{
					std::cout << verts[idx] << " ";
				}
				std::cout << std::endl;
			}
		}
	}

	void DFS(const T& src)
	{
		size_t src_idx = GetVertIdx(src);
		if (src_idx == verts.size())
		{
			throw std::exception("Vertex does not exist");
			return;
		}

		LinkedListStack<DSA<size_t>> s;
		s.push(DSA<size_t>{ 1, src_idx });

		while (!s.empty())
		{
			auto f = s.top();
			s.pop();

			bool completed = true;
			for (auto& e : edges[f.back()])
			{
				if (!f.Has(e.dst))
				{
					auto temp = f;
					temp.push_back(e.dst);
					s.push(temp);
					completed = false;
				}
			}

			if (completed)
			{
				for (auto& idx : f)
				{
					std::cout << verts[idx] << " ";
				}
				std::cout << std::endl;
			}
		}
	}

	void Bellmanford(const T& src)
	{
		size_t src_idx = GetVertIdx(src);
		size_t num_verts = verts.size();

		DSA<int> dist(num_verts, INT_MAX);
		dist[src_idx] = 0;

		for (size_t i = 0; i < num_verts - 1; i++)
		{
			// equivalent to a single for loop through all edges
			for (auto& lst : edges)
			{
				for (auto& e : lst)
				{
					if (dist[e.src] != INT_MAX && dist[e.dst] > dist[e.src] + e.weight)
					{
						dist[e.dst] = dist[e.src] + e.weight;
					}
				}
			}
		}

		for (auto& lst : edges)
		{
			for (auto& e : lst)
			{
				if (dist[e.src] != INT_MAX && dist[e.dst] > dist[e.src] + e.weight)
				{
					std::cout << "Graph has negative weight cycle\n";
					return;
				}
			}
		}

		for (size_t i = 0; i < verts.size(); i++)
		{
			std::cout << "dist(" << verts[i] << ") = " << dist[i] << std::endl;
		}
	}

private:
	size_t GetVertIdx(const T& val)
	{
		for (size_t i = 0; i < verts.size(); i++)
		{
			if (val == verts[i])
				return i;
		}
		return verts.size();
	}

private:
	DSA<T> verts;
	DSA<SinglyLinkedList<Edge>> edges;
};

