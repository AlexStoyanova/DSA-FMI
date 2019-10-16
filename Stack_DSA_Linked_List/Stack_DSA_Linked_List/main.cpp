#include <iostream>
#include "StackWithLinkedList.h"

int main()
{
	StackWithLinkedList<int> stack;
	stack.push(1);
	stack.push(5);
	stack.push(8);
	stack.push(59);
	stack.push(51);
	std::cout << stack.top() << std::endl;
	stack.pop();
	std::cout << stack.top() << std::endl;
	std::cout << stack.getSize() << std::endl;

	return 0;
}
