/*************************************************************************
    > File Name: string.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Tue 06 Oct 2015 10:16:36 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

/*
 * 将字符串中所有的空格全部换成%20
 */
void replace_blank(char str[], int len) {
	if (str == NULL) {
		cout << "null string" << endl;
		return;
	}

	int org_len = 0, blank_num = 0, new_len = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == ' ') {
			++blank_num;
		}
		++org_len;
	}
	new_len = org_len + 2 * blank_num;

	if (new_len > len) {
		cout << "overflow" << endl;
		return;
	}

	int idx_org = org_len - 1, idx_new = new_len - 1;
	while (idx_org >= 0 && idx_new > idx_org) {
		if (str[idx_org] == ' ') {
			str[idx_new--] = '0';
			str[idx_new--] = '2';
			str[idx_new--] = '%';
		} else {
			str[idx_new--] = str[idx_org];
		}
		--idx_org;
	}
}

/*
 * 打印1到最大的n位数（n = 3，则输出1, 2, ..., 999)
 */
void print_number(char *number) {
	bool is_begin = false;
	for (int i = 0; number[i] != '\0'; ++i) {
		if (is_begin == false && number[i] != '0') {
			is_begin = true;
		}
		if (is_begin == true) {
			cout << number[i];
		}
	}
	cout << '\t';
}

bool increment(char *number) {
	bool is_overflow = false;
	int c = 0;
	int len = strlen(number);
	for (int i = len - 1; i >= 0; --i) {
		int sum = number[i] - '0' + c;
		if (i == len - 1) {
			++sum;
		}

		if (sum >= 10) {
			if (i == 0) {
				is_overflow = true;
			} else {
				sum -= 10;
				c = 1;
				number[i] = sum + '0';
			}
		} else {
			number[i] = sum + '0';
			break;
		}
	}
	return is_overflow;
}

void print_max_n_digits(int n) {
	if (n <= 0) {
		return;
	}

	char *number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';

	while (!increment(number)) {
		print_number(number);
	}

	delete number;
	number = NULL;
}

/*
 * 字符串全排列
 */
void permutation(char *string, char *begin) {
	if (*begin == '\0') {
		cout << string << endl;
	} else {
		for (char *ch = begin; *ch != '\0'; ++ch) {
			char tmp = *ch;
			*ch = *begin;
			*begin  =tmp;

			permutation(string, begin + 1);

			tmp = *ch;
			*ch = *begin;
			*begin = tmp;
		}
	}
}

void permutation(char *string) {
	if (string == NULL) {
		return;
	}
	permutation(string, string);
}

/*
 * 只出现一次的字符
 */
char first_not_repeate_char(char *string) {
	if (string == NULL) {
		return '\0';
	}

	int *hash = new int[256];
	for (int i = 0; i < 256; ++i) {
		hash[i] = 0;
	}

	for (int i = 0; string[i] != '\0'; ++i) {
		++hash[string[i]];
	}

	for (int i = 0; i < 256; ++i) {
		if (hash[i] == 1) {
			return i;
		}
	}
}

/*
 * 字符串转整数
 */
int str_to_int_core(const char *digits, bool minus) {
	long long num = 0;
	while (*digits != '\0') {
		if (*digits >= '0' && *digits <= '9') {
			int flag = minus ? -1 : 1;
			num = num * 10 + flag * (*digits - '0');

			if ((!minus && num > 0x7fffffff)
					|| (minus && num <= (signed int)0x80000000)) {
				num = 0;
				break;
			}
			++digits;
		} else {
			num = 0;
			break;
		}
	}
	return num;
}

int str_to_int(const char *string) {
	long long num = 0;
	if (string == NULL || *string == '\0') {
		return num;
	}

	bool minus = false;
	if (*string == '+') {
		++string;
	} else if (*string == '-') {
		++string;
		minus = true;
	}

	if (*string == '\0') {
		return num;
	}

	num = str_to_int_core(string, minus);

	return (int)num;
}

/*
 * 数值的整数次方
 */
bool equal(double num1, double num2) {
	if ((num1 - num2 > -0.00000001) ||
			(num1 - num2 <= 0.00000001)) {
		return true;
	} else {
		return false;
	}
}

double power_iter(double base, int exponent) {
	double result = 1.0;
	for (int i = 1; i <= exponent; ++i) {
		result *= base;
	}
	return result;
}

