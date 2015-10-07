/*************************************************************************
    > File Name: binary_tree.cpp
    > Author: xinyang
    > Mail: xuechen.xy@gmail.com 
    > Created Time: Fri 02 Oct 2015 05:24:25 PM CST
 ************************************************************************/
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

/*
 * 二叉树节点
 */
struct Node {
	int value;
	Node *lchild, *rchild;
	Node *next;

	Node (int x) {
		value = x;
		lchild = NULL;
		rchild = NULL;
		next = NULL;
	}
};

/*
 * 往二叉树中插入节点
 */
Node *insert(Node *T, int x) {
	if (T == NULL) {
		T = new Node(x);
	} else if (T->value > x) {
		T->lchild = insert(T->lchild, x);
	} else if (T->value < x) {
		T->rchild = insert(T->rchild, x);
	}

	return T;
}

/*
 * 前序遍历（递归）
 */
void pre_order_recur(Node *T) {
	cout << T->value << ' ';
	if (T->lchild != NULL) {
		pre_order_recur(T->lchild);
	} 
	if (T->rchild != NULL) {
		pre_order_recur(T->rchild);
	}
}

/*
 * 前序遍历（非递归）
 */
void pre_order_iter(Node *T) {
	if (T == NULL) {
		return;
	}

	Node *tmp = T;
	stack<Node *> S;
	while (tmp != NULL || !S.empty()) {
		while (tmp != NULL) {
			S.push(tmp);
			cout << tmp->value << ' ';
			tmp = tmp->lchild;
		}
		if (!S.empty()) {
			tmp = S.top();
			S.pop();
			tmp = tmp->rchild;
		}
	}
}

/*
 * 中序遍历（递归）
 */
void in_order_recur(Node *T) {
	if (T->lchild != NULL) {
		in_order_recur(T->lchild);
	}
	cout << T->value << ' ';
	if (T->rchild != NULL) {
		in_order_recur(T->rchild);
	}
}

/*
 * 中序遍历（非递归）
 */
void in_order_iter(Node *T) {
	if (T == NULL) {
		return ;
	}

	Node *tmp = T;
	stack<Node *> S;
	while (tmp != NULL || !S.empty()) {
		while (tmp != NULL) {
			S.push(tmp);
			tmp = tmp->lchild;
		}
		if (!S.empty()) {
			tmp = S.top();
			S.pop();
			cout << tmp->value << ' ';
			tmp = tmp->rchild;
		}
	}
}

/*
 * 后序遍历（递归）
 */
void post_order_recur(Node *T) {
	if (T->lchild != NULL) {
		post_order_recur(T->lchild);
	}
	if (T->rchild != NULL) {
		post_order_recur(T->rchild);
	}
	cout << T->value << ' ';
}
/*
 * 后序遍历（非递归）
 */
void post_order_iter(Node *T) {
	if (T == NULL) {
		return;
	}

	Node *pre = NULL, *cur = NULL;
	stack<Node *> S;
	S.push(T);
	while (!S.empty()) {
		cur = S.top();
		if ((cur->lchild == NULL && cur->rchild == NULL)
				|| (pre != NULL && (pre == cur->lchild || pre == cur->rchild))) {
			cout << cur->value << ' ';
			S.pop();
			pre = cur;
		} else {
			if (cur->rchild != NULL) {
				S.push(cur->rchild);
			}
			if (cur->lchild != NULL) {
				S.push(cur->lchild);
			}
		}
	}
}

/*
 * 层次遍历
 */
void level_order(Node *T) {
	if (T == NULL) {
		return;
	}

	Node *tmp = T;
	queue<Node *> Q;
	Q.push(tmp);
	while (!Q.empty()) {
		tmp = Q.front();
		Q.pop();
		cout << tmp->value << ' ';
		if (tmp->lchild != NULL) {
			Q.push(tmp->lchild);
		}
		if (tmp->rchild != NULL) {
			Q.push(tmp->rchild);
		}
	}
}

