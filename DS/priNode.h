#pragma once
template < typename T>
class priNode
{
private:
	T item;		// A data item
	double pri;	//priority of the item
	priNode<T>* next; // Pointer to next node
public:
	priNode(const T& r_Item, double PRI)
	{
		setItem(r_Item, PRI);
		next = nullptr;
	}
	void setItem(const T& r_Item, double PRI)
	{
		item = r_Item;
		pri = PRI;
	}
	void setNext(priNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getItem(double& PRI) const
	{
		PRI = pri;
		return item;
	}

	priNode<T>* getNext() const
	{
		return next;
	}

	int getPri() const
	{
		return pri;
	}
}; // end Node


