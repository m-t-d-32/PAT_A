/*
	1017 Queueing at Bank （25 分）
	Suppose a bank has K windows open for service. There is a yellow line in front of the windows which devides the waiting area into two parts. All the customers have to wait in line behind the yellow line, until it is his/her turn to be served and there is a window available. It is assumed that no window can be occupied by a single customer for more than 1 hour.

	Now given the arriving time T and the processing time P of each customer, you are supposed to tell the average waiting time of all the customers.

	Input Specification:
	Each input file contains one test case. For each case, the first line contains 2 numbers: N (≤10
	​4
	​​ ) - the total number of customers, and K (≤100) - the number of windows. Then N lines follow, each contains 2 times: HH:MM:SS - the arriving time, and P - the processing time in minutes of a customer. Here HH is in the range [00, 23], MM and SS are both in [00, 59]. It is assumed that no two customers arrives at the same time.

	Notice that the bank opens from 08:00 to 17:00. Anyone arrives early will have to wait in line till 08:00, and anyone comes too late (at or after 17:00:01) will not be served nor counted into the average.

	Output Specification:
	For each test case, print in one line the average waiting time of all the customers, in minutes and accurate up to 1 decimal place.

	Sample Input:
	7 3
	07:55:00 16
	17:00:01 2
	07:59:59 15
	08:01:00 60
	08:00:00 30
	08:00:02 2
	08:03:00 10
	Sample Output:
	8.2
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Time{
	int seconds;
	void setTime(){
		int hh, mm, ss;
		scanf("%d:%d:%d", &hh, &mm, &ss);

		//全部换成秒，方便计算
		seconds = hh * 60 * 60 + mm * 60 + ss;
	}
	bool operator < (const Time & another) const{
		return seconds < another.seconds;
	}
};
typedef pair<Time, int> customer; //到来的时刻和需要的时间即顾客属性
bool operator < (const customer & c1, const customer & c2){
	return c1.first < c2.first;
}

int main(){
	int n, w;
	scanf("%d%d", &n, &w);
	//表示每个窗口还需要等待多长时间
	int * remainTime = new int[w];
	for (int i = 0; i < w; ++i){
		remainTime[i] = 0;
	}
	//定义8时和17时常数
	Time const8hour, const17hour;
	const8hour.seconds = 8 * 60 * 60;
	const17hour.seconds = 17 * 60 * 60;

	vector<customer> customers;
	//读取输入并存储早于17时来的顾客
	for (int i = 0; i < n; ++i){
		Time t;
		t.setTime();
		int remain;
		scanf("%d", &remain);
		if (t.seconds <= const17hour.seconds){
			customers.push_back(customer(t, remain));
		}
	}

	unsigned result = 0;
	//先来后到进行排序
	sort(customers.begin(), customers.end());
	//更早的顾客，归一化成8时顾客
	for (int i = 0; i < customers.size(); ++i){
		if (customers[i].first.seconds < const8hour.seconds){
			result += const8hour.seconds - customers[i].first.seconds;
			customers[i].first.seconds = const8hour.seconds;
		}
	}
	//开始工作
	int begin_time = const8hour.seconds;
	for (int i = 0; i < customers.size(); ++i){
		//下一个顾客来了，时间刷新
		int now_time = customers[i].first.seconds;
		for (int j = 0; j < w; ++j){
			remainTime[j] = (remainTime[j] - (now_time - begin_time) > 0) ? remainTime[j] - (now_time - begin_time) : 0;
		}
		//下一个顾客去找等待时间最少的位置
		sort(remainTime, remainTime + w);
		//更新等待时间
		result += remainTime[0];
		remainTime[0] += customers[i].second * 60;
		//更新时间
		begin_time = now_time;
	}
	printf("%.1lf", result / 60.0 / customers.size());
	return 0;
}
