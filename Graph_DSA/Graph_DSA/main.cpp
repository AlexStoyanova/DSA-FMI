#include "Graph.h"

void test()
{
	Graph g;
	for (int i = 1; i <= 10; ++i)
	{
		g.addVertex(i);
	}
	g.addEdge(7, 9);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 5);
	g.addEdge(4, 6);
	g.addEdge(5, 6);
	g.addEdge(7, 8);

	g.addEdge(7, 10);

	std::vector<int> ch = g.children(7);
	int sizeCh = ch.size();
	for (int i = 0; i < sizeCh; ++i)
	{
		std::cout << ch[i] << " ";
	}
	std::cout << std::endl;

	std::vector<int> p = g.parents(6);
	int sizeP = p.size();
	for (int i = 0; i < sizeP; ++i)
	{
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	g.removeVertex(10);
	g.removeEdge(7, 8);
	std::cout << (g.hasEdge(7, 9) ? "Yes" : "No") << std::endl;
}


int main()
{
	test();
	return 0;
}