/*
 * 按行打印（换行）
 */
void level_order_line(Node *T) {
	if (T == NULL) {
		return;
	}

	int cur = 0, last = 0;
	Node *tmp = T;
	queue<Node *> Q;
	Q.push(tmp);
	cur = 1;
	while (!Q.empty()) {
		last = cur;
		while (last--) {
			tmp = Q.front();
			Q.pop();
			cout << tmp->value << ' ';
			if (tmp->lchild != NULL) {
				Q.push(tmp->lchild);
			} 
			if (tmp->rchild != NULL) {
				Q.push(tmp->rchild);
			}
		}
		cur = Q.size();
		cout << endl;
	}
}

/*
 * 按行打印（之字形）
 */
void level_order_s(Node *T) {
	if (T == NULL) {
		return;
	}

	stack<Node *> levels[2];
	int current = 0, next = 1;
	Node *tmp = T;
	levels[current].push(tmp);
	while (!levels[current].empty() || !levels[next].empty()) {
		tmp = levels[current].top();
		levels[current].pop();
		cout << tmp->value << ' ';

		if (current == 0) {
			if (tmp->lchild != NULL) {
				levels[next].push(tmp->lchild);
			}
			if (tmp->rchild != NULL) {
				levels[next].push(tmp->rchild);
			}
		} else {
			if (tmp->rchild != NULL) {
				levels[next].push(tmp->rchild);
			}
			if (tmp->lchild != NULL) {
				levels[next].push(tmp->lchild);
			}
		}

		if (levels[current].empty()) {
			cout << endl;
			current = 1 - current;
			next = 1 - next;
		}
	}
}
/*
 * 高度（递归）
 */
int height_recur(Node *T) {
	if (T == NULL) {
		return 0;
	}

	int left = height_recur(T->lchild);
	int right = height_recur(T->rchild);
	return left > right ? (left + 1) : (right + 1);
}
/*
 * 高度（非递归）
 */
int height_iter(Node *T) {
	if (T == NULL) {
		return 0;
	}

	Node *tmp = T;
	queue<Node *> Q;
	Q.push(tmp);
	while (!Q.empty()) {
		tmp = Q.front();
		Q.pop();
		if (tmp->lchild != NULL) {
			Q.push(tmp->lchild);
		}
		if (tmp->rchild != NULL) {
			Q.push(tmp->rchild);
		}
	}

	Node *m = tmp, *n = T;
	int h = 0;
	while (m != n) {
		Q.push(n);
		while (!Q.empty()) {
			tmp = Q.front();
			Q.pop();
			if (tmp->lchild == m || tmp->rchild == m) {
				++h;
				m = tmp;
				break;
			}
			if (tmp->lchild != NULL) {
				Q.push(tmp->lchild);
			}
			if (tmp->rchild != NULL) {
				Q.push(tmp->rchild);
			}
		}
	}
	return h + 1;
}
/*
 * 宽度
 */
int width(Node *T) {
	if (T == NULL) {
		return 0;
	}

	Node *tmp = T;
	queue<Node *> Q;
	Q.push(tmp);
	int last_width = 1, last_width_tmp = 1;
	int width = 1, cur_width = 1;
	while (!Q.empty()) {
		last_width_tmp = last_width;
		while (last_width_tmp--) {
			tmp = Q.front();
			Q.pop();
			if (tmp->lchild != NULL) {
				Q.push(tmp->lchild);
			}
			if (tmp->rchild != NULL) {
				Q.push(tmp->rchild);
			}
		}
		cur_width = Q.size();
		width = cur_width > width ? cur_width : width;
		last_width = cur_width;
	}
	return width;
}

/*
 * 平衡二叉树判断1
 */
bool is_balanced1(Node *T) {
	if (T == NULL) {
		return true;
	}

	int left = height_recur(T->lchild);
	int right = height_recur(T->rchild);
	int diff = left - right;
	if (diff > 1 || diff < -1) {
		return false;
	} else {
		return is_balanced1(T->lchild)
			&& is_balanced1(T->rchild);
	}
}
/*
 * 最小高度
 */
