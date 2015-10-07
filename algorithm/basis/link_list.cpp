/*************************************************************************
    > File Name: link_list.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Tue 06 Oct 2015 11:42:12 AM CST
 ************************************************************************/

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

/*
 * 链表节点
 */
struct Node {
	int value;
	Node *next;

	Node(int x) {
		value = x;
		next = NULL;
	}
};

/*
 * 尾插法创建链表
 */
Node *insert(Node *head, int x) {
	if (head == NULL) {
		head = new Node(x);
	} else {
		head->next = insert(head->next, x);
	}
	return head;
}

/*
 * 打印链表
 */
void print(Node *head) {
	if (head == NULL) {
		return;
	}
	Node *tmp = head;
	while (tmp != NULL) {
		cout << tmp->value << ' ';
		tmp = tmp->next;
	}
}

/*
 * 逆向打印链表（迭代）
 */
void print_reverse_iter(Node *head) {
	if (head == NULL) {
		return;
	}

	Node *tmp = head;
	stack<Node *> S;
	while (tmp != NULL) {
		S.push(tmp);
		tmp = tmp->next;
	}

	while (!S.empty()) {
		tmp = S.top();
		S.pop();
		cout << tmp->value << ' ';
	}
}

/*
 * 逆向打印链表（递归）
 */
void print_reverse_recur(Node *head) {
	if (head == NULL) {
		return;
	}

	if (head != NULL) {
		print_reverse_recur(head->next);
	}
	cout << head->value << ' ';
}

/*
 * O(1)时间内删除指定节点
 */
void delete_node(Node **head, Node *aim) {
	if (head == NULL || aim == NULL) {
		return;
	}

	if (aim->next != NULL) {
		Node *p = aim->next;
		aim->value = p->value;
		aim->next = p->next;
		delete p;
		p = NULL;
	} else if (*head == aim) {
		delete aim;
		aim = NULL;
		*head = NULL;
	} else {
		Node *tmp = *head;
		while (tmp->next != NULL && tmp->next != aim) {
			tmp = tmp->next;
		}
		tmp->next = NULL;
		delete aim;
		aim = NULL;
	}
}

/*
 * 找出链表中倒数第k个节点
 */
Node *find_kth_node(Node *head, int k) {
	if (head == NULL || k <= 0) {
		return NULL;
	}
	Node *fast = head;
	for (int i = 1; i <= k - 1; ++i) {
		if (fast->next == NULL) {
			return NULL;
		}
		fast = fast->next;
	}
	Node *slow = head;
	while (fast->next != NULL) {
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

/*
 * 翻转链表
 */
Node *reverse_list(Node *head) {
	if (head == NULL) {
		return NULL;
	}

	Node *ret = NULL, *cur = head, *pre = NULL;
	while (cur != NULL) {
		Node *p = cur->next;
		if (p == NULL) {
			ret = cur;
		}
		cur->next = pre;
		pre = cur;
		cur = p;
	}
	return ret;
}

/*
 * 翻转m到n之间的链表
 */
Node *reverse_between_m_and_n(Node *head, int m, int n) {
	if (head == NULL || m <= 0 || n <= 0 || m >= n) {
		return head;
	}

	Node *pre = NULL, *m_pre = NULL, *cur = head;
	for (int i = 1; i <= n; ++i) {
		if (i == m) {
			m_pre = pre;
		} else if (i > m) {
			pre->next = cur->next;
			cur->next = m_pre->next;
			m_pre->next = cur;
			cur = pre;
		}
		pre = cur;
		cur = cur->next;
	}
	return head;
}

/*
 * 旋转链表，k = 2， 1->2->3->4->5 ==> 4->5->1->2->3
 */
Node *rotate_list(Node *head, int k) {
	if (head == NULL || k <= 0) {
		return head;
	}

	int len = 1;
	Node *tmp = head;
	while (tmp->next != NULL) {
		++len;
		tmp = tmp->next;
	}

	tmp->next = head;
	k = len - k % len;
	tmp = head;
	for (int i = 1; i < k; ++i) {
		tmp = tmp->next;
	}
	Node *ret = tmp->next;
	tmp->next = NULL;
	return ret;
}

/*
 * 合并两个排序的链表
 */
Node *merge(Node *sorted1, Node *sorted2) {
	if (sorted1 == NULL) {
		return sorted2;
	} else if (sorted2 == NULL) {
		return sorted1;
	}

	Node *ret = NULL;
	if (sorted1->value < sorted2->value) {
		ret= sorted1;
		ret->next = merge(sorted1->next, sorted2);
	} else {
		ret = sorted2;
		ret->next = merge(sorted1, sorted2->next);
	}
	return ret;
}

/*
 * 找出链表的第一个公共子节点
 */
int get_length(Node *head) {
	int len = 0;
	Node *tmp = head;
	while (tmp != NULL) {
		++len;
		tmp = tmp->next;
	}
	return len;
}

Node *find_first_common_node(Node *head1, Node *head2) {
	if (head1 == NULL || head2 == NULL) {
		return NULL;
	}

	int L1 = get_length(head1);
	int L2 = get_length(head2);
	cout << "L1: " << L1 << ' ' << "L2: " << L2 << endl;
	int diff = L1 - L2;
	Node *long_list = head1, *short_list = head2;
	if (diff < 0) {
		diff = L2 - L1;
		long_list = head2;
		short_list = head1;
	}

	for (int i = 0; i < diff; ++i) {
		long_list = long_list->next;
	}

	while (long_list != NULL && short_list != NULL 
			&& long_list != short_list) {
		long_list = long_list->next;
		short_list = short_list->next;
	}

	return long_list;
}

/*
 * 找出环链表的入口节点
 */
Node *meet_node_within_loop(Node *head) {
	if (head == NULL) {
		return NULL;
	}

	Node *slow = head->next;
	if (slow == NULL) {
		return NULL;
	}

	Node *fast = slow->next;
	while (fast != NULL && slow != NULL) {
		if (fast == slow) {
			return slow;
		}
		slow = slow->next;
		fast = fast->next;
		if (fast != NULL) {
			fast = fast->next;
		}
	}
	return NULL;
}

Node *start_node_of_loop1(Node *head) {
	Node *meet_node = meet_node_within_loop(head);
	if (meet_node == NULL) {
		return NULL;
	}

	int node_in_loop_num = 1;
	Node *p = meet_node;
	while (p->next != meet_node) {
		p = p->next;
		node_in_loop_num++;
	}

	p = head;
	for (int i = 0; i < node_in_loop_num; ++i) {
		p = p->next;
	}

	Node *q = head;
	while (p != q) {
		p = p->next;
		q = q->next;
	}
	return p;
}

Node *start_node_of_loop2(Node *head) {
	if (head == NULL || head->next == NULL) {
		return NULL;
	}

	Node *slow = head, *fast = head;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			Node *slow2 = head;
			while (slow2 != slow) {
				slow2 = slow2->next;
				slow = slow->next;
			}
			return slow2;
		}
	}
	return NULL;
}

