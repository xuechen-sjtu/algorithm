/*************************************************************************
    > File Name: stack_queue.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Wed 07 Oct 2015 02:24:43 PM CST
 ************************************************************************/

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <deque>
using namespace std;

/*
 * 用两个栈实现队列
 */
template <typename T>
class CQueue {
public:
	CQueue() {
	}
	~CQueue() {
	}

	void append_to_tail(const T &node);
	T delete_head();
private:
	stack<T> stack1;
	stack<T> stack2;
};

template <typename T>
void CQueue<T>::append_to_tail(const T&element) {
	stack1.push(element);
}

template <typename T>
T CQueue<T>::delete_head() {
	if (stack2.empty()) {
		while (!stack1.empty()) {
			T x = stack1.top();
			stack1.pop();
			stack2.push(x);
		}
	}
	if (stack2.empty()) {
		cout << "queue is empty" << endl;
		return 0;
	}
	T head = stack2.top();
	stack2.pop();
	return head;
}

/*
 * 包含min函数的栈
 */
template <typename T>
class StackWithMin {
public:
	void push(const T &value);
	void pop();
	const T &get_min() const;
private:
	stack<T> m_data;
	stack<T> m_min;
};

template <typename T>
void StackWithMin<T>::push(const T &value) {
	m_data.push(value);
	if (m_min.empty() || value < m_min.top()) {
		m_min.push(value);
	} else {
		m_min.push(m_min.top());
	}
}

template <typename T>
void StackWithMin<T>::pop() {
	if (m_data.empty() || m_min.empty()) {
		cout << "stack is empty" << endl;
		return;
	}
	m_data.pop();
	m_min.pop();
}

template <typename T>
const T &StackWithMin<T>::get_min() const {
	if (m_data.empty() && m_min.empty()) {
		cout << "stack is empty" << endl;
	}
	return m_min.top();
}

/*
 * 给出入栈顺序，判断所给出栈序列是否合法
 */
bool is_pop_order(const int push[], const int pop[], int n) {
	if (push == NULL || pop == NULL || n <= 0) {
		return false;
	}

	bool possible = false;
	int idx_push = 0, idx_pop = 0;
	stack<int> S;
	while (idx_pop < n) {
		// 找到栈顶与当前pop序列值一致的位置
		while (S.empty() || S.top() != pop[idx_pop]) {
			if (idx_push == n) {
				break;
			}
			S.push(push[idx_push]);
			++idx_push;
		}
		if (S.top() != pop[idx_pop]) {
			break;
		}
		S.pop();
		++idx_pop;
	}
	if (S.empty() && idx_pop == n) {
		possible = true;
	}
	return possible;
}
		
/*
 * 滑动窗口的最大值
 */
vector<int> max_in_windows(const int A[], unsigned int n, unsigned int size) {
	vector<int> ret;
	if (A == NULL || n <= 0 || size <= 0 || size > n) {
		return ret;
	}

	deque<int> index;
	for (int i = 0; i < size; ++i) {
		while (!index.empty() && A[i] >= A[index.back()]) {
			index.pop_back();
		}
		index.push_back(i);
	}

	for (int i = size; i < n; ++i) {
		ret.push_back(A[index.front()]);
		while (!index.empty() && A[i] >= A[index.back()]) {
			index.pop_back();
		}
		if (!index.empty() && index.front() <= (int)(i - size)) {
			index.pop_front();
		}
		index.push_back(i);
	}
	ret.push_back(A[index.front()]);
	return ret;
}

int main() {
	cout << "implete a queue with two stacks" << endl;
	CQueue<int> *CQ = new CQueue<int>();
	CQ->append_to_tail(0);
	CQ->append_to_tail(1);
	cout << CQ->delete_head() << endl << endl;

	cout << "implete a stack with minimum" << endl;
	StackWithMin<int> *SWM = new StackWithMin<int>();
	SWM->push(1);
	SWM->push(2);
	cout << SWM->get_min() << endl;
	SWM->pop();
	SWM->push(0);
	cout << SWM->get_min() << endl << endl;

	int A[] = {1, 2, 3, 4, 5};
	// int B[] = {4, 5, 3, 2, 1};
	int B[] = {4, 3, 5, 1, 2};
	if (true == is_pop_order(A, B, 5)) {
		cout << "is pop order" << endl << endl;
	} else {
		cout << "is not pop order" << endl << endl;
	}

	vector<int> ret = max_in_windows(A, 5, 3);
	for (int i = 0; i < ret.size(); ++i) {
		cout << ret[i] << ' ';
	}
	cout << endl << endl;

	return 0;
}
