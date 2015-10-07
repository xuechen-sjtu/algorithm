/*************************************************************************
    > File Name: probability.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Wed 07 Oct 2015 03:11:56 PM CST
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

/*
 * 获取从a到b之间的一个随机数
 */
int get_random(int a, int b) {
    srand((unsigned)time(NULL));
    return rand()%(b - a) + a ;
}

/*
 * 从1, 2, ..., n中找出k个不重复的随机数
 */
void get_k_random(int A[], int n, int k, vector<int> &ret) {
    if (A == NULL || n <= 0 || k > n) {
        return ;
    }

    int num = n - 1;
    int index;
    for (int i = 0; i < k; ++i) {
        index = get_random(0, num);
        int tmp = A[index];
        A[index] = A[num];
        A[num] = tmp;
        ret.push_back(A[num]);
        --num;
    }
}

/*
 * 从一个数组中等概率返回一个最大数
 */
int get_random_max(int A[], int n) {
    if (A == NULL || n <= 0) {
        cout << "array is null" << endl;
        return -1;
    }

    int max = A[0];
    int max_count = 1;
    vector<int> max_vec;
    max_vec.push_back(0);
    for (int i = 1; i < n; ++i) {
        if (max == A[i]) {
            max_vec.push_back(i);
            max_count ++;
        } else if (max < A[i]) {
            max = A[i];
            while (!max_vec.empty()) {
                max_vec.pop_back();
            }
            max_count = 1;
            max_vec.push_back(i);
        }
    }

    int aim_index = get_random(0, max_count - 1);
    return A[max_vec[aim_index]];
}

/*
 * 从一个数组（n个数）中等概率返回m个数（m <= n）
 */
void get_random_m_digits(int A[], int n, int B[], int m) {
    if (A == NULL || n <= 0 || B == NULL || m <= 0 || m > n) {
        return;
    }
    
    vector<int> rand_array;
    int *TMP = new int[n];
    for (int i = 0; i < n; ++i) {
        TMP[i] = i;
    }
    get_k_random(TMP, n, m, rand_array);
    delete[] TMP;
    TMP = NULL;

    for (int i = 0; i < m; ++i) {
        B[i] = A[rand_array[i]];
    }
}

void genknuth(int m, int n) {
    clock_t start, end;
    start = clock();
    srand(time(NULL));
    for(int i = 0; i < n; i++) {
        if(rand() % (n - i) < m) {
            cout << i << endl;
            if(!(--m)) {
                break;
            }
        }
    }

    end = clock();
    cout << "Process took " << 
        (double(end - start) / CLOCKS_PER_SEC) << "seconds" << endl;
    return ;
}

int main() {
    int A[100];
    for (int i = 0; i < 100; ++i) {
        A[i] = i + 1;
    }

    cout << "从1, ..., 100获取50个随机数" << endl;
    vector<int> random_without_dup;
    get_k_random(A, 100, 50, random_without_dup);
    for (unsigned int i = 0; i < random_without_dup.size(); ++i) {
        cout << random_without_dup[i] << ' ';
    }
    cout << endl << endl;

    cout << "从一个数组中随机返回一个最大数" << endl;
    int B[] = {1, 2, 5, 5};
    cout << get_random_max(B, 4) << endl;
    cout << endl;

    cout << "从一个包含n个数的数组中随机抽取m个数" << endl;
    int C[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *D = new int[5];
    get_random_m_digits(C, 10, D, 5);
    for (int i = 0; i < 5; ++i) {
        cout << D[i] << ' ';
    }
    cout << endl << endl;;

    cout << "从1, ..., n中随机选m个数字" << endl;
    genknuth(5, 10);

    return 0;
}


