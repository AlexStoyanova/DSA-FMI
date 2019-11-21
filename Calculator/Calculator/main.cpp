#include <iostream>
#include "Calculator.h"
#include <string>

void menu()
{
	Calculator cl;
	std::string command;
	double numberToAdd;
	size_t index;

	while (true)
	{
		std::cin >> command;
		if (command == "CREATE")
		{
			cl.CREATE();
		}
		else if (command == "PUSH")
		{
			std::cin.ignore();
			std::cin >> numberToAdd >> index;
			cl.PUSH(numberToAdd, index);
		}
		else if (command == "POP")
		{
			std::cin.ignore();
			std::cin >> index;
			cl.POP(index);
		}
		else if (command == "ADD")
		{
			cl.ADD();
		}
		else if (command == "SUBSTRACT")
		{
			cl.SUBSTRACT();
		}
		else if (command == "NEGATIVE")
		{
			cl.NEGATIVE();
		}
		else if (command == "MAX")
		{
			cl.MAX();
		}
		else if (command == "PRINT")
		{
			cl.PRINT();
		}
		else if (command == "EXIT")
		{
			break;
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}
}

int main()
{
	menu();
	return 0;
}