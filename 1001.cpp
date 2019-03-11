/*
    1001 A+B Format （20 分）
    Calculate a+b and output the sum in standard format -- that is, the digits must be separated into groups of three by commas (unless there are less than four digits).

    Input Specification:
    Each input file contains one test case. Each case contains a pair of integers a and b where −10
    ​6
    ​​ ≤a,b≤10
    ​6
    ​​ . The numbers are separated by a space.

    Output Specification:
    For each test case, you should output the sum of a and b in one line. The sum must be written in the standard format.

    Sample Input:
    -1000000 9
    Sample Output:
    -999,991
*/

#include <cstdio>
#include <stack>
using namespace std;

int main(){
    //输入
    int a, b;
    scanf("%d%d", &a, &b);
    //计算
    int result = a + b;
    //输出负号，并且变成正数
    if (result < 0){
        printf("-");
        result = -result;
    }
    //循环整除1000，余数依次压栈，最终高位在栈顶
    stack<int> prints;
    while (result){
        prints.push(result % 1000);
        result /= 1000;
    }
    //循环出栈，先输出高位
    if (prints.empty()){
        //如果栈空，表明是数字0，输出0
        printf("0");
    }
    else {
        //否则依次输出，高位在前低位在后
        printf("%d", prints.top());
        prints.pop();
        while (!prints.empty()){
            //低位不足3位补齐输出，并添加逗号
            printf(",%03d", prints.top());
            prints.pop();
        }
    }
    return 0;
}