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
	queue.DoubleDequeue(x,y);
	 
	 cout << x << y;
	 queue.peek(x);
	 cout << x;
}