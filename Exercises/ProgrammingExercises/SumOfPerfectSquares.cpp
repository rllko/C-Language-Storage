//SumOfAllPerfect Squares.cpp
/*given a integer 0 <=N<= 1000, determine whether N can be expressed as (a + b + c + d) where a,b,c,d are perfect squares
/ eg.18 is true because 9+9+0+0 or 16+1+1+0
*/

#include <iostream>
#include <map>
#include <vector>
#include <math.h>

int main()
{
	std::vector<int> numList{ 0,0,0,0,0 };
	std::vector<int> perfectSquares;
	
	int chosenNumber,sum = 0;

	std::cin >> chosenNumber;

	for (int i = 0; i <= chosenNumber; i++) { if (sqrt(i) == (int)sqrt(i)) { perfectSquares.push_back(i); } };

	for (auto& num : numList) 
	{
		for (auto& squares : perfectSquares) 
		{
			if (squares + sum <= chosenNumber)
			{
				num = squares;
			}
		}
		sum += num;
		std::cout << num << " + ";
	}
}
