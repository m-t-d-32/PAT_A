/*
	1036 Boys vs Girls （25 分)
	This time you are asked to tell the difference between the lowest grade of all the male students and the highest grade of all the female students.

	Input Specification:
	Each input file contains one test case. Each case contains a positive integer N, followed by N lines of student information. Each line contains a student's name, gender, ID and  grade, separated by a space, where name and ID are strings of no more than 10 characters with no space, gender is either F (female) or M (male), and grade is an integer between 0 and 100. It is guaranteed that all the grades are distinct.

	Output Specification:
	For each test case, output in 3 lines. The first line gives the name and ID of the female student with the highest grade, and the second line gives that of the male student with the lowest grade. The third line gives the difference grade
	​F
	​​ −grade
	​M
	​​ . If one such kind of student is missing, output Absent in the corresponding line, and output NA in the third line instead.

	Sample Input 1:
	3
	Joe M Math990112 89
	Mike M CS991301 100
	Mary F EE990830 95
	Sample Output 1:
	Mary EE990830
	Joe Math990112
	6
	Sample Input 2:
	1
	Jean M AA980920 60
	Sample Output 2:
	Absent
	Jean AA980920
	NA
*/

#include <cstdio>
#include <cstring>
using namespace std;
#define MIN_GRADE -1
#define MAX_GRADE 101

struct Student {
	//学生对象
	char name[50];
	char gender;
	char id[50];
	int grade;
	Student(){}
	void get_from_input() {
		//从输入读取学生信息（姓名、性别、学号、成绩）
		scanf("%s %c %s %d", name, &gender, id, &grade);
	}
	Student(const Student & another) {
		//重写拷贝构造函数
		strcpy(name, another.name);
		gender = another.gender;
		strcpy(id, another.id);
		grade = another.grade;
	}
	void print() {
		//输出
		printf("%s %s\n", name, id);
	}
};
int main() {
	//输入
	int n;
	scanf("%d", &n);
	Student * students = new Student[n];
	for (int i = 0; i < n; ++i) {
		students[i].get_from_input();
	}
	//初始化男生的最低分和女生的最高分两个（虚拟）学生对象
	//初始化最低分为101（上限），最高分为-1（下限）
	Student min_male, max_female;
	min_male.grade = MAX_GRADE;
	max_female.grade = MIN_GRADE;	
	for (int i = 0; i < n; ++i) {
		if (students[i].gender == 'M' && students[i].grade < min_male.grade) {
			//如果是男生并且比最低分低，更改最低分为该男生的分数
			min_male = students[i];
		}
		else if (students[i].gender == 'F' && students[i].grade > max_female.grade) {
			//如果是女生并且比最低分高，更改最低分为该女生的分数
			max_female = students[i];
		}
	}
	bool absent = false;	//用于记录是否没有男生或者女生
	if (max_female.grade == MIN_GRADE) {
		//如果女生最高分为下限，表明没有女生
		absent = true;
		printf("Absent\n");
	}
	else {
		max_female.print();
	}
	if (min_male.grade == MAX_GRADE) {
		//如果男生最低分为上限，表明没有男生
		absent = true;
		printf("Absent\n");
	}
	else {
		min_male.print();
	}
	if (absent) {
		printf("NA\n");
	}
	else {
		printf("%d\n", max_female.grade - min_male.grade);
	}
	return 0;
}
