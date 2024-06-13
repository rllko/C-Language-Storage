// Exercises.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
/*
Given a square matrix, calculate the absolute difference between the sums of its diagonals.

For example, the square matrix  is shown below:

1 2 3
4 5 6
9 8 9
The left-to-right diagonal - 1 + 5 + 9 = 15. The right to left diagonal - 3+5+9 = 17. Their absolute difference is |17 - 15| = 2.


*/

#include <iostream>
#include <vector>

int main()
{
	using namespace std;

	vector<vector<int, int>>arr = {{11,2,4,
									4,5,6,
									10,8,2}};

    int coluna = arr.size(),
        linha = arr.at(0).size(),
        soma = 0,
        soma2 = 0;

    for (int i = 0; i < coluna;i++) {
        for (int j = 0; j < linha; j++) {
            if (i == j)
                soma += arr[i][j];

            if (i + j == coluna - 1)
                soma2 += arr[i][j];
        }
    }

}