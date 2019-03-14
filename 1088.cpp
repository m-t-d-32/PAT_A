/*
	1088 Rational Arithmetic （20 分)
	For two rational numbers, your task is to implement the basic arithmetics, that is, to calculate their sum, difference, product and quotient.

	Input Specification:
	Each input file contains one test case, which gives in one line the two rational numbers in the format a1/b1 a2/b2. The numerators and the denominators are all in the range of long int. If there is a negative sign, it must appear only in front of the numerator. The denominators are guaranteed to be non-zero numbers.

	Output Specification:
	For each test case, print in 4 lines the sum, difference, product and quotient of the two rational numbers, respectively. The format of each line is number1 operator number2 = result. Notice that all the rational numbers must be in their simplest form k a/b, where k is the integer part, and a/b is the simplest fraction part. If the number is negative, it must be included in a pair of parentheses. If the denominator in the division is zero, output Inf as the result. It is guaranteed that all the output integers are in the range of long int.

	Sample Input 1:
	2/3 -4/2
	Sample Output 1:
	2/3 + (-2) = (-1 1/3)
	2/3 - (-2) = 2 2/3
	2/3 * (-2) = (-1 1/3)
	2/3 / (-2) = (-1/3)
	Sample Input 2:
	5/3 0/6
	Sample Output 2:
	1 2/3 + 0 = 1 2/3
	1 2/3 - 0 = 1 2/3
	1 2/3 * 0 = 0
	1 2/3 / 0 = Inf
*/

#include <cstdio>
#include <algorithm>
using namespace std;

struct Fraction{
	//分数类
	long long upnum, downnum;
	void simplify(){
		//分数约分
		long long common_factor;
		//找到最大公约数
		if (upnum < 0){
			common_factor = get_factor(-upnum, downnum);
		}
		else {
			common_factor = get_factor(upnum, downnum);
		}
		//约分
		upnum /= common_factor;
		downnum /= common_factor;
	}
	void print(){
		if (upnum == 0){
			//如果是0直接输出
			printf("0");
		}
		else {
			//约分成最简假分数
			simplify();
			long long temp_up, temp_down;
			if (upnum < 0){
				//如果是负数输出括号和负号，变成正数
				printf("(-");
				temp_up = -upnum;
			}
			else {
				temp_up = upnum;
			}
			if (temp_up / downnum >= 1){
				//整数部分输出
				printf("%lld", temp_up / downnum);
				if (temp_up % downnum != 0){
					printf(" ");
				}
			}
			if (temp_up % downnum != 0){
				//分数部分输出
				printf("%lld/%lld", temp_up % downnum, downnum);
			}
			if (upnum < 0){
				//补齐右半边括号
				printf(")");
			}
		}
	}
	void operator + (Fraction frac){
		//重载加号，计算并输出
		
		//找到两个分母的最小公倍数
		long long common_multi = get_multi(downnum, frac.downnum);
		Fraction result;
		//通分相加
		result.downnum = common_multi;
		result.upnum = common_multi / downnum * upnum + common_multi / frac.downnum * frac.upnum;
		//输出
		result.print();
	}
	void operator - (Fraction frac){
		//重载减号，计算并输出
		//直接把减数取相反数，两者相加
		frac.upnum = -frac.upnum;
		(*this) + frac;
	}
	void operator * (Fraction frac){
		//重载乘号，计算并输出
		
		//分子乘分子，分母乘分母
		Fraction result;
		result.downnum = downnum * frac.downnum;
		result.upnum = upnum * frac.upnum;
		//输出
		result.print();
	}
	void operator / (Fraction frac){
		//重载除号，计算并输出
		if (frac.upnum == 0){
			//如果除数是0输出Inf
			printf("Inf");
		}
		else {
			if (frac.upnum < 0){
				//如果除数是负数，倒置前取分子分母的相反数（保证分子是负数）
				frac.upnum = -frac.upnum;
				frac.downnum = -frac.downnum;
			}
			//倒置除数的分子分母，然后和被除数相乘
			swap(frac.upnum, frac.downnum);
			(*this) * frac;
		}
	}	
	long long get_factor(long long a, long long b){
		//最大公约数：辗转相除
		while (a % b != 0){
			a %= b;
			swap(a, b);
		}
		return b;
	}
	long long get_multi(long long a, long long b){
		//最小公倍数：乘积除以最大公约数
		return a * b / get_factor(a, b);
	}
};
int main(){
	Fraction a, b;
	//输入
	scanf("%lld/%lld", &a.upnum, &a.downnum);
	scanf("%lld/%lld", &b.upnum, &b.downnum);
	//计算以及输出
	a.print(); printf(" + "); b.print(); printf(" = "); a + b; printf("\n");
	a.print(); printf(" - "); b.print(); printf(" = "); a - b; printf("\n");
	a.print(); printf(" * "); b.print(); printf(" = "); a * b; printf("\n");
	a.print(); printf(" / "); b.print(); printf(" = "); a / b; printf("\n");
	return 0;
}
	