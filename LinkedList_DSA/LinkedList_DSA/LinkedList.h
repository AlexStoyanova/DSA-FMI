#pragma once
#include <iostream> 

template <typename T>
struct Node
{
	T data;
	Node<T>* nextPtr;
	Node(const T& data, Node<T>* nextPtr = nullptr) :data(data), nextPtr(nextPtr) {}
};

template <typename T>
class LinkedList
{
private:
	Node<T>* front;
	Node<T>* back;
	Node<T>* current;

private:
	void copyFrom(const LinkedList<T>& other);
	void clear();

public:

	LinkedList();
	LinkedList(const LinkedList<T>& other);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	~LinkedList();

	void iterStart(Node<T>* ptr = nullptr);
	Node<T>* iter();

	void insertToEnd(const T& x);
	void insertAfter(Node<T>* ptr, const T& x);
	void insertBefore(Node<T>* ptr, const T& x);

	bool deleteAfter(Node<T>* ptr, T& x);
	bool deleteBefore(Node<T>* ptr, T& x);
	bool deleteElem(Node<T>* ptr, T& x);

	void print();
	int length();
};

template<typename T>
inline void LinkedList<T>::copyFrom(const LinkedList<T>& other)
{
	front = back = nullptr;
	if (other.front)
	{
		Node<T>* ptr = other.front;
		while (ptr)
		{
			insertToEnd(ptr->data);
			ptr = ptr->nextPtr;
		}
	}	
}

template<typename T>
inline void LinkedList<T>::clear()
{
	Node<T>* ptr;
	while (front)
	{
		ptr = front;
		front = front->nextPtr;
		delete ptr;	
	}
	back = nullptr;
}

template<typename T>
inline LinkedList<T>::LinkedList() : front(nullptr), back(nullptr)
{}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	copyFrom(other);
}

template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	clear();
}

template<typename T>
inline void LinkedList<T>::iterStart(Node<T> * ptr)
{
	if (ptr == nullptr)
	{
		current = front;
		return;
	}
	current = ptr;
}

template<typename T>
inline Node<T> * LinkedList<T>::iter()
{
	if (current == nullptr)
	{
		return nullptr;
	}
	Node<T>* helper = current;
	current = current->nextPtr;
	return helper;
}

template<typename T>
inline void LinkedList<T>::insertToEnd(const T & x)
{
	Node<T>* ptr = new Node<T>(x);
	if (back == nullptr)
	{
		front = back = ptr;
		return;
	}
	back->nextPtr = ptr;
	back = ptr;
}

template<typename T>
inline void LinkedList<T>::insertAfter(Node<T> * ptr, const T & x)
{
	if (!ptr)
	{
		std::cerr << "Invalid pointer!" << std::endl;
		return;
	}
	Node<T>* newPtr = new Node<T>(x, ptr->nextPtr);
	if (ptr == back)
	{
		back = newPtr;
	}
	ptr->nextPtr = newPtr;
}

template<typename T>
inline void LinkedList<T>::insertBefore(Node<T> * ptr, const T & x)
{
	if (ptr == nullptr)
	{
		std::cerr << "Invalid pointer!" << std::endl;
		return;
	}
	Node<T>* newPtr = new Node<T>(ptr->data, ptr->nextPtr);
	if (ptr == back)
	{
		back = newPtr;
	}
	ptr->data = x;
	ptr->nextPtr = newPtr;
}

template<typename T>
inline bool LinkedList<T>::deleteAfter(Node<T> * ptr, T & x)
{
	if (ptr == nullptr || ptr == back)
	{
		std::cerr << "Invalid pointer!" << std::endl;
		return false;
	}
	Node<T>* deletePtr = ptr->nextPtr;
	x = deletePtr->data;
	ptr->nextPtr = deletePtr->nextPtr;
	if (deletePtr == back)
	{
		back = ptr;
	}
	delete deletePtr;
	return true;
}

template<typename T>
inline bool LinkedList<T>::deleteBefore(Node<T> * ptr, T & x)
{
	if (ptr == nullptr || ptr == front)
	{
		std::cerr << "Invalid pointer!" << std::endl;
		return false;
	}
	Node<T>* prevPtr = front;
	while (prevPtr->nextPtr != ptr)
	{
		prevPtr = prevPtr->nextPtr;
	}
	deleteElem(prevPtr, x);
	return true;
}

template<typename T>
inline bool LinkedList<T>::deleteElem(Node<T> * ptr, T & x)
{
	if (ptr == nullptr)
	{
		std::cerr << "Invalid pointer!" << std::endl;
		return false;
	}
	if (ptr == front)
	{
		x = ptr->data;
		if (ptr == back)
		{
			front = back = nullptr;
		}
		else
		{
			front = front->nextPtr;
		}
		delete ptr;
		return true;
	}
	Node<T>* prevPtr = front;
	while (prevPtr->nextPtr != ptr)
	{
		prevPtr = prevPtr->nextPtr;
	}
	deleteAfter(prevPtr, x);
	return true;
}

template<typename T>
inline void LinkedList<T>::print()
{
	if (front == nullptr)
	{
		return;
	}
	Node<T>* helper = front;
	while (helper)
	{
		std::cout << helper->data << " ";
		helper = helper->nextPtr;
	}
	std::cout << std::endl;
}

template<typename T>
inline int LinkedList<T>::length()
{
	int size = 0;
	Node<T>* helper = front;
	while (helper)
	{
		++size;
		helper = helper->nextPtr;
	}
	return size;
}
