/*
    1090 Highest Price in Supply Chain （25 分)
    A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone involved in moving a product from supplier to customer.

    Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P and sell or distribute them in a price that is r% higher than P. It is assumed that each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.

    Now given a supply chain, you are supposed to tell the highest price we can expect from some retailers.

    Input Specification:
    Each input file contains one test case. For each case, The first line contains three positive numbers: N (≤10
    ​5
    ​​ ), the total number of the members in the supply chain (and hence they are numbered from 0 to N−1); P, the price given by the root supplier; and r, the percentage rate of price increment for each distributor or retailer. Then the next line contains N numbers, each number S
    ​i
    ​​  is the index of the supplier for the i-th member. S
    ​root
    ​​  for the root supplier is defined to be −1. All the numbers in a line are separated by a space.

    Output Specification:
    For each test case, print in one line the highest price we can expect from some retailers, accurate up to 2 decimal places, and the number of retailers that sell at the highest price. There must be one space between the two numbers. It is guaranteed that the price will not exceed 10
    ​10
    ​​ .

    Sample Input:
    9 1.80 1.00
    1 5 4 4 -1 4 5 3 6
    Sample Output:
    1.85 2
*/

#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
struct Shop{
    //零售商/经销商类
    vector<int> next_shops; //它供应的下家零售商/经销商
    bool visited;   //它是否在BFS中被访问过
    int height;   //在BFS中它的高度（深度）
    Shop():visited(false), height(0){}
};
Shop * shops;
void bfs(int root, int & height, vector<Shop> & last_members){
    //广度优先搜索

    //Open队列
    queue<Shop> remains;
    //放入初始的根节点
    remains.push(shops[root]);
    height = 0;
    while (!remains.empty()){
        //取出队列的头元素
        Shop temp_shop = remains.front();
        remains.pop();
        //如果搜索到树新的一层，则清空存储前面一层的数组
        if (temp_shop.height > height){
            ++height;
            last_members.clear();
        }
        //将节点放入存储（到目前为止）最深一层的节点的数组
        last_members.push_back(temp_shop);
        for (int i = 0; i < temp_shop.next_shops.size(); ++i){
            //寻找当前节点毗邻且没被访问过的元素，高度等于当前节点的高度+1，加入open表
            //并且设置visited为true
            int index = temp_shop.next_shops[i];
            if (!shops[index].visited){
                shops[index].visited = true;
                shops[index].height = height + 1;
                remains.push(shops[index]);
            }
        }
    }
}
int main(){
    //输入第一行
    int n, root;
    double begin_price, add_price;
    scanf("%d%lf%lf", &n, &begin_price, &add_price);
    shops = new Shop[n];
    //依据第二行的输入保存零售商/经销商的下家零售商/经销商
    for (int i = 0; i < n; ++i){
        int up_shop;
        scanf("%d", &up_shop);
        if (up_shop >= 0){
            shops[up_shop].next_shops.push_back(i);
        }
        else {
            root = i;
        }
    }
    //进行bfs
    int max_len;
    vector<Shop> last_members;
    bfs(root, max_len, last_members);
    //计算最终的出售价格（与高度呈指数关系）和最深一层的元素个数
    printf("%.2f %d\n", begin_price * pow((1 + add_price / 100), max_len), last_members.size());
    return 0;
}