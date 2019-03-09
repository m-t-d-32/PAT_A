/*
	1082 Read Number in Chinese （25 分）
	Given an integer with no more than 9 digits, you are supposed to read it in the traditional Chinese way. Output Fu first if it is negative. For example, -123456789 is read as Fu yi Yi er Qian san Bai si Shi wu Wan liu Qian qi Bai ba Shi jiu. Note: zero (ling) must be handled correctly according to the Chinese tradition. For example, 100800 is yi Shi Wan ling ba Bai.

	Input Specification:
	Each input file contains one test case, which gives an integer with no more than 9 digits.

	Output Specification:
	For each test case, print in a line the Chinese way of reading the number. The characters are separated by a space and there must be no extra space at the end of the line.

	Sample Input 1:
	-123456789
	Sample Output 1:
	Fu yi Yi er Qian san Bai si Shi wu Wan liu Qian qi Bai ba Shi jiu
	Sample Input 2:
	100800
	Sample Output 2:
	yi Shi Wan ling ba Bai
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

vector<string> results;

string chn_nums[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
string middle_nums[] = {"Qian", "Bai", "Shi"};
char * num_str;
bool * zeros;

void read(int begin, int end){	
	//输出num_str数组中begin到end位（可能为负数）
	for (int i = begin; i < end; ++i){
		//必须i不是负数才可能输出
		if (i >= 0 && num_str[i] != '0'){
			//如果i的上一位存在且是0，且这一位不是0，则输出0
			if (i > 0 && num_str[i - 1] == '0'){
				results.push_back(chn_nums[0]);
			}
			//输出这一位
			results.push_back(chn_nums[num_str[i] - '0']);
			//输出千、百、十
			if (i - begin < sizeof(middle_nums) / sizeof(string)){
				results.push_back(middle_nums[i - begin]);
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	//输入
	num_str = new char[20];
	scanf("%s", num_str);
	//输出负号
	if (num_str[0] == '-'){
		++num_str;
		printf("Fu ");
	}

	int max_len = strlen(num_str);
	//保存[12, 8)位，即亿量级
	if (max_len > 8){
		read(max_len - 12, max_len - 8);
		results.push_back("Yi");
	}
	//保存[8, 4)位，即万量级
	if (max_len > 4){
		read(max_len - 8, max_len - 4);
		results.push_back("Wan");
	}
	//保存[4, 0)位，即个量级
	read(max_len - 4, max_len);
	
	//输出结果
	if (results.size()){
		for (int i = 0; i < results.size() - 1; ++i){
			printf("%s ", results[i].c_str());
		}
		printf("%s\n", results.back().c_str());
	}
	else {
		printf("%s\n", chn_nums[0].c_str());
	}
	return 0;
}