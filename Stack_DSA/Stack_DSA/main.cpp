#include <iostream>
#include "Stack.h"

int main()
{
	Stack<int> stack(6);
	stack.peek();
	stack.push(1);
	stack.push(5);
	std::cout << stack.peek() << std::endl;
	stack.pop();
	std::cout << stack.peek() << std::endl;
	std::cout << stack.size() << std::endl;


	return 0;
}