#include<iostream>
#include"ArrayStack.h"
#include"NodeWithPrev.h"
#include"StackADT.h"
#include"DoubleEndedQueue.h"

using namespace std;
int main() {
	DoubleEndedQueue<int> queue;
	int x,y ;
	queue.enqueue(0);
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	queue.enqueue(4);
	queue.enqueue(5);
	queue.enqueue(6);
	queue.dequeue(x);
	queue.dequeue(x);
	queue.dequeue(x);
	queue.dequeue(x);
	queue.dequeue(x);
	queue.dequeue(x);
	queue.dequeue(x);
	
    cout<< queue.dequeue(x);

	 cout << x;
	 queue.peek(x);
	 cout << x;
}