#include <iostream>
#include <string>
#include <cstdlib>
//greatest common divisor

long long GCD(long a,long b) {
	if(b==0) return a;
	
	int r = a % b;
	return GCD(a,r);
}

int main()
{
std::cout << GCD(rand() % 10000 + 1000,rand()%10000 +1000)
}


