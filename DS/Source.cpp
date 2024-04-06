#include<iostream>
#include"ArrayStack.h"
#include"NodeWithPrev.h"
#include"StackADT.h"
#include"DoubleEndedQueue.h"
#include "Unit.h"
std::ostream& operator<<(std::ostream& os, const Unit*& item) {
	os << item->getID();  // Print the value of the item
	return os;
}
using namespace std;
int main() {
	DoubleEndedQueue<int> queue;
	int x,y ;
	queue.FrontEnqueue(0);
	queue.FrontEnqueue(1);
	queue.FrontEnqueue(2);
	queue.FrontEnqueue(3);
	queue.FrontEnqueue(4);
	queue.FrontEnqueue(5);
	queue.FrontEnqueue(6);
	/* queue.RearDequeue(x);
	cout << x << " ";
	queue.RearDequeue(x);
	cout << x << " ";
	queue.RearDequeue(x);
	cout << x << " ";
	queue.RearDequeue(x);
	cout << x << " ";
	queue.RearDequeue(x);
	cout << x << " ";
	queue.RearDequeue(x);
	cout << x << " ";
	queue.RearDequeue(x);
	cout << x << " ";
	
	*/

	queue.print();
	
}