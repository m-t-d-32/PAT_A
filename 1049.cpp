/*
    1049 Counting Ones （30 分）
    The task is simple: given any positive integer N, you are supposed to count the total number of 1's in the decimal form of the integers from 1 to N. For example, given N being 12, there are five 1's in 1, 10, 11, and 12.

    Input Specification:
    Each input file contains one test case which gives the positive N (≤2
    ​30
    ​​ ).

    Output Specification:
    For each test case, print the number of 1's in one line.

    Sample Input:
    12
    Sample Output:
    5
*/

#include <cstdio>
#include <cmath>
#include <string>
using namespace std;

string split(const string & str, int begin, int end){
	//切片操作，返回字符串[begin, end)之间的元素
    string result;
    for (int i = begin; i < end; ++i){
        result += str[i];
    }
    return result;
}

inline int _stoi(string str){
	//加工的stoi，如果是空串返回0
    return str.size() ? stoi(str) : 0;
}

int main(){
	//输入
    char number[20];
    scanf("%s", number);
    string num_str(number);

    long long counter = 0, add_counter = 0;
    for (int i = 0; i < num_str.size(); ++i){
		//对于输入的数字（字符串）的每一位
        if (num_str[i] == '1'){
			//如果该位是1，则不超过该数字的所有数字中，该位为1的数字的个数为
			//将这一位抹去，剩下的所有位组合起来，得到的数字再加1（因为考虑0和本身）
            add_counter = _stoi(split(num_str, 0, i) + split(num_str, i + 1, num_str.size())) + 1;
        }
        else if (num_str[i] == '0'){
			//如果该位是0，则不超过该数字的所有数字中，该位为1的数字的个数为
			//该位前面的数字，乘以10的“该位后面的数字的位数”次方
			//（例如2024，则0100-0199, 1100-1199都可以，而21xx，31xx等都不可以）
            add_counter = (_stoi(split(num_str, 0, i))) * pow(10, num_str.size() - i - 1);
        }
        else {
			//如果该位大于1，则不超过该数字的所有数字中，该位为1的数字的个数为
			//该位前面的数字加一，乘以10的“该位后面的数字的位数”次方
			//（例如2424的第2位，则0100-0199, 1100-1199, 2100-2199都可以，而31xx，41xx等都不可以）
            add_counter = (_stoi(split(num_str, 0, i)) + 1) * pow(10, num_str.size() - i - 1);
        }
        counter += add_counter;
    }
	//输出
    printf("%lld", counter);
    return 0;
}
