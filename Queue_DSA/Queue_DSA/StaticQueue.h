#pragma once

#include "Queue.h"

const int MAX_SIZE = 8;

template <typename T>
class StaticQueue : public Queue<T>
{
private:
	T data[MAX_SIZE];
	int front;
	int back;
	size_t size;

private:
	bool isFull() const;

public:
	StaticQueue();
	void pop();
	void push(const T& element);
	const T& frontEl() const;
	bool empty() const;

};

template<typename T>
inline bool StaticQueue<T>::isFull() const
{
	return size == MAX_SIZE;
}

template<typename T>
inline StaticQueue<T>::StaticQueue() : size(0), front(0), back(-1)
{
}

template<typename T>
inline void StaticQueue<T>::pop()
{
	if (empty())
	{
		std::cerr << "Empty queue!!!" << std::endl;
		return;
	}
	++front;
	front = front % MAX_SIZE;
	--size;
}

template<typename T>
inline void StaticQueue<T>::push(const T & element)
{
	if (isFull())
	{
		std::cerr << "Full queue!!!" << std::endl;
		return;
	}
	++back;
	back = back % MAX_SIZE;
	data[back] = element;
	++size;
}

template<typename T>
inline const T & StaticQueue<T>::frontEl() const
{
	if (empty())
	{
		std::cerr << "Empty queue!!!" << std::endl;
		return T();
	}
	return data[front];
}

template<typename T>
inline bool StaticQueue<T>::empty() const
{
	return size == 0;
}
