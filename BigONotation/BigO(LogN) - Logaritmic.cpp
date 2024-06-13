//BigOLogN.cpp: This is a constant so it can run forever without any time penalty
//this is a O(log n) function, for every input size "n"
//it takes 1 , 2 , 4, 8, 16, 32 ms to compute, you can see it because it multiplying by 2/ O(log_2(n))

#include <iostream>

void LogN(int n) {

	for (int i = 0; i < n; i * 2) {
		std::cout << "this is a logN function!\n";
	}

}

int main()
{

}