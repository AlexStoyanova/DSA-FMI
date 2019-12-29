#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class BSTree
{
private:
	
	struct Node
	{
		T data;
		Node* leftTree;
		Node* rightTree;

		Node(const T& d = {}) : data(d), leftTree(nullptr), rightTree(nullptr) {}
	};

private:

	Node* root;

private:

	void copyFrom(const BSTree<T>& other);
	void copyHelper(Node*& ours, Node* theirs);
	void deleteTree(Node*& start);
	void add(Node* start, const T& newElem);
	void remove(Node* start, const T& elem);
	BSTree<T> findAndTake(Node* start, const T& elem);
	unsigned int getHeightHelper(Node* start) const;

public:
	BSTree();
	BSTree(const BSTree& other);
	BSTree<T>& operator=(const BSTree& rhs);
	~BSTree();

	void addElement(const T& newElem);
	void removeElement(const T& elem);
	BSTree<T> findElemAndTakeSubtree(const T& elem);
	unsigned int getHeight() const;
};

template<typename T>
void BSTree<T>::copyFrom(const BSTree & other)
{
	copyHelper(root, other.root);
}

template<typename T>
void BSTree<T>::copyHelper(typename BSTree<T>::Node *& ours, 
	                       typename BSTree<T>::Node * theirs)
{
	if (theirs == nullptr)
	{
		ours = nullptr;
		return;
	}
	ours = new Node(theirs->data);
	copyHelper(ours->leftTree, theirs->leftTree);
	copyHelper(theirs->rightTree, theirs->rightTree);
}

template<typename T>
void BSTree<T>::deleteTree(typename BSTree<T>::Node *& start)
{
	if (start != nullptr)
	{
		deleteTree(start->leftTree);
		deleteTree(start->rightTree);
		delete start;
	}
}

template<typename T>
void BSTree<T>::add(typename BSTree<T>::Node * start, const T & newElem)
{
	if (start == nullptr)
	{
		start = new Node(newElem);
		return;
	}
	if (newElem == start->data)
	{
		throw std::logic_error("This element already exists!!!\n");
	}
	if (newElem < start->data)
	{
		add(start->leftTree, newElem);
		return;
	}
	if (newElem > start->data)
	{
		add(start->rightTree, newElem);
		return;
	}
}

template<typename T>
void BSTree<T>::remove(typename BSTree<T>::Node * start, const T & elem)
{
	if (start == nullptr)
	{
		throw std::logic_error("This element does not exist!!!\n");
	}
	if (elem < start->data)
	{
		remove(start->leftTree, elem);
		return;
	}
	if (elem > start->data)
	{
		remove(start->rightTree, elem);
		return;
	}

	if (!start->leftTree && !start->rightTree)
	{
		delete start;
		start = nullptr;
		return;
	}

	if (start->leftTree != nullptr && start->rightTree != nullptr)
	{
		Node* temp = start->leftTree;
		while (temp->rightTree != nullptr)
		{
			temp = temp->rightTree;
		}
		start->data = temp->data;
		remove(start->leftTree, start->data);
	}
	else
	{
		Node* temp = start;
		if (start->leftTree)
		{
			start = start->leftTree;
		} 
		else
		{
			start = start->rightTree;
		}
		delete temp;
	}
}

template<typename T>
BSTree<T> BSTree<T>::findAndTake(typename BSTree<T>::Node * start, const T & elem)
{
	if (start == nullptr)
	{
		throw std::logic_error("This element does not exist!!!\n");
	}
	if (elem < start->data)
	{
		return findAndTake(start->leftTree, elem);
	}
	if (elem > start->data)
	{
		return findAndTake(start->rightTree, elem);
	}

	BSTree<T> newTree;
	copyHelper(newTree.root, start);
	return newTree;
}

template<typename T>
inline unsigned int BSTree<T>::getHeightHelper(Node * start) const
{
	if (start == nullptr)
	{
		return 0;
	}
	return 1 + std::max(getHeightHelper(start->leftTree), getHeightHelper(start->rightTree));
}

template<typename T>
BSTree<T>::BSTree() : root(nullptr)
{}

template<typename T>
BSTree<T>::BSTree(const BSTree & other)
{
	root = nullptr;
	copyFrom(other);
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree & rhs)
{
	if (this != &rhs)
	{
		deleteTree(root);
		root = nullptr;
		copyFrom(rhs);
	}
	return *this;
}

template<typename T>
BSTree<T>::~BSTree()
{
	deleteTree(root);
}

template<typename T>
void BSTree<T>::addElement(const T & newElem)
{
	add(root, newElem);
}

template<typename T>
void BSTree<T>::removeElement(const T & elem)
{
	remove(root, elem);
}

template<typename T>
BSTree<T> BSTree<T>::findElemAndTakeSubtree(const T & elem)
{
	return findAndTake(root, elem);
}

template<typename T>
unsigned int BSTree<T>::getHeight() const
{
	return getHeightHelper(root);
}
