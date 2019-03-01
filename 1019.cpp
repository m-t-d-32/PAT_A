/*
	1019 General Palindromic Number （20 分）
	A number that will be the same when it is written forwards or backwards is known as a Palindromic Number. For example, 1234321 is a palindromic number. All single digit numbers are palindromic numbers.

	Although palindromic numbers are most often considered in the decimal system, the concept of palindromicity can be applied to the natural numbers in any numeral system. Consider a number N>0 in base b≥2, where it is written in standard notation with k+1 digits a
	​i
	​​  as ∑
	​i=0
	​k
	​​ (a
	​i
	​​ b
	​i
	​​ ). Here, as usual, 0≤a
	​i
	​​ <b for all i and a
	​k
	​​  is non-zero. Then N is palindromic if and only if a
	​i
	​​ =a
	​k−i
	​​  for all i. Zero is written 0 in any base and is also palindromic by definition.

	Given any positive decimal integer N and a base b, you are supposed to tell if N is a palindromic number in base b.

	Input Specification:
	Each input file contains one test case. Each case consists of two positive numbers N and b, where 0<N≤10
	​9
	​​  is the decimal number and 2≤b≤10
	​9
	​​  is the base. The numbers are separated by a space.

	Output Specification:
	For each test case, first print in one line Yes if N is a palindromic number in base b, or No if not. Then in the next line, print N as the number in base b in the form "a
	​k
	​​  a
	​k−1
	​​  ... a
	​0
	​​ ". Notice that there must be no extra space at the end of output.

	Sample Input 1:
	27 2
	Sample Output 1:
	Yes
	1 1 0 1 1
	Sample Input 2:
	121 5
	Sample Output 2:
	No
	4 4 1
*/

#include <cstdio>
#include <string>
#include <stack>
#include <vector>
using namespace std;

vector<int> get_from_decimal(int number, int radix){
	//将十进制数转化为任意形式（数组中的每个元素表示一个数位）
	stack<int> result_conv;
	while (number != 0){
		//倒序进栈
		result_conv.push(number % radix);
		number /= radix;
	}
	vector<int> result;
	while (!result_conv.empty()){
		//出栈正序
		result.push_back(result_conv.top());
		result_conv.pop();
	}
	return result;
}
bool judge_palin(vector<int> & number){
	//判断是否为回文数
	for (int i = 0; i < number.size() / 2; ++i){
		if (number[i] != number[number.size() - i - 1]){
			return false;
		}
	}
	return true;
}
void print_by_spc(vector<int> & s){
	//格式输出
	if (s.size() > 0){
		for (int i = 0; i < s.size() - 1; ++i){
			printf("%d ", s[i]);
		}
		printf("%d\n", s[s.size() - 1]);
	}
}
int main(int argc, char const *argv[])
{
	int number, radix;
	scanf("%d %d", &number, &radix);	//读取输入
	vector<int> conv_number = get_from_decimal(number, radix);
	bool palin = judge_palin(conv_number);
	if (palin){
		printf("Yes\n");
	}
	else{
		printf("No\n");
	}
	print_by_spc(conv_number);
	return 0;
}
