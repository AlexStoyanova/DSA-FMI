#pragma once
#include "Calculation.h"

class Calculator
{
private:
	Calculation* arr;
	int size;
	int capacity;

private:
	void copyFrom(const Calculator& other);
	void clear();
	void resize();

public:
	Calculator();
	Calculator(int newCapacity);
	Calculator(const Calculator& other);
	Calculator& operator=(const Calculator& rhs);
	~Calculator();

	void CREATE();
	void PUSH(double number, size_t index);
	void POP(size_t index);
	void ADD();
	void SUBSTRACT();
	void NEGATIVE();
	void MAX() const;
	void PRINT() const;

};

