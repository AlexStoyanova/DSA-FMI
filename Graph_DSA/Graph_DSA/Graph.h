#pragma once
#include <iostream>
#include <vector>

class Graph
{
private:
	std::vector<std::vector<int>> g;

private:
	void removeVertexFromChildren(int vertex);
	int positionOfVertex(int vertex);
	bool isValidPosition(int pos);
	int positionOfChild(int child, int vertexPos);

public:
	bool addVertex(int vertex);
	bool addEdge(int v1, int v2);
	bool removeVertex(int vertex);
	bool removeEdge(int v1, int v2);
	bool isVertex(int vertex);
	bool isEmpty();
	bool hasEdge(int v1, int v2);
	std::vector<int> children(int vertex);
	std::vector<int> parents(int vertex);
};

