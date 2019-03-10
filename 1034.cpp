/*
    1034 Head of a Gang （30 分）
    One way that the police finds the head of a gang is to check people's phone calls. If there is a phone call between A and B, we say that A and B is related. The weight of a relation is defined to be the total time length of all the phone calls made between the two persons. A "Gang" is a cluster of more than 2 persons who are related to each other with total relation weight being greater than a given threthold K. In each gang, the one with maximum total weight is the head. Now given a list of phone calls, you are supposed to find the gangs and the heads.

    Input Specification:
    Each input file contains one test case. For each case, the first line contains two positive numbers N and K (both less than or equal to 1000), the number of phone calls and the weight threthold, respectively. Then N lines follow, each in the following format:

    Name1 Name2 Time
    where Name1 and Name2 are the names of people at the two ends of the call, and Time is the length of the call. A name is a string of three capital letters chosen from A-Z. A time length is a positive integer which is no more than 1000 minutes.

    Output Specification:
    For each test case, first print in a line the total number of gangs. Then for each gang, print in a line the name of the head and the total number of the members. It is guaranteed that the head is unique for each gang. The output must be sorted according to the alphabetical order of the names of the heads.

    Sample Input 1:
    8 59
    AAA BBB 10
    BBB AAA 20
    AAA CCC 40
    DDD EEE 5
    EEE DDD 70
    FFF GGG 30
    GGG HHH 20
    HHH FFF 10
    Sample Output 1:
    2
    AAA 3
    GGG 3
    Sample Input 2:
    8 70
    AAA BBB 10
    BBB AAA 20
    AAA CCC 40
    DDD EEE 5
    EEE DDD 70
    FFF GGG 30
    GGG HHH 20
    HHH FFF 10
    Sample Output 2:
    0
*/

#include <cstdio>
#include <map>
#include <set>
#include <string>
#include <queue>
using namespace std;

map<string, set<string> > relationships;    //表示与一个人通过电话的若干个人
map<string, int> time_count;    //表示一个人通电话的总时间
map<string, bool> visited;      //表示广度优先搜索中这个人是否被访问过
set<pair<string, int> > headers;    //表示最终结果：某个团伙和总通话时间的集合
int min_weight;     //表示要成为一个团伙，需要的最小总通话时间

void bfs(const string & str){
    //广度优先搜索，找到与str相关的某个团伙，如果符合条件则添加到结果数组headers

    //先添加第一个人到广度搜索队列中
    queue<string> bfs_queue;
    bfs_queue.push(str);
    visited[str] = true;

    //记录具有最长通话时间的某个人名及其对应的总通话时间
    pair<string, int> max_person;
    //记录团伙具有的人数和整个团伙的总通话时间（的两倍）
    int counter = 0, sum = 0;
    while (!bfs_queue.empty()){
        //从队列中去除一个人名
        string temp_str = bfs_queue.front();
        bfs_queue.pop();

        //如果这个人总通话时间大于当前的最长通话时间，更新最长通话时间
        if (time_count[temp_str] > max_person.second){
            max_person.first = temp_str;
            max_person.second = time_count[temp_str];
        }
        //更新团伙总通话时间和总人数
        sum += time_count[temp_str];
        ++counter;

        //寻找和这个人有关的且未遍历过的人，添加到队列中
        set<string> relations = relationships[temp_str];
        for (set<string>::iterator it = relations.begin(); it != relations.end(); ++it){
            if (!visited[*it]){
                bfs_queue.push(*it);
                visited[*it] = true;
            }
        }
    }
    if (counter > 2 && sum > 2 * min_weight){
        //如果符合要求，则添加到结果数组
        //min_weight乘以2是因为算出的总的通话时间事实上是两倍的总通话时间（每次通话被算了两次）
        headers.insert(pair<string, int>(max_person.first, counter));
    }
}

int main(){
    //输入
    int n;
    scanf("%d%d", &n, &min_weight);

    for (int i = 0; i < n; ++i){
        //对于输入的每组数据
        char temp_a[10], temp_b[10];
        scanf("%s%s", temp_a, temp_b);
        //两人分别在各自的关系集合中添加对方
        relationships[temp_a].insert(temp_b);
        relationships[temp_b].insert(temp_a);
        int temp_time;
        scanf("%d", &temp_time);
        //两人分别在各自的总通话时间集合中添加通话时间
        //这样使得最终算出的所有人的总通话时间事实上是两倍（算了两遍）
        time_count[temp_a] += temp_time;
        time_count[temp_b] += temp_time;
        //初始化bfs中的visited数组，表明bfs还没访问过这个人
        visited[temp_a] = visited[temp_b] = false;
    }

    for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); ++it){
        //如果某个人还没访问过，说明是一个新的团伙
        if (it -> second){
            continue;
        }
        //从这个人开始进行广度优先搜索
        bfs(it->first);
    }

    //输出最终结果headers
    printf("%d\n", headers.size());
    for (set<pair<string, int> >::iterator it = headers.begin(); it != headers.end(); ++it){
        printf("%s %d\n", it->first.c_str(), it->second);
    }
    return 0;
}