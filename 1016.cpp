/*
    1016 Phone Bills （25 分）
    A long-distance telephone company charges its customers by the following rules:

    Making a long-distance call costs a certain amount per minute, depending on the time of day when the call is made. When a customer starts connecting a long-distance call, the time will be recorded, and so will be the time when the customer hangs up the phone. Every calendar month, a bill is sent to the customer for each minute called (at a rate determined by the time of day). Your job is to prepare the bills for each month, given a set of phone call records.

    Input Specification:
    Each input file contains one test case. Each case has two parts: the rate structure, and the phone call records.

    The rate structure consists of a line with 24 non-negative integers denoting the toll (cents/minute) from 00:00 - 01:00, the toll from 01:00 - 02:00, and so on for each hour in the day.

    The next line contains a positive number N (≤1000), followed by N lines of records. Each phone call record consists of the name of the customer (string of up to 20 characters without space), the time and date (mm:dd:hh:mm), and the word on-line or off-line.

    For each test case, all dates will be within a single month. Each on-line record is paired with the chronologically next record for the same customer provided it is an off-line record. Any on-line records that are not paired with an off-line record are ignored, as are off-line records not paired with an on-line record. It is guaranteed that at least one call is well paired in the input. You may assume that no two records for the same customer have the same time. Times are recorded using a 24-hour clock.

    Output Specification:
    For each test case, you must print a phone bill for each customer.

    Bills must be printed in alphabetical order of customers' names. For each customer, first print in a line the name of the customer and the month of the bill in the format shown by the sample. Then for each time period of a call, print in one line the beginning and ending time and date (dd:hh:mm), the lasting time (in minute) and the charge of the call. The calls must be listed in chronological order. Finally, print the total charge for the month in the format shown by the sample.

    Sample Input:
    10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10
    10
    CYLL 01:01:06:01 on-line
    CYLL 01:28:16:05 off-line
    CYJJ 01:01:07:00 off-line
    CYLL 01:01:08:03 off-line
    CYJJ 01:01:05:59 on-line
    aaa 01:01:01:03 on-line
    aaa 01:02:00:01 on-line
    CYLL 01:28:15:41 on-line
    aaa 01:05:02:24 on-line
    aaa 01:04:23:59 off-line
    Sample Output:
    CYJJ 01
    01:05:59 01:07:00 61 $12.10
    Total amount: $12.10
    CYLL 01
    01:06:01 01:08:03 122 $24.40
    28:15:41 28:16:05 24 $3.85
    Total amount: $28.25
    aaa 01
    02:00:01 04:23:59 4318 $638.80
    Total amount: $638.80
*/

#include <cstdio>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

#define HOUR_A_DAY 24

struct Time{
	int month, day, hour, minute;
	bool is_start; //表示是开始时间还是结束时间
	Time(){//构造函数（无效时间）
		month = day = hour = minute = is_start = -1;
	}
	void setTime(){ //从输入中读入时间
		char type[20];
		scanf("%d:%d:%d:%d %s", &month, &day, &hour, &minute, type);
		if (string(type) == "on-line"){
			is_start = true;
		}
		else if (string(type) == "off-line"){
			is_start = false;
		}
	}
	bool operator < (const Time & another){	//比较运算符，用于排序
		char result = 0;

		//加权比较方法 省if
		result += (month > another.month ? (1 << 4) : (month < another.month ? -(1 << 4) : 0));
		result += (day > another.day ? (1 << 3) : (day < another.day ? -(1 << 3) : 0));
		result += (hour > another.hour ? (1 << 2) : (hour < another.hour ? -(1 << 2) : 0));
		result += (minute > another.minute ? 1 : (minute < another.minute ? -1 : 0));
		return result < 0;
	}
	void print(){	//格式输出时间
		printf("%02d:%02d:%02d", day, hour, minute);
	}
};
int operator - (const Time & t1, const Time & t2){
	return (t1.day - t2.day) * 24 * 60 + (t1.hour - t2.hour) * 60 + t1.minute - t2.minute;
}
typedef pair<Time, Time> each_pair;	//开始时间和结束时间（一组通话记录）
typedef vector<Time> info; //一个人所有的通话记录
typedef vector<each_pair> pairs; //一个人所有的通话记录对

int time_price_table[HOUR_A_DAY];	//一天不同时间的收费
double price_between_table[HOUR_A_DAY][HOUR_A_DAY];	//一天从某时刻到某时刻的收费（打表）
double price_whole_day; //整个一天的收费（24小时）
double get_price(const Time & begin, const Time & end){	//获取通话时间所对应的价格
	double result = 0;
	//对齐
	result -= time_price_table[begin.hour] * begin.minute  / 100.0;
	result += time_price_table[end.hour] * end.minute / 100.0;
	//计算小时
	result += price_between_table[begin.hour][end.hour];
	//计算天
	result += price_whole_day * (end.day - begin.day);
	return result;
}

int main(){
	for (int i = 0; i < HOUR_A_DAY; ++i){
		scanf("%d", &time_price_table[i]);
	}
	for (int i = 0; i < HOUR_A_DAY; ++i){
		double total = 0;	//从i到j的总价钱
		for (int j = i + 1; j < HOUR_A_DAY; ++j){
			total += time_price_table[j - 1] * 60.0 / 100;
			price_between_table[i][j] = total;
			price_between_table[j][i] = -price_between_table[i][j];
		}
		price_between_table[i][i] = 0;
	}
	//整个一天的价钱由[0, 23) + 23组成
	price_whole_day = price_between_table[0][HOUR_A_DAY - 1] + time_price_table[HOUR_A_DAY - 1] * 60.0 / 100;
	int n;
	scanf("%d", &n);
	map<string, info> result_table;	//人名和与之对应的通话记录
	map<string, pairs> result;	//人名与最终的通话记录对
	for (int i = 0; i < n; ++i){
		char name[50];
		scanf("%s", name);
		Time time;
		time.setTime();
		result_table[name].push_back(time);
	}
	for (map<string, info>::iterator it = result_table.begin(); it != result_table.end(); ++it){
		//读取某个用户的所有时间并转化为有效的时间对
		const string & name = it->first;
		info & person_info = it->second;
		sort(person_info.begin(), person_info.end());	//按时间顺序排序
		bool now_begin = false;
		Time begin_time;
		for (info::iterator another_it = person_info.begin(); another_it != person_info.end(); ++another_it){
			if (another_it->is_start){
				//如果是开始时间，则后面的总更显前面的
				begin_time = *another_it;
				now_begin = true;
			}
			else if (now_begin){
				//如果是结束时间，并有与之对应的开始时间，则得到时间对
				each_pair now_result(begin_time, *another_it);
				result[name].push_back(now_result);
				now_begin = false;
			}
		}
	}
	for (map<string, pairs>::iterator it = result.begin(); it != result.end(); ++it){
		pairs & times = it->second;
		double all_price = 0;
		int month = times[0].first.month;
		printf("%s %02d\n", it->first.c_str(), month);
		for (pairs::iterator another_it = times.begin(); another_it != times.end(); ++another_it){
			//格式输出
			another_it->first.print();
			printf(" ");
			another_it->second.print();
			printf(" ");
			int time_between = another_it->second - another_it->first;
			double price_between = get_price(another_it->first, another_it->second);
			printf("%d $%.2lf\n", time_between, price_between);
			all_price += price_between;
		}
		printf("Total amount: $%.2lf\n", all_price);
	}
	return 0;
}
