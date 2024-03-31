#pragma once


template <typename T>
class NodeWithPrev
{
private:
    T item; // A data item
    NodeWithPrev<T>* next; // Pointer to next node
    NodeWithPrev <T>* previous;// Pointer to previous node
public:
    NodeWithPrev();
    NodeWithPrev(const T& r_Item);
    NodeWithPrev(const T& r_Item, NodeWithPrev<T>* nextNodePtr, NodeWithPrev<T>* previousNodePtr);
    void setItem(const T& r_Item);
    void setNext(NodeWithPrev<T>* nextNodePtr);
    T getItem() const;
    NodeWithPrev<T>* getNext() const;
    void setPrevious(NodeWithPrev<T>* previousNodePtr);
    NodeWithPrev<T>* getPrevioss() const;
}; // end Node


template <typename T>
NodeWithPrev<T>::NodeWithPrev()
{
    next = nullptr;
    previous = nullptr;
}

template < typename T>
NodeWithPrev<T>::NodeWithPrev(const T& r_Item)
{
    item = r_Item;
    next = nullptr;
    previous = nullptr;
}

template < typename T>
NodeWithPrev<T>::NodeWithPrev(const T& r_Item, NodeWithPrev<T>* nextNodePtr, NodeWithPrev<T>* previousNodePtr)
{
    item = r_Item;
    next = nextNodePtr;
    previous = previousNodePtr;
}

template < typename T>
void NodeWithPrev<T>::setItem(const T& r_Item)
{
    item = r_Item;
}

template < typename T>
void NodeWithPrev<T>::setNext(NodeWithPrev<T>* nextNodePtr)
{
    next = nextNodePtr;
}

template < typename T>
T NodeWithPrev<T>::getItem() const
{
    return item;
}

template < typename T>
NodeWithPrev<T>* NodeWithPrev<T>::getNext() const
{
    return next;
}

template < typename T>
void NodeWithPrev<T>::setPrevious(NodeWithPrev<T>* previousNodePtr)
{
    previous = previousNodePtr;
}

template < typename T>
NodeWithPrev<T>* NodeWithPrev<T>::getPrevioss() const
{
    return previous;
}