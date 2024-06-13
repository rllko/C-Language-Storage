/*

Staircase detail

This is a staircase of size :

   #
  ##
 ###
####
Its base and height are both equal to n . It is drawn using # symbols and spaces. The last line is not preceded by any spaces.

Write a program that prints a staircase of size n .

*/

#include <iostream>

void staircase(int n) {
		int charNum = 1;
		for (int spacesNum = n-1; spacesNum >= 0; spacesNum--)
		{
			std::cout << std::string(spacesNum, ' ') << std::string(charNum, '#') << '\n';
			charNum++;
		}
}

int main()
{
	staircase(6);
}
