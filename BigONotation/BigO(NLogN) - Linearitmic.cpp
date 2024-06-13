//BigO-NLogN.cpp: This is a constant so it can run forever without any time penalty
//you should always think as being O(n) mixed with O(log n), becoming O(n log n)
#include <iostream>

void NLogN(int n) {
	for (int i = 0; i < n; i++) { 
		for(int j = 0; j < n; j * 2){
		// O(1) but its ignored since we want the worst case scenario
		std::cout << "Hello!\n"; 
		}
	}
}

int main()
{

	NLogN(2);

}