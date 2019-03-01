/*
	1020 Tree Traversals （25 分）
	Suppose that all the keys in a binary tree are distinct positive integers. Given the postorder and inorder traversal sequences, you are supposed to output the level order traversal sequence of the corresponding binary tree.

	Input Specification:
	Each input file contains one test case. For each case, the first line gives a positive integer N (≤30), the total number of nodes in the binary tree. The second line gives the postorder sequence and the third line gives the inorder sequence. All the numbers in a line are separated by a space.

	Output Specification:
	For each test case, print in one line the level order traversal sequence of the corresponding binary tree. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

	Sample Input:
	7
	2 3 1 5 7 6 4
	1 2 3 4 5 6 7
	Sample Output:
	4 1 6 3 5 7 2
*/

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode{	//节点结构
	int value;
	TreeNode *left, *right;
	TreeNode(int x):value(x), left(NULL), right(NULL){}
};
TreeNode * get_from_traversals(vector<int> & postorders, vector<int> & inorders){
	//由后序遍历和中序遍历递归构建树
	if (postorders.size()){
		int middle = postorders.back();	//后序遍历的最后一个元素一定是当前树的树根
		vector<int> post_left, post_right;
		vector<int> in_left, in_right;
		int post_begin = 0, in_begin = 0;

		//以树根为轴将树分成左子树和右子树
		while (inorders[in_begin] != middle){
			in_left.push_back(inorders[in_begin]);
			post_left.push_back(postorders[post_begin]);
			++in_begin; ++post_begin;
		}
		++in_begin;
		while (in_begin < inorders.size()){
			in_right.push_back(inorders[in_begin]);
			post_right.push_back(postorders[post_begin]);
			++in_begin; ++post_begin;
		}

		//递归调用，返回当前的新树
		TreeNode * root = new TreeNode(middle);
		root->left = get_from_traversals(post_left, in_left);
		root->right = get_from_traversals(post_right, in_right);
		return root;
	}
	else{
		//返回空树
		return NULL;
	}
}
void print_by_level(TreeNode * root){
	//层序遍历
	queue<TreeNode *> open_queue;
	open_queue.push(root);
	while (true){
		//宽度优先搜索算法（BFS）
		TreeNode * temp = open_queue.front();
		open_queue.pop();
		printf("%d", temp->value);

		if (temp->left){
			open_queue.push(temp->left);
		}
		if (temp->right){
			open_queue.push(temp->right);
		}
		//如果是最后一个元素，则不输出空格
		if (open_queue.empty()){
			break;
		}
		printf(" ");
	}
}
int main(int argc, char const *argv[]) {
	int n;
	scanf("%d", &n);
	vector<int> postorders, inorders;
	//读取输入
	for (int i = 0; i < n; ++i){
		int temp;
		scanf("%d", &temp);
		postorders.push_back(temp);
	}
	for (int i = 0; i < n; ++i){
		int temp;
		scanf("%d", &temp);
		inorders.push_back(temp);
	}
	//构建树
	TreeNode * root = get_from_traversals(postorders, inorders);
	//层序遍历树
	print_by_level(root);
	return 0;
}
