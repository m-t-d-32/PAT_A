/*
    1009 Product of Polynomials （25 分）
    This time, you are supposed to find A×B where A and B are two polynomials.

    Input Specification:
    Each input file contains one test case. Each case occupies 2 lines, and each line contains the information of a polynomial:

    K N
    ​1
    ​​  a
    ​N
    ​1
    ​​ 
    ​​  N
    ​2
    ​​  a
    ​N
    ​2
    ​​ 
    ​​  ... N
    ​K
    ​​  a
    ​N
    ​K
    ​​ 
    ​​ 

    where K is the number of nonzero terms in the polynomial, N
    ​i
    ​​  and a
    ​N
    ​i
    ​​ 
    ​​  (i=1,2,⋯,K) are the exponents and coefficients, respectively. It is given that 1≤K≤10, 0≤N
    ​K
    ​​ <⋯<N
    ​2
    ​​ <N
    ​1
    ​​ ≤1000.

    Output Specification:
    For each test case you should output the product of A and B in one line, with the same format as the input. Notice that there must be NO extra space at the end of each line. Please be accurate up to 1 decimal place.

    Sample Input:
    2 1 2.4 0 3.2
    2 2 1.5 1 0.5
    Sample Output:
    3 3 3.6 2 6.0 1 1.6
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct Item{
    //项：一个底数和一个指数组成一个项
    int radix;
    double base;
};
bool operator < (const Item & i1, const Item & i2){
    //比较两个项大小的函数（用于排序函数sort）
    return i1.radix < i2.radix;
}
inline bool isZero(double t){
    //判断浮点数为0（不可直接判断==0）
    return fabs(t) < 1e-7;
}
vector<Item> get_items(){
    //从输入流中获取一个多项式，并且排序后返回Item的数组
    vector<Item> result;
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i){
        Item temp;
        scanf("%d %lf", &temp.radix, &temp.base);
        result.push_back(temp);
    }
    //从小到大排序
    sort(result.begin(), result.end());
    return result;
}

int main(){
    //输入
    vector<Item> r1 = get_items(), r2 = get_items();
    vector<Item> result;
    //乘积
    for (int i = 0; i < r1.size(); ++i){
        for (int j = 0; j < r2.size(); ++j){
            Item temp;
            temp.base = r1[i].base * r2[j].base;
            temp.radix = r1[i].radix + r2[j].radix;
            result.push_back(temp);
        }
    }
    //排序乘积（用于合并同类项，相同指数一定相邻）
    sort(result.begin(), result.end());
    //合并同类项
    vector<Item> final_result;
    final_result.push_back(result[0]);
    for (int i = 1; i < result.size(); ++i){
        if (final_result.back().radix == result[i].radix){
            //如果是同类项，则直接底数相加
            final_result[final_result.size() - 1].base += result[i].base;
        }
        else {
            //如果不是，则新建一个项并放在数组的末尾
            if (isZero(final_result.back().base)){
                //判断刚刚放入的是否是底数为0的项，如果是则删除
                final_result.pop_back();
            }
            final_result.push_back(result[i]);
        }
    }
    //按题目要求从大到小排列
    reverse(final_result.begin(), final_result.end());
    //排序输出，保留一位小数
    printf("%d ", final_result.size());
    if (final_result.size() > 1){
        for (int i = 0; i < final_result.size() - 1; ++i){
            printf("%d %.1lf ", final_result[i].radix, final_result[i].base);
        }
    }
    printf("%d %.1lf", final_result.back().radix, final_result.back().base);
    return 0;
}