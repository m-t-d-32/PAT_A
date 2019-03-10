/*
	1081 Rational Sum （20 分）
	Given N rational numbers in the form numerator/denominator, you are supposed to calculate their sum.

	Input Specification:
	Each input file contains one test case. Each case starts with a positive integer N (≤100), followed in the next line N rational numbers a1/b1 a2/b2 ... where all the numerators and denominators are in the range of long int. If there is a negative number, then the sign must appear in front of the numerator.

	Output Specification:
	For each test case, output the sum in the simplest form integer numerator/denominator where integer is the integer part of the sum, numerator < denominator, and the numerator and the denominator have no common factor. You must output only the fractional part if the integer part is 0.

	Sample Input 1:
	5
	2/5 4/15 1/30 -2/60 8/3
	Sample Output 1:
	3 1/3
	Sample Input 2:
	2
	4/3 2/3
	Sample Output 2:
	2
	Sample Input 3:
	3
	1/3 -1/6 1/8
	Sample Output 3:
	7/24
*/

#include <cstdio>

struct Fraction{
	//分数类，值相当于整数部分加分子/分母，并且保证分子，分母都大于0，整数部分可以小于0
	//例如分数-1又2/3在这里表示为-2又（正）1/3，即整数部分为-2，分子为1，分母为3
	//所有需要用到的数设置为long long, 并及时约分化简，不会溢出
	long long numerator, denominator;	//分子和分母
	long long integer;	//（带分数的）整数部分

	Fraction(){	//初始化一个分数0
		numerator = integer = 0;
		denominator = 1;
	}
	Fraction operator + (const Fraction & frac){	
		Fraction result;
		//结果的分母是两个分数分母的最小公倍数
		result.denominator = get_common_multiple(denominator, frac.denominator);
		//结果的分子是两个分数的分子乘以因数，然后再相加
		result.numerator = result.denominator / denominator * numerator \
			+ result.denominator / frac.denominator * frac.numerator;
		//结果的整数部分等于两个分数整数部分的和，再加上约分出的整数部分
		result.integer = result.numerator / result.denominator + integer + frac.integer;
		//约分后，分子变成整除分母的结果
		result.numerator = result.numerator % result.denominator;
		return result;
	}
	void simplify(){
		//化简，包括约分和将分子分母变成整数两部分
		if (numerator == 0){
			//如果分子等于0，不需要化简，可将分母变成1（防止后面溢出）
			denominator = 1;
			return;
		}
		else if (numerator < 0){
			//如果分子小于0，将分子变成正数，多加的数在整数部分上面减去
			long long adds = - numerator / denominator + 1;
			integer = -adds;
			numerator = adds * denominator + numerator;
		}
		//约分
		long long divides = get_common_divide(numerator, denominator);
		numerator /= divides;
		denominator /= divides;
		//如果分数部分是假分数，变成真分数，多出的数加在整数部分（这里分子分母一定非负）
		integer += numerator / denominator;
		numerator %= denominator;
	}
	void print(){
		//输出当前的分数：如果整数部分是负数，则分数部分也变为负数，多减的数加在整数部分
		//例如分数-2又（正）1/3变回-1又2/3

		long long _numerator = numerator, _denominator = denominator;
		long long _integer = integer;
		if (_numerator == 0){
			//如果分子是0，只需要输出整数部分
			if (_integer == 0){
				printf("0");
			}
			else {
				printf("%lld", _integer);
			}			
		}
		else{
			if (_integer < 0){
				//如果整数部分小于0，则在分子上减去一个1（这里保证分数部分是真分数）
				_numerator = _denominator - _numerator;
				++_integer;
			}
			if (_integer != 0){
				//如果整数部分是0，只需要输出分数部分
				printf("%lld ", _integer);
			}
			printf("%lld/%lld", _numerator, _denominator);		
		}
	}
private:
	long long get_common_multiple(long long x, long long y){
		//计算最小公倍数：相当于两个数乘积除以最大公约数
		return x * y / get_common_divide(x, y);
	}
	long long get_common_divide(long long x, long long y){
		//计算最大公约数：辗转相除法
		while (x % y != 0){
			x = x % y;
			//交换x和y
			long long temp = x;
			x = y;
			y = temp;
		}
		return y;
	}
};

int main(int argc, char const *argv[])
{
	//输入
	int n;
	scanf("%d", &n);
	Fraction * fracs = new Fraction[n];
	Fraction sum;
	for (int i = 0; i < n; ++i){
		scanf("%lld/%lld", &fracs[i].numerator, &fracs[i].denominator);
		fracs[i].simplify();	//先化简输入的分数（防止溢出）
		sum = sum + fracs[i];
		sum.simplify();	//加完以后再化简一次
	}
	//输出
	sum.print();
	return 0;
}