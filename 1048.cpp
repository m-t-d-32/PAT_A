/*
	1048 Find Coins （25 分）
	Eva loves to collect coins from all over the universe, including some other planets like Mars. One day she visited a universal shopping mall which could accept all kinds of coins as payments. However, there was a special requirement of the payment: for each bill, she could only use exactly two coins to pay the exact amount. Since she has as many as 10
	​5
	​​  coins with her, she definitely needs your help. You are supposed to tell her, for any given amount of money, whether or not she can find two coins to pay for it.

	Input Specification:
	Each input file contains one test case. For each case, the first line contains 2 positive numbers: N (≤10
	​5
	​​ , the total number of coins) and M (≤10
	​3
	​​ , the amount of money Eva has to pay). The second line contains N face values of the coins, which are all positive numbers no more than 500. All the numbers in a line are separated by a space.

	Output Specification:
	For each test case, print in one line the two face values V
	​1
	​​  and V
	​2
	​​  (separated by a space) such that V
	​1
	​​ +V
	​2
	​​ =M and V
	​1
	​​ ≤V
	​2
	​​ . If such a solution is not unique, output the one with the smallest V
	​1
	​​ . If there is no solution, output No Solution instead.

	Sample Input 1:
	8 15
	1 2 8 7 2 4 11 15
	Sample Output 1:
	4 11
	Sample Input 2:
	7 14
	1 8 7 2 4 11 15
	Sample Output 2:
	No Solution
*/

#include <cstdio>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
	//输入
	int n, sum;
	scanf("%d%d", &n, &sum);
	int * coins = new int[n];
	for (int i = 0; i < n; ++i){
		scanf("%d", &coins[i]);
	}
	//排序所有硬币价值
	sort(coins, coins + n);
	//双指针，首先分别指向第一个数和最后一个数
	int begin = 0, end = n - 1;
	while (begin < end){
		//比较两个指针对应的数的和与要求的和的大小
		int temp_sum = coins[begin] + coins[end];
		if (temp_sum < sum){	
			//如果要求的和大，移动左边指针，使得和变大
			++begin;
		}
		else if (temp_sum == sum){	
			//如果两者相等则跳出循环
			break;
		}
		else {	
			//如果要求的和小，移动右边指针，使得和变小
			--end;
		}
	}
	if (begin != end){	
		//输出结果
		printf("%d %d\n", coins[begin], coins[end]);
	}
	else {	
		//如果两个指针碰撞了，说明没找到
		printf("No Solution\n");
	}
	return 0;
}