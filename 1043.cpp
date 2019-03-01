/*
	1043 Is It a Binary Search Tree （25 分）
	A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

	The left subtree of a node contains only nodes with keys less than the node's key.
	The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
	Both the left and right subtrees must also be binary search trees.
	If we swap the left and right subtrees of every node, then the resulting tree is called the Mirror Image of a BST.

	Now given a sequence of integer keys, you are supposed to tell if it is the preorder traversal sequence of a BST or the mirror image of a BST.

	Input Specification:
	Each input file contains one test case. For each case, the first line contains a positive integer N (≤1000). Then N integer keys are given in the next line. All the numbers in a line are separated by a space.

	Output Specification:
	For each test case, first print in a line YES if the sequence is the preorder traversal sequence of a BST or the mirror image of a BST, or NO if not. Then if the answer is YES, print in the next line the postorder traversal sequence of that tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

	Sample Input 1:
	7
	8 6 5 7 10 8 11
	Sample Output 1:
	YES
	5 7 6 8 11 10 8
	Sample Input 2:
	7
	8 10 11 8 6 7 5
	Sample Output 2:
	YES
	11 8 10 7 5 6 8
	Sample Input 3:
	7
	8 6 8 5 10 9 11
	Sample Output 3:
	NO
*/

#include <cstdio>
#include <functional>
#include <algorithm>
using namespace std;

struct TreeNode{
	int value;
	TreeNode *left, *right;
};

typedef struct _BadTree{} BadTree;
TreeNode * result_tree;

template <class Compare>
TreeNode * get_tree(int * array, int begin, int end){
	//通过数组，起始下标和终止下标尝试构建一棵二叉树，如果不是二叉树，则抛出异常
	if (end < begin){
		return NULL;
	}
	else {
		int middle = array[begin];	//第一个元素是根节点
		int right_begin = begin + 1;
		Compare compare;
		while (right_begin <= end && compare(array[right_begin], middle)){
			++right_begin;	//找到左子树的终止位置（右子树的起始位置）
		}
		int judge_begin = right_begin;
		while (judge_begin <= end){	
			//检查右子树所有的元素是否都大于根节点，从而判断是否是二叉树
			if (compare(array[judge_begin], middle)){
				throw BadTree();
			}
			++judge_begin;
		}
		TreeNode * p = new TreeNode();

		//递归构建子树
		p->value = middle;
		p->left = get_tree<Compare>(array, begin + 1, right_begin - 1);
		p->right = get_tree<Compare>(array, right_begin, end);
		return p;
	}
}

void print_post_order(const TreeNode * root){
	//后序遍历输出
	if (!root){
		return;
	}
	else {
		//先输出左右子树
		print_post_order(root->left);
		print_post_order(root->right);
		printf("%d", root->value);
		if (result_tree != root){
			//如果是整个树的根节点，则是最后一个元素，不用输出多余空格
			printf(" ");
		}
	}
}
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	int * numbers = new int[n];
	for (int i = 0; i < n; ++i){
		scanf("%d", &numbers[i]);
	}
	try{
		//尝试构建子树：左边都小于根节点，右边都不小于根节点
		TreeNode * std_tree = get_tree<std::less<int> >(numbers, 0, n - 1);	
		printf("YES\n");
		result_tree = std_tree;
		print_post_order(std_tree);	//遍历输出
		return 0;
	}
	catch(BadTree bt){}	//如果没有抛出异常，则构建成功，否则继续

	try {
		//尝试构建旋转子树：左边都不小于根节点，右边都小于根节点
		TreeNode * reversed_tree = get_tree<std::greater_equal<int> >(numbers, 0, n - 1);
		printf("YES\n");
		result_tree = reversed_tree;
		print_post_order(reversed_tree);
		return 0;
	}
	catch(BadTree bt){} //如果没有抛出异常，则构建成功，否则继续

	//如果都抛出了异常，则程序输出NO
	printf("NO\n");
	return 0;
}