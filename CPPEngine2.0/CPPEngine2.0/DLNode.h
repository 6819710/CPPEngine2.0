#pragma once

/**
 * Doubly Linked Node.
 * Defines Doubley Linked Nodes to be used in Lists.
 * Developed by James P Galovic.
 * Code adapted from code developed for COS30008 - Data Structures and Patterns
 */

template<class T>
class DLNode
{
private:
	T fValue;
	DLNode<T>* fNext;
	DLNode<T>* fPrevious;

	DLNode();

public:
	DLNode(const T& aValue);

	void prepend(DLNode<T>& aNode);
	void append(DLNode<T>& aNode);
	void remove();

	const T& getValue() const;
	const DLNode<T>& getNext() const;
	const DLNode<T>& getPrevious() const;
};

template<class T>
DLNode<T>::DLNode()
{
	fValue = T();
	fNext = nullptr;
	fPrevious = nullptr;
}

template<class T>
DLNode<T>::DLNode(const T & aValue)
{
	fValue = aValue;
	fPrevious = nullptr;
	fNext = nullptr;
}

template<class T>
void DLNode<T>::prepend(DLNode<T>& aNode)
{
	aNode.fNext = this;
	if (fPrevious != nullptr) // insert at previous if previous exsists.
	{
		aNode.fPrevious = fPrevious;
		fPrevious->fNext = &aNode;
	}
	fPrevious = &aNode;
}

template<class T>
void DLNode<T>::append(DLNode<T>& aNode)
{
	aNode.fPrevious = this;
	if (fNext != nullptr) // insert at next if next exsists.
	{
		aNode.fNext = fNext;
		fPrevious->fPrevious = &aNode;
	}
	fNext = &aNode;
}

template<class T>
void DLNode<T>::remove()
{
	if (fPrevious != nullptr)
		fPrevious->fNext = fNext;
	if (fNext != nullptr)
		fNext->fPrevious = fPrevious;
}

template<class T>
const T & DLNode<T>::getValue() const
{
	return fValue;
}

template<class T>
const DLNode<T>& DLNode<T>::getNext() const
{
	return *fNext;
}

template<class T>
const DLNode<T>& DLNode<T>::getPrevious() const
{
	return *fPrevious;
}
