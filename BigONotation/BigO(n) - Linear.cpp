//BigOLinear.cpp: this is the most common and simple one - O(n),prints hello n times
// O(n)
#include <iostream>

void LinearFunc(int n) {
	for (int i = 0; i < n; i++) { 
		std::cout << "Hello!\n"; 
	}
}

int main()
{

	LinearFunc(5);

}