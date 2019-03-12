/*
    1059 Prime Factors （25 分)
    Given any positive integer N, you are supposed to find all of its prime factors, and write them in the format N = p
    ​1
    ​​ 
    ​k
    ​1
    ​​ 
    ​​ ×p
    ​2
    ​​ 
    ​k
    ​2
    ​​ 
    ​​ ×⋯×p
    ​m
    ​​ 
    ​k
    ​m
    ​​ 
    ​​ .

    Input Specification:
    Each input file contains one test case which gives a positive integer N in the range of long int.

    Output Specification:
    Factor N in the format N = p
    ​1
    ​​ ^k
    ​1
    ​​ *p
    ​2
    ​​ ^k
    ​2
    ​​ *…*p
    ​m
    ​​ ^k
    ​m
    ​​ , where p
    ​i
    ​​ 's are prime factors of N in increasing order, and the exponent k
    ​i
    ​​  is the number of p
    ​i
    ​​  -- hence when there is only one p
    ​i
    ​​ , k
    ​i
    ​​  is 1 and must NOT be printed out.

    Sample Input:
    97532468
    Sample Output:
    97532468=2^2*11*17*101*1291
*/

#include <cstdio>
#include <vector>
using namespace std;

int main(){
    long long num;
    //输入输出原数
    scanf("%lld", &num);
    printf("%lld=", num);
    //动态数组：用于存放所有质因数（从小到大）
    vector<long long> factors;
    if (num <= 1){
        //原数如果小于2则直接输出
        printf("%lld", num);
        return 0;
    }
    //从2开始遍历所有比原数小的数，直到能够被整除为止
    //这样可以保证遍历到的一定是质因数，且先遍历到的一定比后遍历到的小
    while (num != 1){
        long long begin = factors.empty() ? 2 : factors.back();
        for (long long i = begin; i <= num; ++i){
            if (num % i == 0){
                //遍历到一个，则插入到动态数组，同时原数除以这个质因数
                num /= i;
                factors.push_back(i);
                break;
            }
        }
    }
    //输出
    printf("%lld", factors[0]);
    //counter用于计数当前质因数出现的次数
    int counter = 1;
    for (int i = 1; i < factors.size(); ++i){
        //判断当前遍历到的质因数是否与刚才的质因数相同
        if (factors[i] == factors[i - 1]){
            //如果相同，则出现次数+1
            ++counter;
        }
        else {
            //如果不同，则输出
            if (counter > 1){
                //如果刚才的质因数出现的次数多于1，则输出counter作为指数
                printf("^%d", counter);
            }
            //输出这次的质因数
            printf("*%lld", factors[i]);
            counter = 1;
        }
    }
    //最后还可能有质因数没有输出
    if (counter > 1){
        //如果出现的次数多于1，则输出counter作为指数
        printf("^%d", counter);
    }
    return 0;
}