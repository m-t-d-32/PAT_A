/*
    1029 Median （25 分)
    Given an increasing sequence S of N integers, the median is the number at the middle position. For example, the median of S1 = { 11, 12, 13, 14 } is 12, and the median of S2 = { 9, 10, 15, 16, 17 } is 15. The median of two sequences is defined to be the median of the nondecreasing sequence which contains all the elements of both sequences. For example, the median of S1 and S2 is 13.

    Given two increasing sequences of integers, you are asked to find their median.

    Input Specification:
    Each input file contains one test case. Each case occupies 2 lines, each gives the information of a sequence. For each sequence, the first positive integer N (≤2×10
    ​5
    ​​ ) is the size of that sequence. Then N integers follow, separated by a space. It is guaranteed that all the integers are in the range of long int.

    Output Specification:
    For each test case you should output the median of the two given sequences in a line.

    Sample Input:
    4 11 12 13 14
    5 9 10 15 16 17
    Sample Output:
    13
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	//伪双指针法：用于解决双指针法内存超限问题
	
	//输入第一组数据
    int size_1;
    scanf("%d", &size_1);
    int *array1 = new int[size_1];	//第一组输入用数组存起来
    for (int i = 0; i < size_1; ++i){
        scanf("%d", &array1[i]);
    }
	//输入第二组数据的大小
    int size_2;
    scanf("%d", &size_2);
	//pointer_1是当前指向第一组数据的某个数的数组下标
	//pointer_2是虚构的当前指向第二组数据的某个数的数组下标
	//开始时为0
    int pointer_1 = 0, pointer_2 = 0, counter = 0;
	//middle_size是两个数组合并后，中位数应该所在的位置
    int middle_size = (size_1 + size_2 - 1) / 2;
	//输入第二组的第一个数据
	int temp;
	scanf("%d", &temp);
	
	//双指针法
    for (int i = 0; pointer_1 < size_1 && pointer_2 < size_2; ++i){
        if (array1[pointer_1] > temp){
			//如果第一个数组当前指向的数大于第二个数组当前指向的数
			//pointer_2右移1（事实上是新读入一个数据，并替换temp）
			if (counter == middle_size){
				printf("%d\n", temp);
				return 0;
			}
			++pointer_2;
			++counter;
			scanf("%d", &temp);
		}
		else {
			//如果第一个数组当前指向的数大于第二个数组当前指向的数
			//pointer_1右移1
			if (counter == middle_size){
				printf("%d\n", array1[pointer_1]);
				return 0;
			}
			++pointer_1;
			++counter;
		}
    }
	//如果还没有到达中位数的位置，且第一个数组没读完
	//则pointer_1右移，直到中位数的位置为止
    while (pointer_1 < size_1){
		if (counter == middle_size){
			printf("%d\n", array1[pointer_1]);
			return 0;
		}
		++pointer_1;
		++counter;
    }
	//如果还没有到达中位数的位置，且第一个数组没读完
	//则pointer_1右移，直到中位数的位置为止
	//（事实上相当于一直读入，直到pointer_2是中位数的位置为止）
	while (pointer_2 < size_2){
		if (counter == middle_size){
			printf("%d\n", temp);
			return 0;
		}
		++pointer_2;
		++counter;
		printf("%d\n", temp);
	}
    return 0;
}