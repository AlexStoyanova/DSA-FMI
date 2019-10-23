#pragma once

template <typename T>
class Queue 
{
public:
	virtual void pop() = 0;

	virtual void push(const T& element) = 0;

	virtual const T& frontEl() const = 0;

	virtual bool empty() const = 0;

};
