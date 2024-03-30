#include<iostream>
#include"ArrayStack.h"
#include"Node.h"
#include"StackADT.h"

using namespace std;
int main() {
	ArrayStack<int> S;
	S.push(2);
	int x;
	S.pop(x);
	//S.isEmpty();
	cout << x;



}