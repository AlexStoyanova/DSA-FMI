#include "LinkedList.h"


void testFunc()
{
	LinkedList<int> list;
	list.insertBegin(5);
	list.insertEnd(1);

	LinkedList<int>::Iterator it = list.begin();
	list.insertBefore(6, it);
	++it;
	list.insertAfter(7, it);
	list.print();

	LinkedList<int> list2;
	list2.insertBegin(8);
	list2.insertEnd(9);

	list.append(list2);
	list.print();

	int x;
	list2.deleteEnd(x);
	list2.print();

	std::cout << (list.empty() ? "Empty!" : "Not empty!") << std::endl;

	LinkedList<int>::Iterator it2 = list2.begin();
	std::cout << it2.get() << std::endl;
	list2.deleteBegin(x);
	std::cout << (list2.empty() ? "Empty!" : "Not empty!") << std::endl;

}

int main()
{
	testFunc();
	return 0;
}