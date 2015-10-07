/*************************************************************************
    > File Name: array.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Tue 06 Oct 2015 03:14:34 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

/*
 * 斐波那契数列
 */
int fibonacci(int n) {
	if (n == 0 || n == 1) {
		return n;
	}

	int a = 0, b = 1;
	for (int i = 2; i <= n; ++i) {
		int tmp = a + b;
		a = b;
		b = tmp;
	}
	return b;
}

/*
 * 调整数组，将奇数放在所有偶数的前面
 */
void reorder_odd_even(int A[], int n) {
	if (A == NULL || n <= 0) {
		return;
	}

	int low = 0, high = n - 1;
	while (low < high) {
		while (low < high && (A[low] & 0x1) == 1) {
			++low;
		}
		while (low < high && (A[high] & 0x1) == 0) {
			--high;
		}
		if (low < high) {
			int tmp = A[low];
			A[low] = A[high];
			A[high] = tmp;
		}
	}
}

/*
 * 顺时针打印矩阵
 */
void print_matrix_in_circle(int A[][4], int columns, int rows, int start) {
	int endX = columns - 1 - start;
	int endY = rows - 1 - start;

	for (int i = start; i <= endX; ++i) {
		cout << A[start][i] << ' ';
	}

	if (start < endY) {
		for (int i = start + 1; i <= endY; ++i) {
			cout << A[i][endX] << ' ';
		}
	}

	if (start < endX && start < endY) {
		for (int i = endX - 1; i >= start; --i) {
			cout << A[endY][i] << ' ';
		}
	}

	if (start <= endX && start < endY - 1) {
		for (int i = endY - 1; i >= start + 1; --i) {
			cout << A[i][start] << ' ';
		}
	}
}

void print_matrix_clock_wisely(int A[][4], int columns, int rows) {
	if (A == NULL || columns <= 0 || rows <= 0) {
		return;
	}
	int start = 0;
	while (columns > start * 2 && rows > start * 2) {
		print_matrix_in_circle(A, columns, rows, start);
		++start;
	}
}

/*
 * 数组中超过一半的数字
 */
