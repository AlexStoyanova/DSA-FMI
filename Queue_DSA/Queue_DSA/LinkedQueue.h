#pragma once

#include "Queue.h"

template <typename T>
class LinkedQueue : public Queue<T>
{
private:
	struct Node
	{
		T data;
		Node* nextPtr;

		Node(const T& data, Node* nextPtr = nullptr) : data(data), nextPtr(nextPtr){}
	};

private:
	Node* front;
	Node* back;

private:
	void copyFrom(const LinkedQueue<T>& other);
	void clear();

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T>& other);
	LinkedQueue<T>& operator=(const LinkedQueue<T>& rhs);
	~LinkedQueue();

	void pop();
	void push(const T& data);
	const T& frontEl() const;
	bool empty() const;
};

template<typename T>
inline void LinkedQueue<T>::copyFrom(const LinkedQueue<T>& other)
{
	front = back = nullptr;
	if (other.front != nullptr)
	{
		Node* temp = other.front;
		while (temp != nullptr)
		{
			push(temp->data);
			temp = temp->nextPtr;
		}
	}
}

template<typename T>
inline void LinkedQueue<T>::clear()
{
	while (!empty())
	{
		pop();
	}
}

template<typename T>
inline LinkedQueue<T>::LinkedQueue() : front(nullptr), back(nullptr)
{}

template<typename T>
inline LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
{
	copyFrom(other);
}

template<typename T>
inline LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}

template<typename T>
inline LinkedQueue<T>::~LinkedQueue()
{
	clear();
}

template<typename T>
inline void LinkedQueue<T>::pop()
{
	if (empty())
	{
		return;
	}
	
	Node* temp = front;
	front = front->nextPtr;

	if (front == nullptr)
	{
		back = nullptr;
	}

	delete temp;
}

template<typename T>
inline void LinkedQueue<T>::push(const T & data)
{
	if (front == nullptr)
	{
		front = new Node(data);
		back = front;
	}
	else
	{
		back->nextPtr = new Node(data);
		back = back->nextPtr;
	}
}

template<typename T>
inline const T & LinkedQueue<T>::frontEl() const
{
	if (empty())
	{
		std::cerr << "Empty queue!!!" << std::endl;
		return T();
	}
	return front->data;
}

template<typename T>
inline bool LinkedQueue<T>::empty() const
{
	return front == nullptr;
}



