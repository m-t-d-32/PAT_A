/*
	1077 Kuchiguse （20 分)
	The Japanese language is notorious for its sentence ending particles. Personal preference of such particles can be considered as a reflection of the speaker's personality. Such a preference is called "Kuchiguse" and is often exaggerated artistically in Anime and Manga. For example, the artificial sentence ending particle "nyan~" is often used as a stereotype for characters with a cat-like personality:

	Itai nyan~ (It hurts, nyan~)

	Ninjin wa iyada nyan~ (I hate carrots, nyan~)

	Now given a few lines spoken by the same character, can you find her Kuchiguse?

	Input Specification:
	Each input file contains one test case. For each case, the first line is an integer N (2≤N≤100). Following are N file lines of 0~256 (inclusive) characters in length, each representing a character's spoken line. The spoken lines are case sensitive.

	Output Specification:
	For each test case, print in one line the kuchiguse of the character, i.e., the longest common suffix of all N lines. If there is no such suffix, write nai.

	Sample Input 1:
	3
	Itai nyan~
	Ninjin wa iyadanyan~
	uhhh nyan~
	Sample Output 1:
	nyan~
	Sample Input 2:
	3
	Itai!
	Ninjinnwaiyada T_T
	T_T
	Sample Output 2:
	nai
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

int main(){
	//读入n
	int n;
	scanf("%d", &n);
	//字符串数组：存储所有字符串
	vector<string> spokens;
	//存储读入的每个临时变量
	char temp[1024];
	//去掉缓冲区中的换行符，避免干扰
	fgets(temp, 1024, stdin);
	for (int i = 0; i < n; ++i){
		//读入每行字符串并放入字符串数组
		fgets(temp, 1024, stdin);
		//去掉行尾的换行符
		temp[strlen(temp) - 1] = '\0';	
		spokens.push_back(string(temp));
	}
	int i = 0;
	while (true){
		//从后往前查找字符，检查是否在每个字符串的对应位置都出现这个字符
		bool is_same = true;	//标志
		if (i >= spokens[0].size()){
			break;
		}
		char same_char = spokens[0][spokens[0].size() - i - 1];	//公共字符
		for (int j = 1; j < spokens.size(); ++j){
			//检查对应位置是否有字符，是否是公共字符
			if (i >= spokens[j].size() || same_char != spokens[j][spokens[j].size() - i - 1]){
				//如果存在一个不是，则更改标志位为失败，循环跳出
				is_same = false;
				break;
			}
		}
		if (!is_same){
			//失败，外层循环跳出
			break;
		}
		++i;	//否则从后往前遍历下一个字符
	}
	if (i > 0){
		//从前往后输出找到的公共字符
		for (int j = i; j > 0; --j){
			printf("%c", spokens[0][spokens[0].size() - j]);
		}
	}
	else{
		//如果一个字符都没有，输出nai
		printf("nai");
	}
	return 0;
}