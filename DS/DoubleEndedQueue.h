#pragma once
#include "DoubleQueue.h"
//#include"NodeWithPrev.h"

template <typename T>
class DoubleEndedQueue :public DoubleQueue<T> {
public:
	DoubleEndedQueue();
	bool RearDequeue( T& lstEntry);
	bool FrontEnqueue(const T& lstEntry);

};

template<typename T>
inline DoubleEndedQueue<T>::DoubleEndedQueue() : DoubleQueue<T>()
{
}

template<typename T>
inline bool DoubleEndedQueue<T>::RearDequeue(T& lstEntry)
{
	if (this->isEmpty()) {
		lstEntry = nullptr;
		return false;
	}
		

	NodeWithPrev<T>* lstnodeToDeletePtr = this->backPtr;
		lstEntry = this->backPtr->getItem();
		this->backPtr = this->backPtr->getPrevious();
		
	
	
	//Queue is not empty; remove front

	if (lstnodeToDeletePtr == this->frontPtr)	 // Special case: last node in the queue
	{
		this->frontPtr = nullptr;

	}
	else
		this->backPtr->setNext(nullptr);


	// Free memory reserved for the dequeued node
	delete lstnodeToDeletePtr;
	lstnodeToDeletePtr = nullptr;
	this->count--;
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::FrontEnqueue(const T& lstEntry)
{
	NodeWithPrev<T>* newNodePtr = new NodeWithPrev<T>(lstEntry);
	// Insert the new node
	if (this->isEmpty())//special case if this is the first node to insert
	{
		this->backPtr = newNodePtr;
	}
	else {
		newNodePtr->setNext(this->frontPtr);
		this->frontPtr->setPrevious(newNodePtr);
		 // The queue was not empty
	}
	this->frontPtr = newNodePtr; // New node is the first node now
	this->count++;
	return true;
	
}


