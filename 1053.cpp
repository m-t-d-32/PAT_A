/*
	1053 Path of Equal Weight （30 分）
	Given a non-empty tree with root R, and with weight W
	​i
	​​  assigned to each tree node T
	​i
	​​ . The weight of a path from R to L is defined to be the sum of the weights of all the nodes along the path from R to any leaf node L.

	Now given any weighted tree, you are supposed to find all the paths with their weights equal to a given number. For example, let's consider the tree showed in the following figure: for each node, the upper number is the node ID which is a two-digit number, and the lower number is the weight of that node. Suppose that the given number is 24, then there exists 4 different paths which have the same given weight: {10 5 2 7}, {10 4 10}, {10 3 3 6 2} and {10 3 3 6 2}, which correspond to the red edges in the figure.



	Input Specification:
	Each input file contains one test case. Each case starts with a line containing 0<N≤100, the number of nodes in a tree, M (<N), the number of non-leaf nodes, and 0<S<2
	​30
	​​ , the given weight number. The next line contains N positive numbers where W
	​i
	​​  (<1000) corresponds to the tree node T
	​i
	​​ . Then M lines follow, each in the format:

	ID K ID[1] ID[2] ... ID[K]
	where ID is a two-digit number representing a given non-leaf node, K is the number of its children, followed by a sequence of two-digit ID's of its children. For the sake of simplicity, let us fix the root ID to be 00.

	Output Specification:
	For each test case, print all the paths with weight S in non-increasing order. Each path occupies a line with printed weights from the root to the leaf in order. All the numbers must be separated by a space with no extra space at the end of the line.

	Note: sequence {A
	​1
	​​ ,A
	​2
	​​ ,⋯,A
	​n
	​​ } is said to be greater than sequence {B
	​1
	​​ ,B
	​2
	​​ ,⋯,B
	​m
	​​ } if there exists 1≤k<min{n,m} such that A
	​i
	​​ =B
	​i
	​​  for i=1,⋯,k, and A
	​k+1
	​​ >B
	​k+1
	​​ .

	Sample Input:
	20 9 24
	10 2 4 3 5 10 2 18 9 7 2 2 1 3 12 1 8 6 2 2
	00 4 01 02 03 04
	02 1 05
	04 2 06 07
	03 3 11 12 13
	06 1 09
	07 2 08 10
	16 1 15
	13 3 14 16 17
	17 2 18 19
	Sample Output:
	10 5 2 7
	10 4 10
	10 3 3 6 2
	10 3 3 6 2
	Special thanks to Zhang Yuan and Yang Han for their contribution to the judge's data.
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

//用数组存一棵树，数组下标表示某个节点的位置

struct TreeNode{	//树节点
	int value;	//权值
	vector<int> childs;	//孩子节点的下标
};

vector<int> now_seq;	//现在的路径经过的树节点的下标
int now_count, need_result;	//现在的路径经过的树节点的权值和，需要的权值和
vector<vector<int> > results;	//存放所有的符合要求的路径
TreeNode * tree;	//树节点数组

void print_result(const vector<int> & vec){	
	//输出一条路径
	for (int i = 0; i < vec.size() - 1; ++i){
		printf("%d ", vec[i]);
	}
	printf("%d\n", vec.back());
}

bool get_less(const vector<int> & v1, const vector<int> & v2){	
	//路径按要求排序：前面节点权值大路径放在前
	for (int i = 0; i < v1.size() && i < v2.size(); ++i){
		if (v1[i] != v2[i]){
			return v1[i] > v2[i];
		}
	}
	return false;
}

void dfs(int now_node){
	//深度优先搜索
	
	//尝试当前节点：将节点权值加入当前权值，将节点存入当前路径
	now_count += tree[now_node].value;
	now_seq.push_back(tree[now_node].value);
	
	//验证是否到达叶子节点，当前权值是否已经等于或大于要求权值
	if (tree[now_node].childs.empty()){
		if (now_count == need_result){
			results.push_back(now_seq);	//如果符合，则记录这条符合要求的路径
		}
	}
	else if (now_count < need_result){
		for (int i = 0; i < tree[now_node].childs.size(); ++i){
			dfs(tree[now_node].childs[i]);
		}
	}
	
	//回溯：撤销当前加入节点操作
	now_count -= tree[now_node].value;
	now_seq.pop_back();
}

int main(){
	//输入
	int all_nodes, all_inners;
	scanf("%d%d", &all_nodes, &all_inners);
	tree = new TreeNode[all_nodes];
	scanf("%d", &need_result);
	for (int i = 0; i < all_nodes; ++i){
		scanf("%d", &tree[i].value);
	}
	for (int i = 0; i < all_inners; ++i){
		int now_node, child_count;
		scanf("%d%d", &now_node, &child_count);
		for (int i = 0; i < child_count; ++i){
			int temp;
			scanf("%d", &temp);
			tree[now_node].childs.push_back(temp);
		}
	}
	//深度优先搜索
	dfs(0);
	//按要求排序
	sort(results.begin(), results.end(), get_less);
	//输出所有符合要求的路径
	for (int i = 0; i < results.size(); ++i){
		print_result(results[i]);
	}
	return 0;
}
	