#pragma once

/**
 * List.
 * Defines Lists.
 * Developed by James P Galovic.
 * Code adapted from code developed for COS30008 - Data Structures and Patterns
 */

#include "DLNodeIter.h"

#include <stdexcept>

template<class T>
class List
{
private:
	DLNode<T>* fTop;
	DLNode<T>* fLast;
	int fCount;

public:
	List();
	~List();

	List(const List<T>& aOther);
	List<T>& operator=(const List<T>& aOther);

	bool isEmpty() const;
	int size() const;

	void push_front(const T& aElement);
	void push_back(const T& aElement);
	void add(const T& aElement);
	void remove(const T& aElement);
	const T& operator[](unsigned int aIndex) const;

	DLNodeIter<T> getIter() const;
};

template<class T>
inline List<T>::List()
{
	fTop = nullptr;
	fLast = nullptr;
	fCount = 0;
}

template<class T>
inline List<T>::~List()
{
	while (fTop != nullptr)
	{
		DLNode<T> lTemp = (DLNode<T>*)&fTop->getNext();
		fTop->remove();
		delete fTop;
		fTop = lTemp;
	}
}

template<class T>
inline List<T>::List(const List<T>& aOther)
{
	fTop = nullptr;
	fLast = nullptr;
	fCount = 0;

	for (DLNodeIter<T> lIter = aOther.getIter().first(); lIter != lIter.right(); lIter++)
		push_back(*lIter);
}

template<class T>
inline List<T>& List<T>::operator=(const List<T>& aOther)
{
	if (&aOther != this)
	{
		while (fTop != nullptr)
		{
			DLNode<T> lTemp = (DLNode<T>*)&fTop->getNext();
			fTop->remove();
			delete fTop;
			fTop = lTemp;
		}

		fTop = nullptr;
		fLast = nullptr;
		fCount = 0;

		for (DLNodeIter<T> lIter = aOther.getIter().first(); lIter != lIter.right(); lIter++)
			push_back(*lIter);
	}
	return *this;
}

template<class T>
inline bool List<T>::isEmpty() const
{
	return fTop == nullptr;
}

template<class T>
inline int List<T>::size() const
{
	return fCount;
}

template<class T>
inline void List<T>::push_front(const T & aElement)
{
	DLNode<T>* lNewElement = new DLNode<T>(aElement);

	if (fTop == nullptr)
	{
		fTop = lNewElement;
		fLast = lNewElement;
	}
	else
	{
		fTop->prepend(*lNewElement);
		fTop = lNewElement;
	}
	fCount++;
}

template<class T>
inline void List<T>::push_back(const T & aElement)
{
	DLNode<T>* lNewElement = new DLNode<T>(aElement);

	if (fTop == nullptr)
	{
		fTop = lNewElement;
		fLast = lNewElement;
	}
	else
	{
		fLast->append(*lNewElement);
		fLast = lNewElement;
	}
	fCount++;
}

template<class T>
inline void List<T>::add(const T & aElement)
{
	push_back(aElement);
}

template<class T>
inline void List<T>::remove(const T & aElement)
{
	DLNode<T> lNode = fTop;

	while (lNode != nullptr)
	{
		if (lNode->getValue() == aElement)
			break;
		lNode = (DLNode<T>*)&lNode->getNext();
	}

	if (lNode != nullptr)
	{
		if (lNode == fTop)
			fTop = (DLNode<T>*)&lNode->getNext();
		if (lNode == fLast)
			fLast = (DLNode<T>*)&lNode->getPrevious();
		
		lNode->remove();
		delete lNode;
		fCount--;
	}
}

template<class T>
inline const T & List<T>::operator[](unsigned int aIndex) const
{
	if (aIndex < fCount)
	{
		DLNode<T>* lNode = fTop;
		while (aIndex)
		{
			aIndex--;
			lNode = (DLNode<T>*)&lNode->getNext();
		}
		return lNode->getValue;
	}
}

template<class T>
inline DLNodeIter<T> List<T>::getIter() const
{
	return new DLNodeIter<T>(*fTop);
}
