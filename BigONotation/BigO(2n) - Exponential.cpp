//BigO-2n.cpp: Exponential - this is a normal recursion, a recursion is a function calling a function
//As a normal example i used the fibonnaci numbers.

#include <iostream>

int fib(int n) {
	if (n == 1)
		return 1;

	if (n == 0)
		return 0;

	return fib(n - 1) + fib(n - 2);

}
int main()
{

	std::cout << fib(5) << " ";

}