/*
	1028 List Sorting （25 分）
	Excel can sort records according to any column. Now you are supposed to imitate this function.

	Input Specification:
	Each input file contains one test case. For each case, the first line contains two integers N (≤10
	​5
	​​ ) and C, where N is the number of records and C is the column that you are supposed to sort the records with. Then N lines follow, each contains a record of a student. A student's record consists of his or her distinct ID (a 6-digit number), name (a string with no more than 8 characters without space), and grade (an integer between 0 and 100, inclusive).

	Output Specification:
	For each test case, output the sorting result in N lines. That is, if C = 1 then the records must be sorted in increasing order according to ID's; if C = 2 then the records must be sorted in non-decreasing order according to names; and if C = 3 then the records must be sorted in non-decreasing order according to grades. If there are several students who have the same name or grade, they must be sorted according to their ID's in increasing order.

	Sample Input 1:
	3 1
	000007 James 85
	000010 Amy 90
	000001 Zoe 60
	Sample Output 1:
	000001 Zoe 60
	000007 James 85
	000010 Amy 90
	Sample Input 2:
	4 2
	000007 James 85
	000010 Amy 90
	000001 Zoe 60
	000002 James 98
	Sample Output 2:
	000010 Amy 90
	000002 James 98
	000007 James 85
	000001 Zoe 60
	Sample Input 3:
	4 3
	000007 James 85
	000010 Amy 90
	000001 Zoe 60
	000002 James 90
	Sample Output 3:
	000001 Zoe 60
	000007 James 85
	000002 James 90
	000010 Amy 90
*/

#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

struct Info{
	int id, grade;
	string name;
	void print(){
		printf("%06d %s %d\n", id, name.c_str(), grade);
	}
};

inline bool compare1(const Info & info1, const Info & info2){
	return info1.id < info2.id;
}
inline bool compare2(const Info & info1, const Info & info2){
	return info1.name == info2.name ? info1.id < info2.id : info1.name < info2.name;
}
inline bool compare3(const Info & info1, const Info & info2){
	return info1.grade == info2.grade ? info1.id < info2.id : info1.grade < info2.grade;
}

int main(int argc, char const *argv[]) {
	int n, type;
	scanf("%d %d", &n, &type);

	Info * infos = new Info[n];
	for (int i = 0; i < n; ++i){
		int temp_id, temp_grade;
		char temp_name[20];
		scanf("%d %s %d", &temp_id, temp_name, &temp_grade);
		infos[i].id = temp_id;
		infos[i].name = string(temp_name);
		infos[i].grade = temp_grade;
	}
	switch (type){
		case 1: sort(infos, infos + n, compare1); break;
		case 2: sort(infos, infos + n, compare2); break;
		case 3: sort(infos, infos + n, compare3); break;
	}
	for (int i = 0; i < n; ++i){
		infos[i].print();
	}
	return 0;
}
