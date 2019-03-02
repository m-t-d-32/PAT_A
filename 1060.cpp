/*
	1060 Are They Equal （25 分）
	If a machine can save only 3 significant digits, the float numbers 12300 and 12358.9 are considered equal since they are both saved as 0.123×10
	​5
	​​  with simple chopping. Now given the number of significant digits on a machine and two float numbers, you are supposed to tell if they are treated equal in that machine.

	Input Specification:
	Each input file contains one test case which gives three numbers N, A and B, where N (<100) is the number of significant digits, and A and B are the two float numbers to be compared. Each float number is non-negative, no greater than 10
	​100
	​​ , and that its total digit number is less than 100.

	Output Specification:
	For each test case, print in a line YES if the two numbers are treated equal, and then the number in the standard form 0.d[1]...d[N]*10^k (d[1]>0 unless the number is 0); or NO if they are not treated equal, and then the two numbers in their standard form. All the terms must be separated by a space, with no extra space at the end of a line.

	Note: Simple chopping is assumed without rounding.

	Sample Input 1:
	3 12300 12358.9
	Sample Output 1:
	YES 0.123*10^5
	Sample Input 2:
	3 120 128
	Sample Output 2:
	NO 0.120*10^3 0.128*10^3
*/

#include <cstdio>
#include <cstring>
#include <cctype>

void preprocess(char * num){
	//预处理，消除数前面的多余的0
	char * i = num;
	char result[200] = "0";
	for (; *i && *i == '0'; ++i);	//找到第一个不是0的位置
	if (isdigit(*i)){
		//如果是数字，则将原数替换为用该数字开头的数
		strcpy(result, i);
	}
	else {
		//如果不是数字，则是小数点或者字符串结尾的'\0'（后者说明这个数就是0）
		//则以0开头
		strcat(result, i);
	}
	strcpy(num, result);
}

char * conv(char * num, int n){	//将数字字符串转化成科学记数法表示的字符串
	int num_before_dot = 0;
	if (num[0] == '0'){
		if (strlen(num) > 1 && num[1] == '.'){	//如果是0.开头
			char * i = num + strlen("0.");
			for (; *i && (*i) == '0'; ++i){	//找到第一个不是0的数
				//记录点后面有多少个0，即10的负几次方
				//（例如0.0023是0.23*10^-2）
				--num_before_dot;	
			}
			if (*i){	//如果存在不是0的数
				//用这个不是0的数开头，替换原来的数
				//（例如0.0023变成23）
				strcpy(num, i);	
			}
			else {	//如果没找到，说明这个数是0.0000...，也就是0
				//不替换原来的数，并且乘以10的0次方
				num_before_dot = 0;	
			}
		}
		else {	//如果就是0
			num_before_dot = 0;
		}
	}
	else {
		for (char * i = num; *i && (*i) != '.'; ++i){	//如果开头不是0
			++num_before_dot;	//找到小数点或者数字结尾前数的个数，即10的正几次方
		}
	}	
	char result[200] = {0};	//最终结果
	strcat(result, "0.");	//先用0.开头
	int number = 0;
	for (char * i = num; *i; ++i){
		//把所有的小数点都去掉，并且按要求保留数位
		if (number >= n){
			break;
		}
		else if (*i != '.'){
			result[number + strlen("0.")] = *i;
			++number;
		}	
	}
	while (number < n){	
		//如果要求的数位多于当前数位，则后面补0
		//例如123.2保留五位，是0.12320
		result[number + strlen("0.")] = '0';
		++number;
	}
	result[number + strlen("0.")] = 0;	//字符串结尾补'\0'
	char after[200] = "*10^";
	//后面乘以10的几次方（刚刚算出的结果）
	sprintf(after + strlen(after), "%d", num_before_dot);
	strcat(result, after);
	//转存临时变量
	strcpy(num, result);
	return num;
}

int main(int argc, char const *argv[])
{
	int n;
	char num1[200], num2[200];
	//输入
	scanf("%d", &n);	
	scanf("%s%s",num1, num2);
	//预处理，用于0开头的数
	preprocess(num1);
	preprocess(num2);
	//替换成科学记数法字符串
	char * conv_num1 = conv(num1, n);
	char * conv_num2 = conv(num2, n);
	//判断两个转换后的字符串是否相等
	if (strcmp(conv_num1, conv_num2) == 0){
		printf("YES %s\n", conv_num1);
	}
	else {
		printf("NO %s %s\n", conv_num1, conv_num2);
	}
	return 0;
}