/*
	1066 Root of AVL Tree （25 分）
	An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Figures 1-4 illustrate the rotation rules.




	Now given a sequence of _insertions, you are supposed to tell the root of the resulting AVL tree.
	Input Specification:
	Each input file contains one test case. For each case, the first line contains a positive integer N (≤20) which is the total number of keys to be _inserted. Then N distinct integer keys are given in the next line. All the numbers in a line are separated by a space.

	Output Specification:
	For each test case, print the root of the resulting AVL tree in one line.

	Sample Input 1:
	5
	88 70 61 96 120
	Sample Output 1:
	70
	Sample Input 2:
	7
	88 70 61 96 120 90 65
	Sample Output 2:
	88
*/

#include <cstdio>

struct TreeNode {
	//树节点
	int value, height;
	TreeNode * left, * right;
	TreeNode(int x):value(x), height(1), left(NULL), right(NULL){}
};

struct AVL {
	//AVL树
	TreeNode * m_root;
	AVL():m_root(NULL){}
	void insert(int x){
		m_root = _insert(m_root, x);
	}
private:
	TreeNode * _insert(TreeNode * root, int x){
		//递归插入
		if (!root){
			root = new TreeNode(x);
		}
		else if (x > root->value){
			root->right = _insert(root->right, x);
		}
		else if (x < root->value){
			root->left = _insert(root->left, x);
		}
		int left_height = root->left ? root->left->height : 0;
		int right_height = root->right ? root->right->height : 0;
		root->height = left_height > right_height ? left_height + 1 : right_height + 1;
		if (left_height - right_height >= 2){
			//左边高，需要调整
			int left_left_height = root->left->left ? root->left->left->height : 0;
			int left_right_height = root->left->right ? root->left->right->height : 0;
			if (left_left_height > left_right_height){
				//右旋一次
				root = right_rotate(root);
			}
			else {
				//左旋一次，右旋一次
				root->left = left_rotate(root->left);
				root = right_rotate(root);
			}
		}
		else if (right_height - left_height >= 2){
			//右边高，需要调整
			int right_left_height = root->right->left ? root->right->left->height : 0;
			int right_right_height = root->right->right ? root->right->right->height : 0;
			if (right_right_height > right_left_height){
				//左旋一次
				root = left_rotate(root);
			}
			else {
				//右旋一次，左旋一次
				root->right = right_rotate(root->right);
				root = left_rotate(root);
			}
		}
		return root;
	}
	TreeNode * right_rotate(TreeNode * future_right){
		//旋转动作（先旋转将来的孩子节点，再旋转将来的根节点）
		TreeNode * future_root = future_right->left;
		future_right->left = future_root->right;
		future_root->right = future_right;

		//重新计算树高
		int left_height = future_right->left ? future_right->left->height : 0;
		int right_height = future_right->right ? future_right->right->height : 0;
		future_right->height = left_height > right_height ? left_height + 1 : right_height + 1;
		left_height = future_root->left ? future_root->left->height : 0;
		right_height = future_root->right ? future_root->right->height : 0;
		future_root->height = left_height > right_height ? left_height + 1 : right_height + 1;

		return future_root;
	}
	TreeNode * left_rotate(TreeNode * future_left){
		//旋转动作（先旋转将来的孩子节点，再旋转将来的根节点）
		TreeNode * future_root = future_left->right;
		future_left->right = future_root->left;
		future_root->left = future_left;

		//重新计算树高
		int left_height = future_left->left ? future_left->left->height : 0;
		int right_height = future_left->right ? future_left->right->height : 0;
		future_left->height = left_height > right_height ? left_height + 1 : right_height + 1;
		left_height = future_root->left ? future_root->left->height : 0;
		right_height = future_root->right ? future_root->right->height : 0;
		future_root->height = left_height > right_height ? left_height + 1 : right_height + 1;

		return future_root;
	}
};

int main(int argc, char const *argv[]) {
	AVL avltree;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i){
		//插入
		int temp;
		scanf("%d", &temp);
		avltree.insert(temp);
	}
	//输出
	printf("%d\n", avltree.m_root->value);
	return 0;
}
