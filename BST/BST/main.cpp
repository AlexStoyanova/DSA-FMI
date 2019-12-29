#include "BSTree.h"

void test()
{
	BSTree<int> bs;
	bs.addElement(5);
	bs.addElement(7);
	bs.addElement(4);
	bs.addElement(6);
	bs.addElement(3);
	bs.addElement(8);
	bs.print();
	std::cout << std::endl;
	std::cout << bs.getHeight() << std::endl;
	bs.removeElement(4);
	bs.print();
	std::cout << std::endl;
	bs.findElemAndTakeSubtree(7).print();
	std::cout << std::endl;
	BSTree<int> bs2 = bs;
	bs2.print();
	std::cout << std::endl;
	BSTree<int> bs3;
	bs3 = bs2;
	bs3.print();
}

int main()
{
	test();
	return 0;
}