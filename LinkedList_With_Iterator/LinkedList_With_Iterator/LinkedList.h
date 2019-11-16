#pragma once
#include <iostream>

template <typename T>
class LinkedList
{
private:

	struct Node
	{
		T data;
		Node* nextPtr;
		Node(const T& data, Node* nextPtr = nullptr) : data(data), nextPtr(nextPtr){}
	};

public:

	class Iterator
	{

		friend class LinkedList<T>;

	private:
		Node* ptr;

	public:
		Iterator(Node* p = nullptr) : ptr(p){}

		bool valid() const { return ptr != nullptr; }
      
		// it <-> it.valid()
		operator bool() const { return valid(); }

		const T& getConst() const { return ptr->data; }

		T& get() const { return ptr->data; }

		bool operator==(const Iterator& it) const { return ptr == it.ptr; }

		bool operator!=(const Iterator& it) const { return !(*this == it); }

		T& operator*() const { return get(); }

		Iterator next() const
		{
			if (!valid())
			{
				return *this;
			}
			return Iterator(ptr->nextPtr);
		}

		Iterator operator++(int)
		{
			Iterator saveIt = *this;
			++(*this);
			return saveIt;
		}

		Iterator& operator++()
		{
			if(valid())
			{
				ptr = ptr->nextPtr;
			}
			return *this;
		}

		Iterator& operator+=(unsigned int n)
		{
			for (unsigned int i = 0; i < n; ++i)
			{
				++(*this);
			}
			return *this;
		}
	};

private:
	Node* front;
	Node* back;

private:
	void copyFrom(const LinkedList<T>& other);
	void clear();
	Iterator prev(const Iterator& it);

public:
	LinkedList();
	LinkedList(const LinkedList<T>& other);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	~LinkedList();

	Iterator begin() const;
	Iterator end() const;
	Iterator find(const T& elem) const;
	
	bool empty() const;

	bool insertBefore(const T& newEl, const Iterator& it);
	bool insertAfter(const T& newEl, const Iterator& it);

	void insertBegin(const T& newEl);
	void insertEnd(const T& newEl);

	bool deleteBefore(const Iterator& it, T& elem);
	bool deleteAt(const Iterator& it, T& elem);
	bool deleteAfter(const Iterator& it, T& elem);

	bool deleteBegin(T& elem);
	bool deleteEnd(T& elem);

	const T& getAt(const Iterator& it) const;
	T& getAt(const Iterator& it);

	void append(const LinkedList<T>& list);

	void print() const;
	int size() const;
};

template<typename T>
inline void LinkedList<T>::copyFrom(const LinkedList<T>& other)
{
	for (Iterator it = other.begin(); it; ++it)
	{
		insertAtEnd(*it);
	}
}

template<typename T>
inline void LinkedList<T>::clear()
{
	if (front == nullptr)
	{
		return;
	}
	Node* destroyer;
	while (front != nullptr)
	{
		destroyer = front;
		front = front->nextPtr;
		delete destroyer;
	}
	back = nullptr;
}

