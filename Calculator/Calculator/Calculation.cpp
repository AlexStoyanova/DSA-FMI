#include "Calculation.h"

Calculation::Calculation() : size(0)
{
}

bool Calculation::push_back(double element)
{
	if (size == MAX_SIZE)
	{
		return false;
	}
	arr[size++] = element;
	return true;
}

bool Calculation::pop_back()
{
	if (size == 0)
	{
		return false;
	}
	--size;
	return true;
}

void Calculation::add()
{
	if (size < 2)
	{
		return;
	}
	double newElem = arr[size - 1] + arr[size - 2];
	pop_back();
	pop_back();
	push_back(newElem);
}

void Calculation::substract()
{
	if (size < 2)
	{
		return;
	}
	double newElem = arr[size - 1] - arr[size - 2];
	pop_back();
	pop_back();
	push_back(newElem);
}

void Calculation::negative()
{
	if (size == 0)
	{
		return;
	}
	arr[size - 1] = (-1)*arr[size - 1];
}

void Calculation::max() const
{
	if (size == 0)
	{
		std::cout << "none" << std::endl;
		return;
	}
	double maxEl = arr[0];
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] > maxEl)
		{
			maxEl = arr[i];
		}
	}
	std::cout << maxEl << std::endl;
}

void Calculation::print() const
{
	if (size >= 1)
	{
		std::cout << arr[0];
	}
	for (int i = 1; i < size; ++i)
	{
		std::cout << ',' << arr[i];
	}
}

bool Calculation::isEmpty() const
{
	return !size;
}
