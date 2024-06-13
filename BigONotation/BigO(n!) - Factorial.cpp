//BigO-n!.cpp: Factorial - you can think of it as using recursion with a for loop
/*
 each function call will create 2 functions in this case

			  f(3)
		for each i = 0,1,2
		 /  	|	  \
		 f(2) f(2) f(2) 
		for each i = 0,1
	   /\		/\		   /\
	f(1)f(1) f(1) f(1) f(1) f(1)
		for each i = 0
	   /\		/\		   /\
	f(0)f(0) f(0) f(0) f(0) f(0)

	the string will be logged 13 times, 
		one each function call
*/


#include <iostream>

void f(int n) {
	if (n == 0) {
		std::cout << "=-=-=-= ";
		return;
	}

	for (int i = 0; i < n; i++)
		f(n - 1);

}
int main()
{
	f(3);
}