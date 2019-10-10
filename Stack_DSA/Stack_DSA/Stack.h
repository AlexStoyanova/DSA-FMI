#ifndef STACK_H
#define STACK_H
#include <stdexcept>

template <typename T>
class Stack
{
private:
	size_t capacity;
	size_t top;
	T* data;

private:
	void clear();
	void copyFrom(const Stack<T>& other);
	void resize();

public:
	Stack();
	Stack(size_t newCapacity);
	Stack(const Stack<T>& other);
	Stack<T>& operator=(const Stack<T>& rhs);
	~Stack();

	bool isEmpty() const;
	void push(const T& member);
	void pop();
	const T& peek() const;
	size_t size() const;
};

#endif

template<typename T>
inline void Stack<T>::clear()
{
	delete[] data;
}

template<typename T>
inline void Stack<T>::copyFrom(const Stack<T>& other)
{
	top = other.top;
	capacity = other.capacity;
	for (size_t i = 0; i < top; ++i)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
inline void Stack<T>::resize()
{
	T* buff;
	buff = data;
	data = new T[2 * capacity];
	for (size_t i = 0; i < top; ++i)
	{
		data[i] = buff[i];
	}
	delete[] buff;
	capacity *= 2;
}

template<typename T>
inline Stack<T>::Stack() : capacity(0), top(0), data(nullptr)
{}

template<typename T>
inline Stack<T>::Stack(size_t newCapacity) : capacity(newCapacity), top(0)
{
	data = new T[capacity];
}

template<typename T>
inline Stack<T>::Stack(const Stack<T>& other)
{
	copyFrom(other);
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}

template<typename T>
inline Stack<T>::~Stack()
{
	clear();
}


template<typename T>
inline bool Stack<T>::isEmpty() const
{
	return !top;
}

template<typename T>
inline void Stack<T>::push(const T & member)
{
	if (top == capacity)
	{
		resize();
	}
	data[top++] = member;
}

template<typename T>
inline void Stack<T>::pop()
{
	if (isEmpty())
	{
		throw std::logic_error("the stack is empty");
	}
	top--;
}

template<typename T>
inline const T & Stack<T>::peek() const
{
	if (isEmpty())
	{                                                 
		throw std::logic_error("the stack is empty");
	}
	return data[top - 1];
}

template<typename T>
inline size_t Stack<T>::size() const
{
	return top;
}
