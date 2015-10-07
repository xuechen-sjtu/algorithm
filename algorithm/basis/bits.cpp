/*************************************************************************
    > File Name: bits.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Wed 07 Oct 2015 03:00:22 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

/*
 * n中二进制位1的个数
 */
int num_of_1_1(int n) {
	int count = 0;
	unsigned int flag = 1;
	while (flag) {
		if (n & flag) {
			++count;
		}
		flag <<= 1;
	}
	return count;
}

int num_of_1_2(int n) {
	int count = 0;
	while (n) {
		n = (n - 1) & n;
		++count;
	}
	return count;
}

/*
 * 找出数组中只出现1次的两个数字
 */
unsigned int find_first_bit1(int num) {
	int idx1 = 0;
	while (((num & 1) == 0) && (idx1 < 8 * sizeof(int))) {
		num >>= 1;
		++idx1;
	}
	return idx1;
}

bool is_bit1(int num, unsigned int idx1) {
	num = num >> idx1;
	return (num & 1);
}

void find_nums_appear_once(int A[], int n, int &num1, int &num2) {
	if (A == NULL || n <= 2) {
		return;
	}

	int exclusive_or = 0;
	for (int i = 0; i < n; ++i) {
		exclusive_or ^= A[i];
	}

	unsigned int idx1 = find_first_bit1(exclusive_or);
	
	num1 = num2 = 0;
	for (int i = 0; i < n; ++i) {
		if (is_bit1(A[i], idx1)) {
			num1 ^= A[i];
		} else {
			num2 ^= A[i];
		}
	}
}

int main() {
	cout << "number of 1 in an integer" << endl;
	// cout << num_of_1_1(6) << endl << endl;
	cout << num_of_1_2(6) << endl << endl;

	cout << "find two numbers appear only once in an array" << endl;
	int num1, num2;
	int A[] = {2, 4, 3, 6, 3, 2, 5, 5};
	find_nums_appear_once(A, 8, num1, num2);
	cout << num1 << " " << num2 << endl << endl;

	return 0;
}
