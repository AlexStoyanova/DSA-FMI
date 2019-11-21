#include "Calculator.h"

void Calculator::copyFrom(const Calculator & other)
{
	capacity = other.capacity;
	size = other.size;
	arr = new Calculation[capacity];
	for (int i = 0; i < size; ++i)
	{
		arr[i] = other.arr[i];
	}
}

void Calculator::clear()
{
	delete[] arr;
}

void Calculator::resize()
{
	Calculation* temp;
	temp = arr;
	arr = new Calculation[2 * capacity];
	for (int i = 0; i < size; ++i)
	{
		arr[i] = temp[i];
	}
	capacity *= 2;
	delete[] temp;
}

Calculator::Calculator() : size(0), capacity(1)
{
	arr = new Calculation[1];
}

Calculator::Calculator(int newCapacity) : size(0), capacity(newCapacity)
{
	if (capacity < 1)
	{
		arr = new Calculation[1];
		capacity = 1;
		return;
	}
	arr = new Calculation[capacity];
}

Calculator::Calculator(const Calculator & other)
{
	copyFrom(other);
}

Calculator & Calculator::operator=(const Calculator & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}


Calculator::~Calculator()
{
	clear();
}

void Calculator::CREATE()
{
	if (size == capacity)
	{
		resize();
	}
	Calculation cal;
	arr[size++] = cal;
}

void Calculator::PUSH(double number, size_t index)
{
	if (index < 0 || index >= size)
	{
		return;
	}
	arr[index].push_back(number);
}

void Calculator::POP(size_t index)
{
	if (index < 0 || index >= size)
	{
		return;
	}
	if (arr[index].pop_back())
	{
		if (arr[index].isEmpty())
		{
			for (int i = index; i < size - 1; ++i)
			{
				arr[i] = arr[i + 1];
			}
			--size;
		}
	}
}

void Calculator::ADD()
{
	for (int i = 0; i < size; ++i)
	{
		arr[i].add();
	}
}

void Calculator::SUBSTRACT()
{
	for (int i = 0; i < size; ++i)
	{
		arr[i].substract();
	}
}

void Calculator::NEGATIVE()
{
	for (int i = 0; i < size; ++i)
	{
		arr[i].negative();
	}
}

void Calculator::PRINT() const
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << i << ": [";
		arr[i].print();
		std::cout << "]" << std::endl;

	}
}

void Calculator::MAX() const
{
	for (int i = 0; i < size; ++i)
	{
		arr[i].max();
	}
}
