/*
    1092 To Buy or Not to Buy （20 分）
    Eva would like to make a string of beads with her favorite colors so she went to a small shop to buy some beads. There were many colorful strings of beads. However the owner of the shop would only sell the strings in whole pieces. Hence Eva must check whether a string in the shop contains all the beads she needs. She now comes to you for help: if the answer is Yes, please tell her the number of extra beads she has to buy; or if the answer is No, please tell her the number of beads missing from the string.

    For the sake of simplicity, let's use the characters in the ranges [0-9], [a-z], and [A-Z] to represent the colors. For example, the 3rd string in Figure 1 is the one that Eva would like to make. Then the 1st string is okay since it contains all the necessary beads with 8 extra ones; yet the 2nd one is not since there is no black bead and one less red bead.

    figbuy.jpg

    Figure 1

    Input Specification:
    Each input file contains one test case. Each case gives in two lines the strings of no more than 1000 beads which belong to the shop owner and Eva, respectively.

    Output Specification:
    For each test case, print your answer in one line. If the answer is Yes, then also output the number of extra beads Eva has to buy; or if the answer is No, then also output the number of beads missing from the string. There must be exactly 1 space between the answer and the number.

    Sample Input 1:
    ppRYYGrrYBR2258
    YrR8RrY
    Sample Output 1:
    Yes 8
    Sample Input 2:
    ppRYYGrrYB225
    YrR8RrY
    Sample Output 2:
    No 2
*/

#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
int main(){
    //输入
    char src[1005], dest[1005];
    scanf("%s %s", src, dest);

    //确定源字符串和目标字符串的大小（避免重复计算）
    int src_count = strlen(src), dest_count = strlen(dest);

    //统计源字符串和目标字符串中每个字符出现的次数
    map<char, int> src_set, dest_set;
    for (int i = 0; i < src_count; ++i){
        ++src_set[src[i]];
    }
    for (int i = 0; i < dest_count; ++i){
        ++dest_set[dest[i]]; 
    }    

    //如果目标字符串中某个字符出现的次数多于源字符串中这个字符出现的次数
    //增加missing的数量，用于最后输出总共少几个字符
    int missing = 0;
    for (map<char, int>::iterator it = dest_set.begin(); it != dest_set.end(); ++it){
        if (it->second > src_set[it->first]){
            missing += (it->second - src_set[it->first]);
        }
    }

    //输出
    if (missing){
        //如果缺少字符，则输出No
        printf("No %d\n", missing);
    }
    else {
        //如果不缺少字符，则输出Yes
        printf("Yes %d\n", src_count - dest_count);
    }
    return 0;
}