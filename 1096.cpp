/*
	1096 Consecutive Factors （20 分）
	Among all the factors of a positive integer N, there may exist several consecutive numbers. For example, 630 can be factored as 3×5×6×7, where 5, 6, and 7 are the three consecutive numbers. Now given any positive N, you are supposed to find the maximum number of consecutive factors, and list the smallest sequence of the consecutive factors.

	Input Specification:
	Each input file contains one test case, which gives the integer N (1<N<2
	​31
	​​ ).

	Output Specification:
	For each test case, print in the first line the maximum number of consecutive factors. Then in the second line, print the smallest sequence of the consecutive factors in the format factor[1]*factor[2]*...*factor[k], where the factors are listed in increasing order, and 1 is NOT included.

	Sample Input:
	630
	Sample Output:
	3
	5*6*7
*/

#include <cstdio>
#include <cmath>
#include <set>
using namespace std;

set<int> get_factors(int n){
	//获取数n的所有质因子（不包括本身）
	int max_num = sqrt(n) + 1;	//由于不包括本身，所以到sqrt(n)就可以了
	set<int> results;	//用set保存，避免重复元素
	for (int i = 2; i <= max_num; ++i){
		if (n % i == 0){
			results.insert(i);
		}
	}
	return results;
}
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);

	//获取质因子
	set<int> factors = get_factors(n);
	//初始化最大长度和最长序列的起始下标
	int max_length = 0, max_index = -1;
	//遍历所有质因子，获得以每一个质因子为起始的连续因数序列的长度
	for (set<int>::iterator it = factors.begin(); it != factors.end(); ++it){
		int factor = *it;
		int now_length = 0;
		int now_n = n;
		while (factor <= now_n){
			//连续除从factor开始的元素，直到除不尽为止
			if (now_n % factor == 0){
				now_n /= factor;
				++now_length;
				++factor;
			}
			else {
				break;
			}
		}
		if (now_length > max_length){
			//如果长度大于原先的最长长度，更新最长长度和起始下标
			max_length = now_length;
			max_index = *it;
		}
	}
	if (max_index == -1){
		//如果是质数，连续因数只有一个且是本身
		max_index = n;
		max_length = 1;
	}

	//输出
	printf("%d\n", max_length);
	for (int i = 0; i < max_length - 1; ++i){
		printf("%d*", max_index + i);
	}
	printf("%d\n", max_index + max_length - 1);
	return 0;
}