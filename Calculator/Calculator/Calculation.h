#pragma once
#include <iostream>

const int MAX_SIZE = 256;

class Calculation
{
private:
	double arr[MAX_SIZE];
	int size;

public:
	Calculation();
	
	bool push_back(double element);
	bool pop_back();
	void add();
	void substract();
	void negative();
	void max() const;
	void print() const;
	bool isEmpty() const;

};

