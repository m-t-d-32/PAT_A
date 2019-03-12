/*
    1015 Reversible Primes （20 分)
    A reversible prime in any number system is a prime whose "reverse" in that number system is also a prime. For example in the decimal system 73 is a reversible prime because its reverse 37 is also a prime.

    Now given any two positive integers N (<10
    ​5
    ​​ ) and D (1<D≤10), you are supposed to tell if N is a reversible prime with radix D.

    Input Specification:
    The input file consists of several test cases. Each case occupies a line which contains two integers N and D. The input is finished by a negative N.

    Output Specification:
    For each test case, print in one line Yes if N is a reversible prime with radix D, or No if not.

    Sample Input:
    73 10
    23 2
    23 10
    -2
    Sample Output:
    Yes
    Yes
    No
*/

#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
#include <stack>
using namespace std;

bool is_prime(int number){
    //判断一个数是否为质数  
    if (number < 2){
        //质数必须大于2
        return false;
    }

    //从2开始遍历直到根号number为止即可
    int max = sqrt(number);
    for (int i = 2; i <= max; ++i){
        if (number % i == 0){
            return false;
        }
    }
    return true;
}

string to_string(int raw_number, int radix){
    //将一个十进制整数变成另一进制的整数并以string返回
    stack<char> remainders;
    while (raw_number){
        //用栈存储：最先push的是低位
        remainders.push(raw_number % radix + '0');
        raw_number /= radix;
    }
    if (remainders.empty()){
        //如果是空栈表明数是0
        return "0";
    }
    else {
        //否则依次弹出，最先弹出的是高位，可直接进行字符串拼接
        string result;
        while (!remainders.empty()){
            result += remainders.top();
            remainders.pop();
        }
        return result;
    }    
}

int to_number(string raw_string, int radix){
    //将一个用string表示的radix进制数变成十进制整数
    int result = 0;
    for (int i = 0; i < raw_string.size(); ++i){
        //result每次进行（十进制）左移并加上新的低位
        result *= radix;
        result += raw_string[i] - '0';
    }
    return result;
}

int main(){        
    while (true){
        //输入
        int number, radix;
        scanf("%d", &number);
        if (number < 0){
            break;
        }
        scanf("%d", &radix);

        //将原数变成要求进制的字符串，然后反转字符串，然后变回十进制数
        string str_num = to_string(number, radix);
        reverse(str_num.begin(), str_num.end());
        if (is_prime(number) && is_prime(to_number(str_num, radix))){
            //如果原数和新数都是质数输出Yes
            printf("Yes\n");
        }
        else {
            //否则输出No
            printf("No\n");
        }
    }
    return 0;
}