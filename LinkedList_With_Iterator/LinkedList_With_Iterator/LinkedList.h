#pragma once

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
	if (front == back == nullptr)
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

	
}

template<typename T>
inline bool LinkedList<T>::insertAfter(const T & newEl, const Iterator & it)
{
	return false;
}

template<typename T>
inline void LinkedList<T>::insertBegin(const T & newEl)
{
}

template<typename T>
inline void LinkedList<T>::insertEnd(const T & newEl)
{
}

template<typename T>
inline bool LinkedList<T>::deleteBefore(const Iterator & it, T & elem)
{
	return false;
}

template<typename T>
inline bool LinkedList<T>::deleteAt(const Iterator & it, T & elem)
{
	return false;
}

template<typename T>
inline bool LinkedList<T>::deleteAfter(const Iterator & it, T & elem)
{
	return false;
}

template<typename T>
inline bool LinkedList<T>::deleteBegin(T & elem)
{
	return false;
}

template<typename T>
inline bool LinkedList<T>::deleteEnd(T & elem)
{
	return false;
}

template<typename T>
inline const T & LinkedList<T>::getAt(const Iterator & it) const
{
	// TODO: insert return statement here
}

template<typename T>
inline T & LinkedList<T>::getAt(const Iterator & it)
{
	// TODO: insert return statement here
}

template<typename T>
inline void LinkedList<T>::append(const LinkedList<T>& list)
{
}

template<typename T>
inline void LinkedList<T>::print() const
{
}

template<typename T>
inline int LinkedList<T>::size() const
{
	return 0;
}
