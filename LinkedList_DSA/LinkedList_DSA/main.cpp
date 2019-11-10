#include "LinkedList.h"

void testFunction()
{
	LinkedList<int> ll;
	ll.insertToEnd(1);
	ll.insertToEnd(2);
	ll.insertToEnd(3);

	std::cout << "After insert to end: ";
	ll.print();

	ll.iterStart();
	Node<int>* ptr = ll.iter();
	ll.insertBefore(ptr, 5);

	std::cout << "After insert before start: ";
	ll.print();

	ll.insertAfter(ptr, 6);

	std::cout << "After insert after start: ";
	ll.print();

	ll.iterStart();
	ptr = ll.iter();
	ptr = ll.iter();
	ll.insertAfter(ptr, 7);

	std::cout << "After insert after second element: ";
	ll.print();

	int x;
	ll.deleteAfter(ptr, x);

	std::cout << "After delete after second element: ";
	ll.print();

	std::cout << "Print the data of deleted element: " << x << std::endl;

	ll.deleteBefore(ptr, x);

	std::cout << "After delete before second element: ";
	ll.print();

	std::cout << "Print the data of deleted element: " << x << std::endl;

	ll.deleteElem(ptr, x);

	std::cout << "After delete first element: ";
	ll.print();

	std::cout << "Print the data of deleted element: " << x << std::endl;

	std::cout << "Print length of list: " << ll.length() << std::endl;

	LinkedList<int> ll2 = ll;

	std::cout << "Copy list1 in list2: ";
	ll2.print();
}

int main()
{
	testFunction();
	
	return 0;
}