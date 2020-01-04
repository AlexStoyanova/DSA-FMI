#include "Graph.h"

void Graph::removeVertexFromChildren(int vertex)
{
	int sizeG = g.size();
	int sizeV;
	for (int i = 0; i < sizeG; ++i)
	{
		sizeV = g[i].size();
		for (int j = 0; j < sizeV; ++j)
		{
			if (g[i][j] == vertex)
			{
				g[i].erase(g[i].begin() + j);
			}
		}
	}
}

int Graph::positionOfVertex(int vertex)
{
	int size = g.size();
	for (int i = 0; i < size; ++i)
	{
		if (g[i].front() == vertex)
		{
			return i;
		}
	}
	return -1;
}

bool Graph::isValidPosition(int pos)
{
	return pos >= 0;
}

int Graph::positionOfChild(int child, int vertexPos)
{
	int sizeV = g[vertexPos].size();
	for (int i = 1; i < sizeV; ++i)
	{
		if (g[vertexPos][i] == child)
		{
			return i;
		}
	}
	return -1;
}

bool Graph::addVertex(int vertex)
{
	if (isVertex(vertex))
	{
		return false;
	}
	std::vector<int> newVertex;
	newVertex.push_back(vertex);
	g.push_back(newVertex);
	return true;
}

bool Graph::addEdge(int v1, int v2)
{
	if (hasEdge(v1, v2))
	{
		return false;
	}
	if (isVertex(v1) && isVertex(v2))
	{
		int size = g.size();
		for (int i = 0; i < size; ++i)
		{
			if (g[i].front() == v1)
			{
				g[i].push_back(v2);
				return true;
			}
		}
	}
	return false;
}

bool Graph::removeVertex(int vertex)
{
	int pos = positionOfVertex(vertex);
	if (isValidPosition(pos))
	{
		g.erase(g.begin() + pos);
		removeVertexFromChildren(vertex);
		return true;
	}
	return false;
}

bool Graph::removeEdge(int v1, int v2)
{
	int pos = positionOfVertex(v1);
	if (isValidPosition(pos))
	{
		int size = g[pos].size();
		for (int i = 0; i < size; ++i)
		{
			if (g[pos][i] == v2)
			{
				g[pos].erase(g[pos].begin() + i);
				return true;
			}
		}
	}
	return false;
}

bool Graph::isVertex(int vertex)
{
	return isValidPosition(positionOfVertex(vertex));
}

bool Graph::isEmpty()
{
	return g.empty();
}

bool Graph::hasEdge(int v1, int v2)
{
	int posVertex = positionOfVertex(v1);
	if (isValidPosition(posVertex))
	{
		int posChild = positionOfChild(v2, posVertex);
		if (isValidPosition(posChild))
		{
			return true;
		}
	}
	return false;
}

std::vector<int> Graph::children(int vertex)
{
	int pos = positionOfVertex(vertex);
	if (isValidPosition(pos))
	{
		int size = g[pos].size();
		std::vector<int> ch;
		for (int i = 1; i < size; ++i)
		{
			ch.push_back(g[pos][i]);
		}
		return ch;
	}
	return std::vector<int>();
}

std::vector<int> Graph::parents(int vertex)
{
	if (isVertex(vertex))
	{
		int sizeG = g.size();
		std::vector<int> p;
		for (int i = 0; i < sizeG; ++i)
		{
			int pos = positionOfChild(vertex, i);
			if (isValidPosition(pos))
			{
				p.push_back(g[i][0]);
			}
		}
		return p;
	}
	return std::vector<int>();
}