int partition(int A[], int low, int high) {
	int pivot = A[low];
	while (low < high) {
		while (low < high && A[high] >= pivot) {
			--high;
		}
		A[low] = A[high];
		while (low < high && A[low] <= pivot) {
			++low;
		}
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}

bool check_more_than_half(int A[], int n, int result) {
	int time = 0, half = n / 2;
	for (int i = 0; i < n; ++i) {
		if (A[i] == result) {
			++ time;
			if (time > half) {
				return true;
			}
		}
	}
	return false;
}

int more_than_half_num1(int A[], int n) {
	if (A == NULL || n <= 0) {
		return -1;
	}

	int low = 0, high = n - 1, mid = (low + high) / 2;
	int pivotpos = partition(A, low, high);
	while (pivotpos != mid) {
		if (pivotpos > mid) {
			high = pivotpos - 1;
			pivotpos = partition(A, low, high);
		} else {
			low = pivotpos + 1;
			pivotpos = partition(A, low, high);
		}
	}

	int result = A[mid];
	if (!check_more_than_half(A, n, result)) {
		result = -1;
	}
	return result;
}

int more_than_half_num2(int A[], int n) {
	if (A == NULL || n <= 0) {
		return 0;
	}
	
	int result = A[0];
	int time = 1;
	for (int i = 1; i < n; ++i) {
		if (time == 0) {
			result = A[i];
			time = 1;
		} else if (A[i] == result) {
			++time;
		} else {
			--time;
		}
	}
	if (!check_more_than_half(A, n, result)) {
		result = -1;
	}
	return result;
}

/*
 * 最小的k个数
 */
void get_least_k_num(int A[], int n, int output[], int k) {
	if (A == NULL || k <= 0
			|| output == NULL || k <= 0 || k > n) {
		return;
	}

	int low = 0, high = n - 1;
	int pivotpos = partition(A, low, high);
	while (pivotpos != k - 1) {
		if (pivotpos > k - 1) {
			high = pivotpos - 1;
			pivotpos = partition(A, low, high);
		} else {
			low = pivotpos + 1;
			pivotpos = partition(A, low, high);
		}
	}

	for (int i = 0; i < k; ++i) {
		output[i] = A[i];
	}
}

/*
 * 连续字数组的最大和
 */
int get_greatest_continous_num(int A[], int n) {
	if (A == NULL || n <= 0) {
		return -1;
	}

	int cur_sum = 0;
	int ret = 0x80000000;
	for (int i = 0; i < n; ++i) {
		if (cur_sum <= 0) {
			cur_sum = A[i];
		} else {
			cur_sum += A[i];
		}
		if(cur_sum > ret) {
			ret = cur_sum;
		}
	}
	return ret;
}

/*
 * 把数组排成最小的数
 */
char *combine_str1 = new char[100];
char *combine_str2 = new char[100];
int cmp(char *str1, char *str2) {
	strcpy(combine_str1, str1);
	strcat(combine_str1, str2);

	strcpy(combine_str2, str2);
	strcat(combine_str2, str1);

	return strcmp(combine_str1, combine_str2);
}

void print_min_number(int A[], int n) {
	if (A == NULL || n <= 0) {
		return;
	}

	char **str_nums = (char **)(new int[n]);
	for (int i = 0; i < n; ++i) {
		str_nums[i] = new char[100];
		sprintf(str_nums[i], "%d", A[i]);
	}

	sort(str_nums, str_nums + n, cmp);
	for (int i = 0; i < n; ++i) {
		cout << str_nums[i];
	}
	for (int i = 0; i < n; ++i) {
		delete[] str_nums[i];
	}
	delete[] str_nums;
}

/*
 * 获取排序数组中指定数字的个数
 */
int get_first_k(int A[], int n, int k, int low, int high) {
	if (low > high) {
		return -1;
	}

	int mid = (low + high) / 2;
	int val_mid = A[mid];
	if (val_mid == k) {
		if ((mid > 0 && A[mid - 1] != k)
				|| mid == 0) {
			return mid;
		} else {
			high = mid - 1;
		}
	} else if (val_mid > k) {
		high = mid - 1;
	} else {
		low = mid + 1;
	}

	return get_first_k(A, n, k, low, high);
}

int get_last_k(int A[], int n, int k, int low, int high) {
	if (low > high) {
		return -1;
	}

	int mid = (low + high) / 2;
	int val_mid = A[mid];
	if (val_mid == k) {
		if ((mid < n - 1 && A[mid + 1] != k)
				|| mid == n - 1) {
			return mid;
		} else {
			low = mid + 1;
		}
	} else if (val_mid > k) {
		high = mid - 1;
	} else {
		low = mid + 1;
	}

	return get_last_k(A, n, k, low, high);
}

int get_num_of_k(int A[], int n, int k) {
	int num = 0;
	if (A == NULL || n <= 0) {
		return num;
	}

	int first = get_first_k(A, n, k, 0, n - 1);
	int last = get_last_k(A, n, k, 0, n - 1);
	if (first > -1 && last > -1) {
		num = last - first + 1;
	}
	return num;
}

/*
 * 和为s的两个数
 */
bool find_nums_with_sum(int A[], int n, int sum, int &num1, int &num2) {
	if (A == NULL || n <= 0) {
		return false;
	}

	int low = 0, high = n - 1;
	while (low < high) {
		long long cur_sum = A[low] + A[high];
		if (cur_sum == sum) {
			num1 = A[low];
			num2 = A[high];
			return true;
		} else if (cur_sum > sum) {
			--high;
		} else {
			++low;
		}
	}
	return false;
}

/*
 * 和为s的连续正数序列
 */
void print_sequence(int small, int big) {
	for (int i = small; i <= big; ++i) {
		cout << i << ' ';
	}
}

void find_continuos_sequence(int sum) {
	if (sum < 3) {
		return;
	}

	int small = 1, big = 2;
	int mid = (1 + sum) / 2;
	int cur_sum = small + big;
	while (small < mid) {
		if (cur_sum == sum) {
			print_sequence(small, big);
		}
		while (cur_sum > sum && small < mid) {
			cur_sum -= small;
			++small;
			if (cur_sum == sum) {
				print_sequence(small, big);
			}
		}
		++big;
		cur_sum += big;
	}
}

/*
 * 扑克牌顺子（癞子斗地主）
 */
bool is_continuos(int A[], int n) {
	bool ret = false;
	if (A == NULL || n <= 0) {
		return ret;
	}

	sort(A, A + n);
	int zero = 0, gap = 0;
	for (int i = 0; i < n && A[i] == 0;
			++i) {
		++zero;
	}

	int small = zero, big = small + 1;
	while (big < n) {
		if (A[small] == A[big]) {
			return ret;
		}
		gap += (A[big] - A[small] - 1);
		small = big;
		++big;
	}

	if (gap <= zero) {
		ret = true;
	}
	return ret;
}

int main() {
	cout << "fibonacci" << endl;
	cout << fibonacci(5) << endl << endl;

	cout << "reorder odd and even" << endl;
	int A[] = {3, 8, 7, 1, 2, 5, 4, 6, 9};
	reorder_odd_even(A, 9);
	for (int i = 0; i < 9; ++i) {
		cout << A[i] << ' ';
	}
	cout << endl << endl;

	cout << "print a matrix clockwisely" << endl;
	int B[][4] = {
        1, 2, 8, 9,
        2, 4, 9, 12,
        4, 7, 10, 13,
        6, 8, 11, 15};
	print_matrix_clock_wisely(B, 4, 4);
	cout << endl << endl;

	cout << "more than half" << endl;
	int C[] = {1, 2, 3, 1, 1};
	// cout << more_than_half_num1(C, 5) << endl << endl;
	cout << more_than_half_num2(C, 5) << endl << endl;

	cout << "get least k numbers" << endl;
	int output[5];
	get_least_k_num(A, 9, output, 5);
	for (int i = 0; i < 5; ++i) {
		cout << output[i] << ' ';
	}
	cout << endl << endl;

	cout << "get greatest continuos numbers" << endl;
	cout << get_greatest_continous_num(A, 9) << endl << endl;

	cout << "print minimum number" << endl;
	int D[] = {3, 32, 321};
	print_min_number(D, 3);
	cout << endl <<endl;

	cout << "get number of k" << endl;
	int E[] = {1, 2, 3, 3, 3, 4, 5};
	cout << get_num_of_k(E, 7, 3) << endl <<endl;;

	cout << "find two numbers with their sum" << endl;
	int num1, num2;
	find_nums_with_sum(E, 7, 5, num1, num2);
	cout << "number1: " << num1 << " number2: " << num2 << endl << endl;

	cout << "find continuos sequence" << endl;
	find_continuos_sequence(45);
	cout << endl << endl;

	int F[]= {0, 0, 1, 3, 4};
	if (true == is_continuos(F, 5)) {
		cout << "is continuos" << endl << endl;
	} else {
		cout << "is not continuos" << endl << endl;
	}

	return 0;
}
