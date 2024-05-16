#pragma once
using namespace std;
/*That Class is created just for Make our code more organized*/

template<typename T>
class Array {
	enum { MAX_SIZE = 1000 };
private:
	T items[MAX_SIZE];		// Array of  items  // ex: array of monster pointers
	int top;                   // Index to top of stack
	int count;					// Number of items in the The Array
public:
	Array()
	{
		top = -1;
		count = 0;
	}  // end default constructor
	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty
	bool AddElement(const T& newEntry)
	{
		if (top == MAX_SIZE - 1) return false;	//Array is FULL

		top++;
		items[top] = newEntry;
		count++;
		return true;
	}  // end AddElement
	bool Remove(T& TopEntry)
	{

		int index = rand() % (count);

		if (isEmpty()) return false;
		for (int i = 0;i < count;i++) {
			if (i == index) {
				TopEntry = items[i];
				items[i] = items[top];
			}
		}
		top--;
		count--;
		return true;
	}  // end Remove
	int getCount() const{
		return count;
	}
	void print() {
		
		cout << "[ ";
		for (int i = 0;i < count;i++) {
			cout << items[i];
			if (i != count - 1) {
				cout << " ," ;
			}
		}


		cout << " ]";
		cout << endl;
	}
};