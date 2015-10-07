/*************************************************************************
    > File Name: search.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Tue 06 Oct 2015 03:22:35 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

/*
 * 顺序查找
 */
bool search(int A[], int n, int x) {
	if (A == NULL || n <= 0) {
		return false;
	}

	for (int i = 0; i < n; ++i) {
		if (A[i] == x) {
			return true;
		}
	}

	return false;
}

/*
 * 二分查找
 */
bool binary_search(int A[], int n, int x) {
	if (A == NULL || n <= 0) {
		return false;
	}

	int low = 0, high = n - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (A[mid] == x) {
			return true;
		} else if (A[mid] > x) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
}

/*
 * 一个矩阵从左到右、从上到下递增，
 * 判断一个数是否存在于该矩阵中
 */
bool find_k(int *matrix, int columns, int rows, int x) {
	if (matrix == NULL || columns <= 0 || rows <= 0) {
		return false;
	}

	int row = 0, column = columns - 1;
	while (row < rows && column >= 0) {
		if (matrix[column + row * columns] == x) {
			return true;
		} else if (matrix[column + row * columns] > x) {
			--column;
		} else {
			++row;
		}
	}
	return false;
}

/*
 * 旋转数组中的最小值
 */
int min_in_order(int A[], int low, int high) {
	int ret = A[low];
	for (int i = low + 1; i <= high; ++i) {
		if (A[i] < ret) {
			ret = A[i];
		}
	}
	return ret;
}

int min(int A[], int n) {
	if (A == NULL || n <= 0) {
		cout << "invalid parameters" << endl;
		return -1;
	}

	int low = 0, high = n - 1;
	int mid = low;
	while (A[low] >= A[high]) {
		if (high - low == 1) {
			mid = high;
			break;
		}

		mid = (low + high) / 2;
		if (A[low] == A[mid] 
				&& A[mid] == A[high]) {
			return min_in_order(A, low, high);
		}

		if (A[mid] >= A[low]) {
			low = mid;
		} else if (A[mid] <= A[high]) {
			high = mid;
		}
	}
	return A[mid];
}

/*
 * 数组中重复的数字
 */
bool dup1(int A[], int n, int &dup) {
	bool has_dup = false;
	if (A == NULL || n <= 0) {
		return has_dup;
	}

	for (int i = 0; i < n; ++i) {
		if (A[i] < 0 || A[i] > n - 1) {
			return has_dup;
		}
	}

	for (int i = 0; i < n; ++i) {
		while (A[i] != i) {
			if (A[i] == A[A[i]]) {
				dup = A[i];
				has_dup = true;
				return has_dup;
			} else {
				int tmp = A[i];
				A[i] = A[tmp];
				A[tmp] = tmp;
			}
		}
	}
	return has_dup;
}

bool dup2(int A[], int n, int &dup) {
	if (A == NULL || n <= 0) {
		return false;
	}

	for (int i = 0; i < n; ++i) {
		if (A[i] < 0 || A[i] > n - 1) {
			return false;
		}
	}

	map<int, int> M;
	for (int i = 0; i < n; ++i) {
		if (M.count(A[i]) == 1) {
			dup = A[i];
			return true;
		} else {
			M[A[i]] = 1;
		}
	}

	return false;
}

int main() {
	int A[] = {
		1, 2, 8, 9,
		2, 4, 9, 12,
		4, 7, 10, 13,
		6, 8, 11, 15
	};

	sort(A, A + 16);
	cout << "find x in a sorted array" <<endl;
	if (true == binary_search(A, 16, 7)) {
		cout << "yes" << endl << endl;
	} else {
		cout << "no" << endl << endl;
	}

	cout << "find x in an array" << endl;
	if (true == search(A, 16, 7)) {
		cout << "yes" << endl << endl;
	} else {
		cout << "no" << endl << endl;
	}
			
	cout << "find x in a special matrix" << endl;
	if (true == find_k(A, 4, 4, 7)) {
		cout << "yes" << endl << endl;
	} else {
		cout << "no" << endl << endl;
	}

	int B[] = {1, 1, 0, 1, 1};
	// int B[] = {4, 5, 1, 2, 3};
	cout << "find minimum in a rotated array" << endl;
	cout << min(B, 5) << endl << endl;

	int dup = -1;
	// if (true == dup1(B, 5, dup)) {
	if (true == dup2(B, 5, dup)) {
		cout << "duplication: " << dup << endl << endl;
	} else {
		cout << "no duplication" << endl << endl;
	}

	return 0;
}