/*
 * 删除链表中重复的节点
 */
Node *delete_dup(Node *head) {
	if (head == NULL) {
		return NULL;
	}

	Node *pre = NULL, *cur = head;
	while (cur != NULL) {
		Node *p = cur->next;
		bool flag = false;
		if (p != NULL && p->value == cur->value) {
			flag = true;
		}
		if (flag == false) {
			pre = cur;
			cur = p;
		} else {
			int val = cur->value;
			Node *del = cur;
			while (del != NULL && del->value == val) {
				p = del->next;

				delete del;
				del = NULL;

				del = p;
			}
			if (pre == NULL) {
				head = p;
			} else {
				pre->next = p;
			}
		}
		cur = p;
	}
	return head;
}

/*
 * 去除多余的重复节点
 */
Node *remove_dup(Node *head) {
	if (head == NULL || head->next == NULL) {
		return NULL;
	}

	Node *pre = head, *cur = head->next;
	while (cur != NULL) {
		if (pre->value == cur->value) {
			pre->next = cur->next;
			delete cur;
		} else {
			pre = cur;
		}
		cur = cur->next;
	}
	return head;
}



int main() {
	Node *head = NULL;
	for (int i = 1; i <= 9; ++i) {
		head = insert(head, i);
	}
	
	cout << "print link list in order" << endl;
	print(head);
	cout << endl << endl;

	cout << "print link list in reverse order" << endl;
	// print_reverse_iter(head);
	print_reverse_recur(head);
	cout << endl << endl;

	/*
	cout << "delete a node in O(1)" << endl;
	Node *aim = head->next->next;
	delete_node(&head, aim);
	print(head);
	cout << endl << endl;
	*/

	cout << "find kth node from the end" << endl;
	Node *kth_ret = find_kth_node(head, 3);
	cout << kth_ret->value << endl << endl;

	/*
	cout << "reverse a link list" << endl;
	Node *reverse_ret = reverse_list(head);
	print(reverse_ret);
	cout << endl << endl;
	*/

	/*
	cout << "reverse between m and n" << endl;
	Node *reverse_ret = reverse_between_m_and_n(head, 2, 4);
	print(reverse_ret);
	cout << endl << endl;
	*/

	cout << "rotate list" << endl;
	Node *rotate_ret = rotate_list(head, 2);
	print(rotate_ret);
	cout << endl << endl;

	cout << "merge two sorted link list" << endl;
	Node *sorted1 = NULL;
	for (int i = 1; i <= 9; i += 2) {
		sorted1 = insert(sorted1, i);
	}
	Node *sorted2 = NULL;
	for (int i = 2; i <= 10; i += 2) {
		sorted2 = insert(sorted2, i);
	}
	Node *merge_ret = merge(sorted1, sorted2);
	print(merge_ret);
	cout << endl << endl;

	cout << "find first common node" << endl;
	Node *second = head->next;
	Node *common_ret = find_first_common_node(head, second);
	cout << common_ret->value << endl << endl;

	cout << "start node of a loop link list" << endl;
	Node *tmp = merge_ret;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = merge_ret->next;
	// Node *start_node = start_node_of_loop1(sorted1);
	Node *start_node = start_node_of_loop2(merge_ret);
	cout << start_node->value << endl << endl;

	cout << "delete duplication nodes" << endl;
	int B[] = {1, 1, 2, 3, 5, 5, 6};
	Node *dup_head = NULL;
	for (int i = 0; i < 7; ++i) {
		dup_head = insert(dup_head, B[i]);
	}
	// Node *dup_ret = delete_dup(dup_head);
	// print(dup_ret);
	Node *dup_ret = remove_dup(dup_head);
	print(dup_ret);
	cout << endl << endl;

	return  0;
}