int min_depth(Node *T) {
	if (T == NULL) {
		return 0;
	}

	return 1 + min(min_depth(T->lchild), 
			min_depth(T->rchild));
}
/*
 * 最大高度
 */
int max_depth(Node *T) {
	if (T == NULL) {
		return 0;
	}

	return 1 + max(max_depth(T->lchild), 
			max_depth(T->rchild));
}

/*
 * 平衡二叉树判断2
 */
bool is_balanced2(Node *T) {
	if (T == NULL) {
		return true;
	}

	int min_h = min_depth(T);
	int max_h = max_depth(T);
	return max_h - min_h <= 1;
}

/*
 * 判断两棵二叉树是否相等
 */
bool is_equal(Node *T1, Node *T2) {
	if (T1 == NULL && T2 == NULL) {
		return true;
	}

	if (T1 == NULL || T2 == NULL) {
		return false;
	}

	if (T1->value == T2->value) {
		return is_equal(T1->lchild, T2->lchild)
			&& is_equal(T1->rchild, T2->rchild);
	} else {
		return false;
	}
}

/*
 * 判断两棵二叉树是否对称
 */
bool is_symmetrical(Node *T1, Node *T2) {
	if (T1 == NULL && T2 == NULL) {
		return true;
	}

	if (T1 == NULL || T2 == NULL) {
		return false;
	}

	if (T1->value == T2->value) {
		return is_symmetrical(T1->lchild, T2->rchild)
			&& is_symmetrical(T1->rchild, T2->lchild);
	} else {
		return false;
	}
}

bool is_symmetrical(Node *T) {
	if (T == NULL) {
		return true;
	}

	return is_symmetrical(T, T);
}

/*
 * 求一棵二叉树的镜像
 */
Node *mirror(Node *T) {
	if (T == NULL) {
		return NULL;
	}

	if (T->lchild == NULL && T->rchild == NULL) {
		return T;
	}

	Node *tmp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = tmp;
	if (T->lchild != NULL) {
		T->lchild = mirror(T->lchild);
	}
	if (T->rchild != NULL) {
		T->rchild = mirror(T->rchild);
	}
	return T;
}

/*
 * 二叉树1与2有相同的根节点，判断1是否包含2
 */
bool does_1_has_2(Node *T1, Node *T2) {
	if (T2 == NULL) {
		return true;
	}

	if (T1 == NULL) {
		return false;
	}

	if (T1->value == T2->value) {
		return does_1_has_2(T1->lchild, T2->lchild)
			&& does_1_has_2(T1->rchild, T2->rchild);
	} else {
		return false;
	}
}

/*
 * 判断二叉树1中是否包含二叉树2
 */
bool has_subtree(Node *T1, Node *T2) {
	bool result = false;
	if (T2 == NULL) {
		return true;
	}

	if (T1 == NULL) {
		return false;
	}

	if (T1->value == T2->value) {
		result = does_1_has_2(T1, T2);
	}

	if (false == result) {
		result = has_subtree(T1->lchild, T2);
	}

	if (false == result) {
		result = has_subtree(T1->rchild, T2);
	}

	return result;
}

/*
 * 判断一棵完美二叉树
 */
bool is_perfect_tree(Node *T) {
	if (T == NULL) {
		return true;
	}

	queue<Node *> Q;
	Node *tmp = T;
	Q.push(tmp);
	while (!Q.empty()) {
		tmp = Q.front();
		Q.pop();
		if ((tmp->lchild != NULL && tmp->rchild == NULL) 
				|| (tmp->lchild == NULL && tmp->rchild != NULL)) {
			return false;
		}
		if (tmp->lchild != NULL) {
			Q.push(tmp->lchild);
		}
		if (tmp->rchild != NULL) {
			Q.push(tmp->rchild);
		}
	}
	return true;
}

/*
 * 判断一棵完全二叉树
 */
