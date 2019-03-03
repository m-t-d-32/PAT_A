/*
	1054 The Dominant Color （20 分）
	Behind the scenes in the computer's memory, color is always talked about as a series of 24 bits of information for each pixel. In an image, the color with the largest proportional area is called the dominant color. A strictly dominant color takes more than half of the total area. Now given an image of resolution M by N (for example, 800×600), you are supposed to point out the strictly dominant color.

	Input Specification:
	Each input file contains one test case. For each case, the first line contains 2 positive numbers: M (≤800) and N (≤600) which are the resolutions of the image. Then N lines follow, each contains M digital colors in the range [0,2
	​24
	​​ ). It is guaranteed that the strictly dominant color exists for each input image. All the numbers in a line are separated by a space.

	Output Specification:
	For each test case, simply print the dominant color in a line.

	Sample Input:
	5 3
	0 0 255 16777215 24
	24 24 0 0 24
	24 0 24 24 24
	Sample Output:
	24
*/

#include <cstdio>

int main(int argc, char const *argv[])
{
	//这是一个只需要浏览一遍所有的数就可以得出解的方法
	//且空间复杂度为O(1)
	//原理是依据题目假设：众数一定出现次数多于一半
	//引入某个数的净出现次数：这个数出现一次，净出现次数+1，否则-1
	//因此得出结论：要求众数净出现次数一定大于0
	
	int m, n;
	scanf("%d%d", &m, &n);
	int * colors = new int[m * n];	//申请内存

	//counter是从当前众数成为众数开始，当前众数的净出现次数
	//max是当前众数
	int counter = 1, max = -1;	
	for (int i = 0; i < m * n; ++i){
		int temp;
		scanf("%d", &temp);	//读取下一个数
		if (temp == max){	//如果当前众数再次出现，则净出现次数+1
			++counter;
		}
		else {
			--counter;	//如果当前众数没有出现，则净出现次数-1
			if (counter <= 0){	
				//如果到目前为止当前众数的净出现次数不再大于0
				//则表明从0到现在为止的这些数，当前众数不是要求众数
				//只有可能是刚刚出现的数是要求众数
				//（从0到现在为止的这些数，刚刚出现的数的净出现次数最多为1，其他数的净出现次数最多为0）
				//因此将众数替换成刚刚出现的数，将counter置为1（题目假设一定存在众数)
				counter = 1;
				max = temp;
			}
		}	
	}

	//输出最终的假设众数，它一定是要求的众数
	printf("%d\n", max);
	return 0;
}