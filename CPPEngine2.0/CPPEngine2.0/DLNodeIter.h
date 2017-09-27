#pragma once

/**
 * Doubly Linked Node Iterator
 * Defines Doubley Linked Node Iterators to be used in Lists.
 * Developed by James P Galovic.
 * Code adapted from code developed for COS30008 - Data Structures and Patterns
 */

#include "DLNode.h"

template<class T>
class DLNodeIter
{
private:
	enum IterStates {BEFORE, DATA, AFTER};

	IterStates fState;

	const DLNode<T>* fLeft;
	const DLNode<T>* fRight;
	const DLNode<T>* fCurrent;

public:
	DLNodeIter(const DLNode<T>& aList);

	const T& operator*() const;
	DLNodeIter<T>& operator++();
	DLNodeIter<T> operator++(int);
	DLNodeIter<T>& operator--();
	DLNodeIter<T> operator--(int);

	bool operator==(const DLNodeIter<T>& aOther) const;
	bool operator!=(const DLNodeIter<T>& aOther) const;

	DLNodeIter<T> left() const;
	DLNodeIter<T> first() const;
	DLNodeIter<T> last() const;
	DLNodeIter<T> right() const;
};

template<class T>
inline DLNodeIter<T>::DLNodeIter(const DLNode<T>& aList)
{
	// Set Left
	fLeft = &aList;
	while (&fLeft->getPrevious() != nullptr)
		fLeft = &fLeft->getPrevious();

	// Set Right
	fRight = &aList;
	while (&fRight->getNext() != nullprt)
		fRight = &fRight->getNext();

	// Set Current
	fCurrent = fLeft;

	// Set State
	if (fCurrent == nullptr)
		fState = AFTER;
	else
		fState = DATA;
}

template<class T>
inline const T & DLNodeIter<T>::operator*() const
{
	return fCurrent->getValue();
}

template<class T>
inline DLNodeIter<T> & DLNodeIter<T>::operator++()
{
	switch (fState)
	{
	case BEFORE:
		fCurrent = fLeft;
		if (fCurrent == nullptr)
			fState = AFTER;
		else
			fState = DATA;
	case DATA:
		fCurrent = &fCurrent->getNext();
		if (fCurrent == nullptr)
			fState = AFTER;
		break;
	default:
		break;
	}
	return *this;
}

template<class T>
inline DLNodeIter<T> DLNodeIter<T>::operator++(int)
{
	DLNodeIter<T> lTemp = *this;
	++(*this);
	return lTemp;
}

template<class T>
inline DLNodeIter<T> & DLNodeIter<T>::operator--()
{
	switch (fState)
	{
	case AFTER:
		fCurrent = fRight;
		if (fCurrent == nullptr)
			fState = BEFORE;
		else
			fState = DATA;
		break;
	case DATA:
		fCurrent = &fCurrent->getPrevious();
		if (fCurrent == nullptr)
			fState = BEFORE;
		break;
	default:
		break;
	}
	return *this;
}

template<class T>
inline DLNodeIter<T> DLNodeIter<T>::operator--(int)
{
	DLNodeIter<T> lTemp = *this;
	--(*this);
	return lTemp;
}

template<class T>
inline bool DLNodeIter<T>::operator==(const DLNodeIter<T> & aOther) const
{
	return fLeft == aOther.fLeft && fRight == aOther.fRight && fCurrent == aOther.fCurrent && fState == aOther.fState;
}

template<class T>
inline bool DLNodeIter<T>::operator!=(const DLNodeIter<T> & aOther) const
{
	return !(this == aOther);
}

template<class T>
inline DLNodeIter<T> DLNodeIter<T>::left() const
{
	DLNodeIter<T> lTemp = *this;

	lTemp.fCurrent = nullptr;
	lTemp.fState = BEFORE;

	return lTemp;
}

template<class T>
inline DLNodeIter<T> DLNodeIter<T>::first() const
{
	return ++(left());
}

template<class T>
inline DLNodeIter<T> DLNodeIter<T>::last() const
{
	return --(right());
}

template<class T>
inline DLNodeIter<T> DLNodeIter<T>::right() const
{
	DLNodeIter<T> lTemp = *this;

	lTemp.fCurrent = nullptr;
	lTemp.fState = AFTER;

	return lTemp;
}
