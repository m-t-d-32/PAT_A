/*
	1064 Complete Binary Search Tree （30 分）
	A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

	The left subtree of a node contains only nodes with keys less than the node's key.
	The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
	Both the left and right subtrees must also be binary search trees.
	A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the bottom level, which is filled from left to right.

	Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is required that the tree must also be a CBT. You are supposed to output the level order traversal sequence of this BST.

	Input Specification:
	Each input file contains one test case. For each case, the first line contains a positive integer N (≤1000). Then N distinct non-negative integer keys are given in the next line. All the numbers in a line are separated by a space and are no greater than 2000.

	Output Specification:
	For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

	Sample Input:
	10
	1 2 3 4 5 6 7 8 9 0
	Sample Output:
	6 3 8 1 5 7 9 0 2 4
*/

#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int process_index = 0;	//目前访问到原数组的第几个数了（每个数只访问一次）
int process_all = 0;	//一共有几个数

void get_cbt(const int * src, int now_index, int * dest){
	//完全二叉树可以用从0开始的数组表示，参数dest存放最终结果

	//由于二叉树中序遍历按序，则排好序后中序遍历时放入，即可构建二叉树
	//（中序遍历的逆过程）
	if (now_index >= process_all){
		//如果超出范围，返回
		return;
	}
	else {
		get_cbt(src, now_index * 2 + 1, dest);	//左孩子节点

		//中序遍历的当前节点存入原数组的当前对应的数
		//原数组标号前移，指向下一个数
		dest[now_index] = src[process_index ++];

		get_cbt(src, now_index * 2 + 2, dest);	//右孩子节点
	}
}

int main(int argc, char const *argv[])
{
	scanf("%d", &process_all);
	int * src = new int[process_all];
	int * result = new int[process_all];
	//读入输入
	for (int i = 0; i < process_all; ++i){
		scanf("%d", &src[i]);
	}
	//排序原数组
	sort(src, src + process_all);
	//获得完全二叉树对应的数组
	get_cbt(src, 0, result);
	//输出
	for (int i = 0; i < process_all; ++i){
		printf("%d", result[i]);
		if (i != process_all - 1){
			printf(" ");
		}
	}
	return 0;
}