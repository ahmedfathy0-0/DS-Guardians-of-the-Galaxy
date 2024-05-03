#pragma once



#include "NodeWithPrev.h"
#include "QueueADT.h"

using namespace std;

template <typename T>
class DoubleQueue :public QueueADT<T>
{
public:
	int count;
	NodeWithPrev<T>* backPtr;
	NodeWithPrev<T>* frontPtr;
public:
	DoubleQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	int getCount() const { return count; }
	void print() const;
	~DoubleQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
DoubleQueue<T>::DoubleQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
	

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool DoubleQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool DoubleQueue<T>::enqueue(const T& newEntry)
{
	NodeWithPrev<T>* newNodePtr = new NodeWithPrev<T>(newEntry);
	// Insert the new node
	if (isEmpty())//special case if this is the first node to insert
	{
		frontPtr = newNodePtr; // The queue is empty

	}
	else {
		newNodePtr->setPrevious(backPtr);
		backPtr->setNext(newNodePtr); // The queue was not empty
	}
	backPtr = newNodePtr; // New node is the last node now
	count++;
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool DoubleQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	NodeWithPrev<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
	{
		backPtr = nullptr;
	
	}
	else 
		frontPtr->setPrevious(nullptr);


	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	nodeToDeletePtr = nullptr;
	count--;
	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template <typename T>
bool DoubleQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;
	
	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void DoubleQueue<T>::print() const
{
	NodeWithPrev<T>* p = frontPtr;

	cout << "[ ";
	while (p)
	{
		cout << p->getItem();
		p = p->getNext();

		if (p) {
			cout << " ,";
		}

	}
	cout << " ]";
	cout << endl;
}

template <typename T>
DoubleQueue<T>::~DoubleQueue()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor
	cout << "\nStarting LinkedQueue destructor...";
	cout << "\nFreeing all nodes in the queue...";

	//Free all nodes in the queue
	T temp;
	while (dequeue(temp));
	
	cout << "\n Is LinkedQueue Empty now?? ==> " << boolalpha << isEmpty();
	cout << "\nEnding LinkedQueue destructor..." << endl;
}


