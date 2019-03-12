/*
    1093 Count PAT's （25 分)
    The string APPAPT contains two PAT's as substrings. The first one is formed by the 2nd, the 4th, and the 6th characters, and the second one is formed by the 3rd, the 4th, and the 6th characters.

    Now given any string, you are supposed to tell the number of PAT's contained in the string.

    Input Specification:
    Each input file contains one test case. For each case, there is only one line giving a string of no more than 10
    ​5
    ​​  characters containing only P, A, or T.

    Output Specification:
    For each test case, print in one line the number of  PAT's contained in the string. Since the result may be a huge number, you only have to output the result moded by 1000000007.

    Sample Input:
    APPAPT
    Sample Output:
    2
*/

#include <cstdio>

int main(){
    //输入
    char str[100005];
    scanf("%s", str);
    //定义P的个数，PA的个数和PAT的个数（最终结果）
    long long p = 0, pa = 0, pat = 0;
    for (int i = 0; str[i] != '\0'; ++i){
        //遍历字符串的每一个字符
        switch(str[i]){
            case 'P': {
                //如果多了一个P
                //那就多出了一个P
                p += 1;
                break;
            }
            case 'A': {
                //如果多了一个A
                //则多出了“多出的P那么多个”PA
                pa += p;
                break;
            }
            case 'T': {
                //如果多了一个T
                //则多出了“多出的PA那么多个”PAT
                pat += pa;
                pat %= 1000000007;
                break;
            }
        }
    }
    //输出
    printf("%lld\n", pat);
    return 0;
}