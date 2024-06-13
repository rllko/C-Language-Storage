/*

Given five positive integers, find the minimum and maximum values that can be calculated by summing exactly four of the five integers. 
Then print the respective minimum and maximum values as a single line of two space-separated long integers.

Example
arr = [1,3,5,7,9]

The minimum sum is 1+3+5+7 = 16 and the maximum sum is 3+5+7+9 = 24 . The function prints 16 24

*/

#include <iostream>
#include <algorithm>
#include <vector>

void miniMaxSum(std::vector<int> arr) {
    std::sort(arr.begin(), arr.end());
    int64_t min = 0, max = 0;

    for (int i = 0; i <= arr.size(); i++) {
        if (i != 0) min += i;
        if (i != 4) max += i;
    }

    std::cout << min << " " << max;

}

int main()
{
	miniMaxSum({ 1,2,3,4,5 });
}