//BigO-n3.cpp: this is like the O(n2) but actually is just three nested loops

#include <iostream>

void n3(int n) {
for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j + 2)
		for (int k = 0; k < n; k + 3)
				std::cout << "Hello!\n";
}
int main()
{

	n3(3);

}