double power_recur(double base, int exponent) {
	if (exponent == 0) {
		return 1.0;
	}
	if (exponent == 1) {
		return base;
	}
	double result = power_recur(base, exponent >> 1);
	result *= result;
	if (exponent & 0x1 == 1) {
		result *= base;
	}
	return result;
}

double power(double base, int exponent) {
	if (equal(base, 0.0) && exponent < 0) {
		return 0.0;
	}

	unsigned int abs_exponent = (unsigned int)(exponent);
	if (exponent < 0) {
		abs_exponent = -exponent;
	}

	double result = power_iter(base, abs_exponent);
	if (exponent < 0) {
		return 1.0 / result;
	}
	return result;
}

/*
 * 翻转字符串 "I love you" -> "you love I"
 */
void reverse(char *pBegin, char *pEnd) {
	if (pBegin == NULL || pEnd == NULL) {
		return;
	}

	while (pBegin < pEnd) {
		char tmp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = tmp;

		++pBegin;
		--pEnd;
	}
}

char *reverse_sentence(char *string) {
	if (string == NULL) {
		return NULL;
	}

	char *pBegin = string;
	char *pEnd = string;
	while (*pEnd != '\0') {
		++pEnd;
	}
	--pEnd;

	reverse(pBegin, pEnd);

	pBegin = pEnd = string;
	while (*pBegin != '\0') {
		if (*pBegin == ' ') {
			++pBegin;
			++pEnd;
		} else if (*pEnd == ' ' || *pEnd == '\0') {
			reverse(pBegin, --pEnd);
			pBegin = ++pEnd;
		} else {
			++pEnd;
		}
	}
	return string;
}
		
/*
 * 字符串是否包含另外一个子字符串
 */
bool contains1(const char *string, const char *substring) {
	if (string == NULL || substring == NULL) {
		return false;
	}
	
	int m = strlen(string);
	int n = strlen(substring);
	if (m < n) {
		return false;
	}

	for (int i = 0; i <= m - n; ++i) {
		int j = 0;
		for (; j < n; ++j) {
			if (string[i + j] != substring[j]) {
				break;
			}
		}
		if (j == n) {
			return true;
		}
	}
	return false;
}

/*
 * KMP
 */
void compute_prefix(int *next, char *p) {
	int	i, n, k;

	n = strlen(p);
	next[1] = next[0] = 0;
	k = 0;		/* 第i次迭代开始之前，k表示next[i-1]的值 */	
	for (i = 2; i <= n; i++) {
		for (; k != 0 && p[k] != p[i-1]; k = next[k]) {
			;
		}
		if (p[k] == p[i-1]) {
			k++;
		}

		next[i] = k;
	}
}

void kmp_match(char *text, char *p, int *next) {
	int m, n, s, q;

	m = strlen(p);
	n = strlen(text);
	q = s = 0;	/* q表示上一次迭代匹配了多少个字符，
				   s表示这次迭代从text的哪个字符开始比较 */ 
	while (s < n) {
		for (q = next[q]; q < m && p[q] == text[s]; q++, s++) {
			;
		}

		if (q == 0) {
			s++;
		} else if (q == m) {
			cout << "pattern occurs with shift " << s-m << endl;
		}
	}
}

int main() {
	cout << "replace blank" << endl;
	char str1[] = "I love you. haha";
	cout << "before: " << str1 << endl;
	replace_blank(str1, 100);
	cout << "after: " << str1 << endl;

	cout << "print max n digits" << endl;
	print_max_n_digits(3);
	cout << endl << endl;

	cout << "permutation" << endl;
	char str2[] = "abcd";
	permutation(str2);
	cout << endl << endl;

	cout << "first not repeated character" << endl;
	char str3[] = "xaabbccd";
	cout << first_not_repeate_char(str3) << endl << endl;

	cout << "string to integer" << endl;
	char str4[] = "1234";
	cout << str_to_int(str4) << endl << endl;

	cout << "power" <<endl;
	cout << power(2, 30) << endl << endl;

	cout << "reverse a sentence" << endl;
	char str5[] = "I love you";
	cout << reverse_sentence(str5) << endl << endl;

	if (true == contains1("I love you", "love")) {
		cout << "string contains substring" << endl << endl;
	} else {
		cout << "string not contains substring" << endl << endl;
	}

	cout << "KMP" << endl;
	int next[101];
	char p[] = "ababacb";
	char text[] = "abababaababacb";
	compute_prefix(next, p);
	kmp_match(text, p, next);

	return 0;
}

