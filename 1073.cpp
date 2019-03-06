/*
	1073 Scientific Notation （20 分）
	Scientific notation is the way that scientists easily handle very large numbers or very small numbers. The notation matches the regular expression [+-][1-9].[0-9]+E[+-][0-9]+ which means that the integer portion has exactly one digit, there is at least one digit in the fractional portion, and the number and its exponent's signs are always provided even when they are positive.

	Now given a real number A in scientific notation, you are supposed to print A in the conventional notation while keeping all the significant figures.

	Input Specification:
	Each input contains one test case. For each case, there is one line containing the real number A in scientific notation. The number is no more than 9999 bytes in length and the exponent's absolute value is no more than 9999.

	Output Specification:
	For each test case, print in one line the input number A in the conventional notation, with all the significant figures kept, including trailing zeros.

	Sample Input 1:
	+1.23400E-03
	Sample Output 1:
	0.00123400
	Sample Input 2:
	-1.2E+10
	Sample Output 2:
	-12000000000
*/

#include <cstdio>
#include <cstring>

void print_raw(char * number){
	//输出原始数字
	
	char base_symbol = *number ++;	//基数的正负号
	char before_dot = *number ++;	//小数点前面的一位数
	++number; //小数点
	char after_dot[100000];	//小数点后面的若干位基数
	int counter_after = 0;
	while (*number != 'E'){
		//从小数点后面一位数开始读到'E'停止
		after_dot[counter_after ++] = *number ++;	
	}
	++number; //字母E
	char radix_symbol = *number ++;	//指数的正负号
	int radix;
	sscanf(number, "%d", &radix);	//指数的若干位
	
	if (base_symbol == '-'){	
		//输出符号（正号不用输出）
		printf("-");
	}
	if (radix_symbol == '-'){
		//指数是负号，则一定输出0-1之间的数
		
		//先输出若干个0
		printf("0.");
		for (int i = 0; i < radix - 1; ++i){
			printf("0");
		}
		//再输出原数
		printf("%c%s\n", before_dot, after_dot);
	}
	else if (radix_symbol == '+'){
		//指数是正号，分成两种情况
		printf("%c", before_dot);
		int max_len = strlen(after_dot);
		if (max_len > radix){
			//小数点后面的数字大于指数，则输出带点号的浮点数
			
			//点号前面的数
			for (int i = 0; i < radix; ++i){
				printf("%c", after_dot[i]);
			}
			printf(".");
			//点号后面的数
			for (int i = radix; i < max_len; ++i){
				printf("%c", after_dot[i]);
			}
		}
		else {
			//小数点后面的数字不大于指数，则输出补0的整数
			
			//输出原数
			for (int i = 0; i < max_len; ++i){
				printf("%c", after_dot[i]);
			}
			
			//后面补若干个0
			for (int i = max_len; i < radix; ++i){
				printf("0", after_dot[i]);
			}
		}
		printf("\n");
	}
}
		
int main(){
	char number[200000];
	//输入
	scanf("%s", number);
	//输出
	print_raw(number);
	return 0;
}