template<typename T>
inline typename LinkedList<T>::Iterator LinkedList<T>::prev(const Iterator & it)
{
	if (it == begin())
	{
		return Iterator();
	}
	Iterator prevIt = begin();
	while (prevIt && prevIt.ptr->nextPtr != it.ptr)
	{
		++prevIt;
	}
	return prevIt;
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
inline typename LinkedList<T>::Iterator LinkedList<T>::begin() const
{
	return Iterator(front);
}

template<typename T>
inline typename LinkedList<T>::Iterator LinkedList<T>::end() const
{
	return Iterator();
}

template<typename T>
inline typename LinkedList<T>::Iterator LinkedList<T>::find(const T & elem) const
{
	Iterator prevIt = begin();
	if (!prevIt)
	{
		return Iterator();
	}
	while (*prevIt != elem)
	{
		++prevIt;
	}
	return prevIt;
}

template<typename T>
inline bool LinkedList<T>::empty() const
{
	return !size();
}

template<typename T>
inline bool LinkedList<T>::insertBefore(const T & newEl, const Iterator & it)
{
	if (it == begin())
	{
		Node* toAdd = new Node(newEl, front);
		front = toAdd;
		if (back == nullptr)
		{
			back = toAdd;
		}
		return true;
	}
	return insertAfter(newEl, prev(it));
}

template<typename T>
inline bool LinkedList<T>::insertAfter(const T & newEl, const Iterator & it)
{
	if (!it || it.ptr == back)
	{
		Node* toAdd = new Node(newEl);
		if (front == nullptr)
		{
			front = toAdd;
			back = toAdd;
			return true;
		}
		back->nextPtr = toAdd;
		back = toAdd;
		return true;
	}
	Node* toAdd = new Node(newEl, it.ptr->nextPtr);
	it.ptr->nextPtr = toAdd;
	return true;
}

template<typename T>
inline void LinkedList<T>::insertBegin(const T & newEl)
{
	Node* newElem = new Node(newEl, front);
	if (back == nullptr)
	{
		back = newElem;
	}
	front = newElem;
}

template<typename T>
inline void LinkedList<T>::insertEnd(const T & newEl)
{
	Node* newElem = new Node(newEl);
	if (front == nullptr)
	{
		front = back = newElem;
		return;
	}
	back->nextPtr = newElem;
	back = newElem;
}

template<typename T>
inline bool LinkedList<T>::deleteBefore(const Iterator & it, T & elem)
{
	if (!it || it == begin())
	{
		return false;
	}
	Node* destroyer = prev(it);
	elem = destroyer->data;
	if (destroyer == begin())
	{
		front = front->nextPtr;
	}
	else
	{
		Node* previous = prev(destroyer);
		previous->nextPtr = destroyer->nextPtr;
	}
	delete destroyer;
	return true;
}

template<typename T>
inline bool LinkedList<T>::deleteAt(const Iterator & it, T & elem)
{
	if (!it)
	{
		return false;
	}
	if (it == begin())
	{
		elem = front->data;
		Node* destroyer = it.ptr;
		if (front == back)
		{
			back = nullptr;
		}
		front = front->nextPtr;
		delete destroyer;
		return true;
	}
	return deleteAfter(prev(it), elem);
}

template<typename T>
inline bool LinkedList<T>::deleteAfter(const Iterator & it, T & elem)
{
	if (!it || it.ptr->nextPtr == nullptr)
	{
		return false;
	}
	Node* destroyer = it.ptr->nextPtr;
	elem = destroyer->data;
	if (destroyer == back)
	{
		back = it.ptr;
	}
	it.ptr->nextPtr = destroyer->nextPtr;
	delete destroyer;
	return true;
}

template<typename T>
inline bool LinkedList<T>::deleteBegin(T & elem)
{
	if (front == nullptr)
	{
		return false;
	}
	Node* destroyer = front;
	elem = front->data;
	if (front == back)
	{
		back = nullptr;
		front = nullptr;
		delete destroyer;
		return true;
	}
	front = front->nextPtr;
	delete destroyer;
	return true;
}

template<typename T>
inline bool LinkedList<T>::deleteEnd(T & elem)
{
	if (back == nullptr)
	{
		return false;
	}
	elem = back->data;
	if (front == back)
	{
		delete back;
		front = back = nullptr;
		return true;
	}
	Iterator destroyer = prev(Iterator(back));
	back = destroyer.ptr;
	delete destroyer.ptr->nextPtr;
	back->nextPtr = nullptr;
	return true;
}

template<typename T>
inline const T & LinkedList<T>::getAt(const Iterator & it) const
{
	return it.getConst();
}

template<typename T>
inline T & LinkedList<T>::getAt(const Iterator & it)
{
	return it.get();
}

template<typename T>
inline void LinkedList<T>::append(const LinkedList<T>& list)
{
	Iterator iter(list.front);
	while (iter)
	{
		insertEnd(iter.getConst());
		++iter;
	}
}

template<typename T>
inline void LinkedList<T>::print() const
{
	Iterator iter(front);
	while (iter)
	{
		std::cout << iter.getConst() << " ";
		++iter;
	}
	std::cout << std::endl;
}

template<typename T>
inline int LinkedList<T>::size() const
{
	int count = 0;
	Iterator iter(front);
	while (iter)
	{
		++count;
		++iter;
	}
	return count;
}
