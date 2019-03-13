/*
    1023 Have Fun with Numbers （20 分)
    Notice that the number 123456789 is a 9-digit number consisting exactly the numbers from 1 to 9, with no duplication. Double it we will obtain 246913578, which happens to be another 9-digit number consisting exactly the numbers from 1 to 9, only in a different permutation. Check to see the result if we double it again!

    Now you are suppose to check if there are more numbers with this property. That is, double a given number with k digits, you are to tell if the resulting number consists of only a permutation of the digits in the original number.

    Input Specification:
    Each input contains one test case. Each case contains one positive integer with no more than 20 digits.

    Output Specification:
    For each test case, first print in a line "Yes" if doubling the input number gives a number that consists of only a permutation of the digits in the original number, or "No" if not. Then in the next line, print the doubled number.

    Sample Input:
    1234567899
    Sample Output:
    Yes
    2469135798
*/

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int main(){
    //初始化数组和读入输入
    char origin_number[50] = {0}, doubled_number[50] = {0};
    scanf("%s", origin_number);
    //翻转源字符串
    int length = strlen(origin_number);
    reverse(origin_number, origin_number + length);
    //源字符串每个数乘以2（这里数字是ASCII码，因此需要先减掉0的ASCII码，然后乘2，然后加0的ASCII码）
    for (int i = 0; i < length; ++i){
        doubled_number[i] = (origin_number[i] - '0') * 2 + '0';
    }
    //进位操作，从低位到高位
    for (int i = 0; i < length; ++i){
        if (doubled_number[i] > '9'){
            //如果某一位超过9，则进位，低位减去0的ASCII码，对10取余，然后加上0的ASCII码
            //高位减去0的ASCII码，整除10
            doubled_number[i + 1] += (doubled_number[i] - '0') / 10;
            doubled_number[i] = (doubled_number[i] - '0') % 10 + '0';
        }
    }
    //如果多出一位，则把该位（最高位）变成ASCII码
    if (doubled_number[length] != '\0'){
        doubled_number[length] += '0';
    }
    //翻转新生成的结果
    length = strlen(doubled_number);
    reverse(doubled_number, doubled_number + length);
    //排序两个字符串，用于比较是否相同
    char test_number[50];
    strcpy(test_number, doubled_number);    //排序字符串前备份字符串
    sort(origin_number, origin_number + strlen(origin_number));
    sort(test_number, test_number + strlen(test_number));
    //根据排序后的字符串相同或不相同输出结果
    if (strcmp(test_number, origin_number) == 0){
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }
    printf("%s\n", doubled_number);
    return 0;
}