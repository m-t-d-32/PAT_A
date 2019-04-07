/*
	1025 PAT Ranking （25 分)
	Programming Ability Test (PAT) is organized by the College of Computer Science and Technology of Zhejiang University. Each test is supposed to run simultaneously in several places, and the ranklists will be merged immediately after the test. Now it is your job to write a program to correctly merge all the ranklists and generate the final rank.

	Input Specification:
	Each input file contains one test case. For each case, the first line contains a positive number N (≤100), the number of test locations. Then N ranklists follow, each starts with a line containing a positive integer K (≤300), the number of testees, and then K lines containing the registration number (a 13-digit number) and the total score of each testee. All the numbers in a line are separated by a space.

	Output Specification:
	For each test case, first print in one line the total number of testees. Then print the final ranklist in the following format:

	registration_number final_rank location_number local_rank
	The locations are numbered from 1 to N. The output must be sorted in nondecreasing order of the final ranks. The testees with the same score must have the same rank, and the output must be sorted in nondecreasing order of their registration numbers.

	Sample Input:
	2
	5
	1234567890001 95
	1234567890005 100
	1234567890003 95
	1234567890002 77
	1234567890004 85
	4
	1234567890013 65
	1234567890011 25
	1234567890014 100
	1234567890012 85
	Sample Output:
	9
	1234567890005 1 1 1
	1234567890014 1 2 1
	1234567890001 3 1 2
	1234567890003 3 1 2
	1234567890004 5 1 4
	1234567890012 5 2 2
	1234567890002 7 1 5
	1234567890013 8 2 3
	1234567890011 9 2 4
*/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Student {
	//学生类
	string id;	//学号
	int grade;	//成绩
	int location;	//地区编号（从1开始）
	int location_rank;	//地区排名（从1开始）
	int all_rank;	//总排名（从1开始）
	void get_input() {
		//从输入中获取学号和成绩
		char id[100];
		scanf("%s %d", id, &grade);
		this->id = id;
	}
	void print() {
		//输出
		printf("%s %d %d %d\n", id.c_str(), all_rank, location, location_rank);
	}
};
struct Compare {
	//用于比较两个学生谁先输出（首先成绩由高到低，其次学号由低到高）
	bool operator ()(const Student * s1, const Student * s2) {
		if (s1->grade != s2->grade)
			return s1->grade > s2->grade;
		else
			return s1->id < s2->id;
	}
};
vector<int> get_ranks(vector<Student *> & sorted_students) {
	//对一个排好序的学生数组，标出每一个的排名返回成数组（用于解决并列问题）
	vector<int> results;
	if (sorted_students.size() == 0) {
		return results;
	}
	results.push_back(1);	//第一个一定是第一名
	for (int i = 1; i < sorted_students.size(); ++i) {
		if (sorted_students[i]->grade == sorted_students[i - 1]->grade) {
			//如果并列，则和前一个名次相同
			results.push_back(results.back());
		}
		else {
			//如果不并列，则就是第i+1名
			results.push_back(i + 1);
		}
	}
	return results;
}

int main() {
	int location_count;
	scanf("%d", &location_count);

	//使用指针数组保存学生信息，用于两个指针指向同一个对象，使得两次赋值作用于同一对象
	vector<Student *> * students = new vector<Student *>[location_count];	//地区分数组
	vector<Student *> all_students;	//总数组
	for (int i = 0; i < location_count; ++i) {
		int this_location;
		scanf("%d", &this_location);
		for (int j = 0; j < this_location; ++j) {
			//读取输入
			Student *temp_student = new Student();
			temp_student->get_input();
			temp_student->location = i + 1;
			students[i].push_back(temp_student);
			all_students.push_back(temp_student);
		}
		//排序当前地区数组
		sort(students[i].begin(), students[i].end(), Compare());
		//第一次赋值：给当前地区的所有学生赋值当前地区的排名
		vector<int> result = get_ranks(students[i]);
		for (int j = 0; j < this_location; ++j) {
			students[i][j]->location_rank = result[j];
		}
	}
	//排序全部学生
	sort(all_students.begin(), all_students.end(), Compare());
	//第二次赋值：给所有学生赋值总排名
	vector<int> result = get_ranks(all_students);
	for (int i = 0; i < all_students.size(); ++i) {
		all_students[i]->all_rank = result[i];
	}
	//输出
	printf("%d\n", all_students.size());
	for (int i = 0; i < all_students.size(); ++i) {
		all_students[i]->print();
	}
	return 0;
}