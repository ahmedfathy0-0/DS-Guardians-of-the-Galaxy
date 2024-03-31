#pragma once
#include "DoubleQueue.h"
//#include"NodeWithPrev.h"

template <typename T>
class DoubleEndedQueue :public DoubleQueue<T> {
public:
	DoubleEndedQueue();
	bool DoubleDequeue( T& frsEntry,  T& lstEntry);

};

template<typename T>
inline DoubleEndedQueue<T>::DoubleEndedQueue() : DoubleQueue<T>()
{
}

template<typename T>
inline bool DoubleEndedQueue<T>::DoubleDequeue( T& frsEntry,  T& lstEntry)
{
	if (this->isEmpty())
		return false;

	NodeWithPrev<T>* frsnodeToDeletePtr = this->frontPtr;
	NodeWithPrev<T>* lstnodeToDeletePtr = this->backPtr;
	if (frsnodeToDeletePtr != lstnodeToDeletePtr) {
		frsEntry = this->frontPtr->getItem();
		lstEntry = this->backPtr->getItem();
		if (this->frontPtr->getNext() == this->backPtr) {
			this->frontPtr = nullptr;
			this->backPtr = nullptr;
		}
		else {
			this->frontPtr = this->frontPtr->getNext();
			this->frontPtr->setPrevious(nullptr);
			this->backPtr = this->backPtr->getPrevious();
			this->backPtr->setNext(nullptr);
		}
		delete frsnodeToDeletePtr;
		delete lstnodeToDeletePtr;
		this->count -= 2;
	}
	// Queue is not empty; remove front
	else {	 // Special case: last node in the queue
		this->backPtr = nullptr;
		this->frontPtr = nullptr;
		delete frsnodeToDeletePtr;
		this->count -= 1;
	}
	// Free memory reserved for the dequeued node
	
	return true;
}
