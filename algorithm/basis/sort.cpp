/*************************************************************************
    > File Name: sort.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Mon 05 Oct 2015 11:27:39 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

/*
 * 插入排序
 */
void insert_sort(int A[], int n) {
	if (A == NULL || n <= 0) {
		return ;
	}

	for (int i = 1; i < n; ++i) {
		if (A[i] < A[i - 1]) {
			int aim = A[i];
			int j;
			for (j = i - 1; j >= 0; --j) {
				if (A[j] > aim) {
					A[j + 1] = A[j];
				} else {
					break;
				}
		}
			A[j + 1] = aim;
		}
	}
}

/*
 * 冒泡排序
 */
void bubble_sort(int A[], int n) {
	if (A == NULL || n <= 0) {
		return;
	}
	for (int i = 0; i < n; ++i) {
		bool flag = false;
		for (int j = n - 1; j > i; --j) {
			if (A[j - 1] > A[j]) {
				int tmp = A[j - 1];
				A[j - 1] = A[j];
				A[j] = tmp;
				flag = true;
			}
		}
		if (false == flag) {
			break;
		}
	}
}

/*
 * 选择排序
 */
void select_sort(int A[], int n) {
	if (A == NULL || n <= 0) {
		return ;
	}

	for (int i = 0; i < n - 1; ++i) {
		int aim = i;
		for (int j = i + 1; j < n; ++j) {
			if (A[aim] > A[j]) {
				aim = j;
			}
		}
		if (aim != i) {
			int tmp = A[aim];
			A[aim] = A[i];
			A[i] = tmp;
		}
	}
}

/*
 * 快速排序
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

void quick_sort(int A[], int low, int high) {
	if (low < high) {
		int pivotpos = partition(A, low, high);
		quick_sort(A, low, pivotpos - 1);
		quick_sort(A, pivotpos + 1, high);
	}
}

void quick_sort(int A[], int n) {
	if (A == NULL || n <= 0) {
		return ;
	}
	int low = 0, high = n - 1;
	quick_sort(A, low, high);
}

/*
 * 归并排序
 */
void merge(int A[], int low, int mid, int high) {
	int l_len = mid - low + 1;
	int r_len = high - mid;
	int *left = new int[l_len];
	int *right = new int[r_len];

	int l_idx = 0, r_idx = 0, idx = low;
	for (int i = low; i <= mid; ++i) {
		left[l_idx++] = A[i];
	}
	for (int i = mid + 1; i <= high; ++i) {
		right[r_idx++] = A[i];
	}

	l_idx = r_idx = 0;
	while (l_idx != l_len && r_idx != r_len) {
		if (left[l_idx] < right[r_idx]) {
			A[idx++] = left[l_idx++];
		} else {
			A[idx++] = right[r_idx++];
		}
	}
	while (l_idx != l_len) {
		A[idx++] = left[l_idx++];
	}
	while (r_idx != r_len) {
		A[idx++] = right[r_idx++];
	}
}


void merge_sort(int A[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		merge_sort(A, low, mid);
		merge_sort(A, mid + 1, high);
		merge(A, low, mid, high);
	}
}

void merge_sort(int A[], int n) {
	if (A == NULL || n <= 0) {
		return ;
	}
	int low = 0, high = n - 1;
	merge_sort(A, low, high);
}

/*
 * 堆排序
 */
void adjust_down(int A[], int k, int n) {
	A[0] = A[k];
	for (int i = k * 2; i <= n; i *= 2) {
		if (i < n && A[i] < A[i + 1]) {
			++i;
		}
		if (A[0] > A[i]) {
			break;
		} else {
			A[i] = A[i];
			k = i;
		}
	}
	A[k] = A[0];
}

void build_max_heap(int A[], int n) {
	for (int i = n / 2; i >= 1; --i) {
		adjust_down(A, i, n);
	}
}

void heap_sort(int A[], int n) {
	if (A == NULL || n <= 0) {
		return;
	}
	build_max_heap(A, n);
	for (int i = n; i > 0; --i) {
		int tmp = A[1];
		A[1] = A[i];
		A[i] = tmp;
		adjust_down(A, 1, i - 1);
	}
}

int main() {
	int A[] = {-1, 3, 8, 7, 1, 2, 5, 6, 4, 9};
	// insert_sort(A, 9);
	// bubble_sort(A, 9);
	// select_sort(A, 9);
	// quick_sort(A, 9);
	merge_sort(A, 9);
	for (int i = 1; i <= 9; ++i) {
		cout << A[i] << ' ';
	}
	cout << endl;
	return 0;
}

