#pragma once

template <typename T>
class StackWithLinkedList
{
private:
	struct Node
	{
		T data;
		Node* nextPtr;
		Node(const T& data, Node* nextPtr = nullptr) : data(data), nextPtr(nextPtr) {}
	};

private:
	Node* topPtr;
	size_t currSize;

private:
	void copyStack(const StackWithLinkedList<T>& other);
	void clear();

public:
	StackWithLinkedList();
	StackWithLinkedList(const StackWithLinkedList<T>& other);
	StackWithLinkedList<T> operator=(const StackWithLinkedList<T>& rhs);
	~StackWithLinkedList();

	void push(const T& data);
	void pop();
	const T& top() const;
	bool isEmpty() const;
	size_t getSize() const;
};

template<typename T>
inline void StackWithLinkedList<T>::copyStack(const StackWithLinkedList<T> & other)
{
	if(other.topPtr == nullptr) 
	{
		topPtr = nullptr;
		currSize = 0;
		return;
	}
	topPtr = new Node(other.topPtr->data);
	Node* ours = topPtr;
	Node* theirs = other.topPtr->nextPtr;
	while (theirs != nullptr)
	{
		ours->nexPtr = new Node(thiers->data);
		theirs = theirs->nextPtr;
		ours = ours->nexPtr;
	}
	currSize = other.currSize;
}


template<typename T>
inline void StackWithLinkedList<T>::clear()
{
	Node* destroyer;
	while (topPtr != nullptr)
	{
		destroyer = topPtr;
		topPtr = topPtr->nextPtr;
		delete destroyer;
	}
	currSize = 0;
}

template<typename T>
inline StackWithLinkedList<T>::StackWithLinkedList() : topPtr(nullptr), currSize(0)
{}

template<typename T>
inline StackWithLinkedList<T>::StackWithLinkedList(const StackWithLinkedList<T>& other) : topPtr(nullptr)
{
	copyStack(other);
}

template<typename T>
inline StackWithLinkedList<T> StackWithLinkedList<T>::operator=(const StackWithLinkedList<T>& rhs)
{
	if (this != &rhs)
	{
		clear();
		copyStack(rhs);
	}
	return *this;
}

template<typename T>
inline StackWithLinkedList<T>::~StackWithLinkedList()
{
	clear();
}

template<typename T>
inline void StackWithLinkedList<T>::push(const T & data)
{
	Node* temp = topPtr;
	topPtr = new Node(data, temp);
	++currSize;
}

template<typename T>
inline void StackWithLinkedList<T>::pop()
{
	if (isEmpty())
	{
		return;
	}
	Node* temp = topPtr;
	topPtr = topPtr->nextPtr;
	delete temp;
	--currSize;
}

template<typename T>
inline const T & StackWithLinkedList<T>::top() const
{
	if(isEmpty())
	{
		return T();
	}
	return topPtr->data;
}

template<typename T>
inline bool StackWithLinkedList<T>::isEmpty() const
{
	return !currSize;
}

template<typename T>
inline size_t StackWithLinkedList<T>::getSize() const
{
	return currSize;
}