bool is_complete_tree(Node *T) {
	if (T == NULL) {
		return true;
	}

	queue<Node *> Q;
	Node *tmp = T;
	Q.push(tmp);
	while (!Q.empty()) {
		tmp = Q.front();
		Q.pop();
		if (tmp == NULL) {
			break;
		}
		Q.push(tmp->lchild);
		Q.push(tmp->rchild);
	}

	while (!Q.empty()) {
		tmp = Q.front();
		Q.pop();
		if (tmp != NULL) {
			return false;
		}
	}
	return true;
}

/*
 * 由前序遍历以及中序遍历序列构建二叉树
 */
int pre[] = {3, 1, 2, 8, 7, 5, 4, 6, 9};
int in[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
Node *build_tree(int s1, int e1, int s2, int e2) {
	Node *ret = new Node(pre[s1]);
	int rootIdx;
	int i;
	for (i = s2; i <= e2; ++i) {
		if (in[i] == pre[s1]) {
			rootIdx = i;
			break;
		}
	}

	if (i == e2 + 1) {
		return NULL;
	}

	if (rootIdx != s2) {
		ret->lchild = build_tree(s1 + 1, s1 + rootIdx - s2, 
				s2, rootIdx - 1);
	}

	if (rootIdx != e2) {
		ret->rchild = build_tree(s1 + rootIdx - s2 + 1, 
				e1, rootIdx + 1, e2);
	}

	return ret;
}

/*
 * 判断是否是BST的后序序列
 */
bool verify_sequence_of_BST(int A[], int n) {
	if (A == NULL || n <= 0) {
		return true;
	}

	int root = A[n - 1];
	int i = 0;
	for (; i < n - 1; ++i) {
		if (A[i] > root) {
			break;
		}
	}

	int j = i;
	for (; j < n - 1; ++j) {
		if (A[j] < root) {
			return false;
		}
	}

	bool left = true;
	if (i > 0) {
		left = verify_sequence_of_BST(A, i);
	}
	bool right = true;
	if (i < n - 1) {
		right = verify_sequence_of_BST(A + i, n - i - 1);
	}
	return left && right;
}

/*
 * 从二叉树中查找和为定值的路径
 */
void find_path(Node *T, int sum, vector<int> &path, int cur_sum) {
	cur_sum += T->value;
	path.push_back(T->value);
	bool is_leaf = T->lchild == NULL && T->rchild == NULL;
	if (is_leaf == true && cur_sum == sum) {
		for (int i = 0; i < path.size(); ++i) {
			cout << path[i] << ' ';
		}
		cout << endl;
	}

	if (T->lchild != NULL) {
		find_path(T->lchild, sum, path, cur_sum);
	}

	if (T->rchild != NULL) {
		find_path(T->rchild, sum, path, cur_sum);
	}
	path.pop_back();
}

void find_path(Node *T, int sum) {
	if (T == NULL) {
		return;
	}

	int cur_sum = 0;
	vector<int> path;
	find_path(T, sum, path, cur_sum);
}

/*
 * 将二叉搜索树转换为双向链表
 */
void convert_node(Node *T, Node **last_node) {
	if (T == NULL) {
		return ;
	}

	if (T->lchild != NULL) {
		convert_node(T->lchild, last_node);
	}

	T->lchild = *last_node;
	if (*last_node != NULL) {
		(*last_node)->rchild = T;
	}
	*last_node = T;

	if (T->rchild != NULL) {
		convert_node(T->rchild, last_node);
	}
}	

Node *convert(Node *T) {
	Node *last_node = NULL;
	convert_node(T, &last_node);
	Node *head = last_node;
	while (head != NULL && head->lchild != NULL) {
		head = head->lchild;
	}
	return head;
}

/*
 * 找出BST中第k个节点
 */
Node *kth_node_core(Node *T, int &k) {
	Node *target = NULL;
	if (T->lchild != NULL) {
		target = kth_node_core(T->lchild, k);
	}

	if (target == NULL) {
		if (k == 1) {
			target = T;
		}
		--k;
	}

	if (target == NULL && T->rchild != NULL) {
		target = kth_node_core(T->rchild, k);
	}
	return target;
}

Node *kth_node(Node *T, int k) {
	if (T == NULL || k <= 0) {
		return NULL;
	}

	return kth_node_core(T, k);
}

/*
 * 获取二叉树中两个节点的最大距离（边个数）
 */
struct RESULT {
	int max_distance;
	int max_depth;
};

RESULT get_max_distance(Node *T) {
	if (T == NULL) {
		RESULT empty = {0, -1};
		return empty;
	}
	
	RESULT lhs = get_max_distance(T->lchild);
	RESULT rhs = get_max_distance(T->rchild);
	RESULT ret;
	ret.max_depth = max(lhs.max_depth + 1, rhs.max_depth + 1);
	ret.max_distance = max(max(lhs.max_distance, rhs.max_distance),
			lhs.max_depth + rhs.max_depth + 2);
	return ret;
}

/*
 * 获取两个节点的最低公共祖先（递归）
 */
Node *common_parent1(Node *T, Node *node1, Node *node2) {
	if (T == NULL) {
		return NULL;
	}

	if (node1 == T || node2 == T) {
		return T;
	}

	Node *left = common_parent1(T->lchild, node1, node2);
	Node *right = common_parent1(T->rchild, node1, node2);
	if (left == NULL) {
		return right;
	} else if (right == NULL) {
		return left;
	} else {
		return T;
	}
}

/*
 * 获取两个节点的最低公共祖先（迭代）
 */
bool find_node(Node *T, Node *node, vector<Node *> &path) {
	if (T == NULL) {
		return false;
	}

	path.push_back(T);
	if (T == node) {
		return true;
	}

	bool found = false;
	found = find_node(T->lchild, node, path);
	if (false == found) {
		found = find_node(T->rchild, node, path);
	}
	if (false == found) {
		path.pop_back();
	}
	return found;
}

Node *common_parent2(Node *T, Node *node1, Node *node2) {
	Node *ret = NULL;
	vector<Node *> path1;
	vector<Node *> path2;
	bool has_node1 = find_node(T, node1, path1);
	bool has_node2 = find_node(T, node2, path2);
	if (false == has_node1 || false == has_node2) {
		return T;
	}

	int L1 = path1.size();
	int L2 = path2.size();
	for (int i = 0, j = 0; i != L1 && j != L2; ++i, ++j) {
		if (path1[i] != path2[j]) {
			break;
		}
		ret= path1[i];
	}
	return ret;
}

/*
 * 判断一个节点是否是叶节点，如果是，求出根节点到该节点的路径
 */
bool find_leaf_node(Node *T, Node *node, vector<Node *> &path) {
	if (T == NULL) {
		return false;
	}

	path.push_back(T);
	bool is_leaf = T->lchild == NULL && T->rchild == NULL;
	if (true == is_leaf && T == node) {
		return true;
	}

	bool found = false;
	found = find_leaf_node(T->lchild, node, path);
	if (false == found) {
		found = find_leaf_node(T->rchild, node, path);
	}
	if (false == found) {
		path.pop_back();
	}
	return found;
}

/*
 * 在一棵完全二叉树中使用next指针链接旁边的节点
 */
void connect_complete_tree(Node *T) {
	if (T == NULL) {
		return ;
	}

	Node *tmp = T;
	Node *first = NULL;
	while (tmp != NULL) {
		if (first == NULL) {
			first = tmp->lchild;
		}
		if (tmp->lchild != NULL) {
			tmp->lchild->next = tmp->rchild;
		} else {
			break;
		}
		if (tmp->next != NULL) {
			tmp->rchild->next = tmp->next->lchild;
			tmp = tmp->next;
			continue;
		} else {
			tmp = first;
			first = NULL;
		}
	}
}

/*
 * 在一棵普通二叉树中使用next指针链接旁边的节点
 */
void connext_normal_tree(Node *T) {
	if (T == NULL) {
		return ;
	}

	Node *tmp = T;
	Node *first = NULL, *last = NULL;
	while (tmp != NULL) {
		if (first == NULL) {
			if (tmp->lchild != NULL) {
				first = tmp->lchild;
			} else if (tmp->rchild != NULL) {
				first = tmp->rchild;
			}
			if (tmp->lchild != NULL) {
				if (last != NULL) {
					last->next = tmp->lchild;
				}
				last = tmp->next;
			}
			if (tmp->rchild != NULL) {
				
				if (last != NULL) {
					last->next = tmp->rchild;
				} 
				last = tmp->next;
			}
			if (tmp->next != NULL) {
				tmp = tmp->next;
			} else {
				tmp = first;
				first = NULL;
				last = NULL;
			}
		}
	}
}

/*
 * 将一个排过序的链表转成一棵BST
 */
struct ListNode {
	int value;
	ListNode *next;
	ListNode(int x) {
		value = x;
		next = NULL;
	}
};

Node *build_from_list(ListNode *start, ListNode *end) {
	if (start == end) {
		return NULL;
	}

	ListNode *fast = start, *slow = start;
	while (fast != end && fast->next != end) {
		slow = slow->next;
		fast = fast->next->next;
	}

	Node *ret = new Node(slow->value);
	
	ret->lchild = build_from_list(start, slow);
	ret->rchild = build_from_list(slow->next, end);

	return ret;
}

Node *sorted_list_to_BST(ListNode *head) {
	return build_from_list(head, NULL);
}

/*
 * 将一个排过序的数组转换成一棵BST
 */
Node *build_from_array(const vector<int> &num, int start, int end) {
	if (start >= end) {
		return NULL;
	}

	int mid = (start + end) / 2;
	Node *ret = new Node(num[mid]);

	ret->lchild = build_from_array(num, start, mid);
	ret->rchild = build_from_array(num, mid + 1, end);

	return ret;
}

Node *sort_array_to_BST(const vector<int> &num) {
	return build_from_array(num, 0, num.size());
}

/*
 * 将一颗二叉树磨平
 */
void flatten(Node *T) {
	if (T == NULL) {
		return;
	}

	stack<Node *> S;
	Node *p = new Node (0);
	Node *ret = p;

	S.push(T);
	while (!S.empty()) {
		Node *tmp = S.top();
		S.pop();

		p->rchild = tmp;
		p = tmp;

		if (tmp->rchild != NULL) {
			S.push(tmp->rchild);
			tmp->rchild = NULL;
		}
		if (tmp->lchild != NULL) {
			S.push(tmp->lchild);
			tmp->lchild = NULL;
		}
	}
}

/*
 * 判断一棵二叉树是否是BST
 */
#define MIN 0x80000000
#define MAX 0x7fffffff
bool is_valid_BST_core(Node *T, int min, int max) {
	if (T == NULL) {
		return true;
	}

	if (T->value < min || T->value > max) {
		return false;
	}

	return is_valid_BST_core(T->lchild, min, T->value)
		&& is_valid_BST_core(T->rchild, T->value, max);

}

bool is_valid_BST(Node *T) {
	return is_valid_BST_core(T, MIN, MAX);
}

int main() {
	int A[] = {3, 8, 7, 1, 2, 5, 6, 4, 9};
	Node *T = NULL;
	for (int i = 0; i < 9; ++i) {
		T = insert(T, A[i]);
	}

	cout << "pre_order_recur" << endl;
	pre_order_recur(T);
	cout << endl;
	cout << "pre_order_iter" << endl;
	pre_order_iter(T);
	cout << endl << endl;

	cout << "in_order_recur" << endl;
	in_order_recur(T);
	cout << endl;
    cout << "in_order_iter" << endl;
    in_order_iter(T);
    cout << endl << endl;

	cout << "post_order_recur" << endl;
    post_order_recur(T);
    cout << endl;
    cout << "post_order_iter" << endl;
    post_order_iter(T);
    cout << endl << endl;

	cout << "level_order" << endl;
	level_order(T);
	cout << endl << endl;
	cout << "level_order_line" << endl;
	level_order_line(T);
	cout << endl << endl;

	cout << "level_order_s" << endl;
	level_order_s(T);
	cout << endl << endl;

	cout << "height_recur" << endl;
	cout << height_recur(T) << endl;
	cout << "height_iter" << endl;
	cout << height_iter(T);
	cout << endl << endl;

	cout << "width" << endl;
	cout << width(T);
	cout << endl << endl;

	// if (true == is_balanced1(T)) {
	if (true == is_balanced2(T)) {
		cout << "is balanced" << endl << endl;
	} else {
		cout << "is not balanced" << endl << endl;
	}

	if (true == is_equal(T, T)) {
		cout << "is equal" << endl << endl;
	} else {
		cout << "is not equal" << endl << endl;
	}

	/*
	Node *T1 = mirror(T);
	// if (true == is_symmetrical(T)) {
	if (true == is_symmetrical(T, T1)) {
		cout << "is symmetrical" << endl << endl;
	} else {
		cout << "is not symmetrical" << endl << endl;
	}
	*/

	Node *T2 = T->lchild;
	if (true == has_subtree(T, T2)) {
		cout << "1 has 2" << endl << endl;
	} else {
		cout << "1 has no 2" << endl << endl;
	}

	if (true == is_perfect_tree(T)) {
		cout << "is pefect tree" << endl << endl;
	} else {
		cout << "is not perfect tree" << endl << endl;
	}

	if (true == is_complete_tree(T)) {
		cout << "is complete tree" << endl << endl;
	} else {
		cout << "is not complete tree" << endl << endl;
	}

	Node *post = build_tree(0, 8, 0, 8);
	post_order_iter(post);
	cout << endl << endl;

	int B[] = {2, 1, 4, 6, 5, 7, 9, 8, 3};
	if (true == verify_sequence_of_BST(B, 9)) {
		cout << "is valid BST sequence" << endl << endl;
	} else {
		cout << "is not valid BST sequence" << endl << endl;
	}

	cout << "find path in a tree with confirmed sum" << endl;
	find_path(T, 27);
	cout << endl;

	/*
	cout << "convert a tree into a link list" << endl;
	Node *convert_ret = convert(T);
	while (convert_ret != NULL) {
		cout << convert_ret->value << ' ';
		convert_ret = convert_ret->rchild;
	}
	cout << endl << endl;
	*/

	cout << "2th node's value" << endl;
	Node *kth_ret = kth_node(T, 2);
	cout << kth_ret->value << endl << endl;

	cout << "max distance" << endl;
	RESULT max_ret = get_max_distance(T);
	cout << max_ret.max_distance << endl << endl;

	cout << "common parent of node1 and node2" << endl;
	Node *node1 = T->lchild, *node2 = T->rchild;
	cout << "node1: " << node1->value << ", node2: " << node2->value << endl;
	Node *common_ret = common_parent1(T, node1, node2);
	// Node *common_ret = common_parent2(T, node1, node2);
	cout << common_ret->value << endl << endl;

	cout << "find a path to leaf_node" << endl;
	Node *leaf = T->lchild->rchild;
	vector<Node *> path;
	if (true == find_leaf_node(T, leaf, path)) {
		cout << "path is" << endl;
		for (int i = 0; i < path.size(); ++i) {
			cout << path[i]->value << ' ';
		}
		cout << endl << endl;
	} else {
		cout << "no path" << endl << endl;
	}

	/*
	flatten(T);
	pre_order_recur(T);
	cout << endl;
	in_order_recur(T);
	cout << endl << endl;
	*/

	if (true == is_valid_BST(T)) {
		cout << "is valid bst" << endl << endl;
	} else {
		cout << "is not valid bst" << endl << endl;
	}

	return 0;
}
