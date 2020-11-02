//
// Created by 庞泽钊 on 2020/10/25.
//

/*
language: C++ 11
Athour: Xing He
School: HuaZhong University of science and technology
compilier: g++.exe ACS.cpp -o ACS.exe -Ofast -std=c++11


File_name 		File_type
salesman.in	 	1
5
0 1 2 2 3
2 0 3 4 2
3 2 0 4 1
3 4 5 0 5
2 4 1 4 0

opt_solution:
11


File_name		File_type
KroA100.tsp     2
100
1 1380 939
2 2848 96
3 3510 1671
4 457 334
5 3888 666
6 984 965
7 2721 1482
8 1286 525
9 2716 1432
10 738 1325
11 1251 1832
12 2728 1698
13 3815 169
14 3683 1533
15 1247 1945
16 123 862
17 1234 1946
18 252 1240
19 611 673
20 2576 1676
21 928 1700
22 53 857
23 1807 1711
24 274 1420
25 2574 946
26 178 24
27 2678 1825
28 1795 962
29 3384 1498
30 3520 1079
31 1256 61
32 1424 1728
33 3913 192
34 3085 1528
35 2573 1969
36 463 1670
37 3875 598
38 298 1513
39 3479 821
40 2542 236
41 3955 1743
42 1323 280
43 3447 1830
44 2936 337
45 1621 1830
46 3373 1646
47 1393 1368
48 3874 1318
49 938 955
50 3022 474
51 2482 1183
52 3854 923
53 376 825
54 2519 135
55 2945 1622
56 953 268
57 2628 1479
58 2097 981
59 890 1846
60 2139 1806
61 2421 1007
62 2290 1810
63 1115 1052
64 2588 302
65 327 265
66 241 341
67 1917 687
68 2991 792
69 2573 599
70 19 674
71 3911 1673
72 872 1559
73 2863 558
74 929 1766
75 839 620
76 3893 102
77 2178 1619
78 3822 899
79 378 1048
80 1178 100
81 2599 901
82 3416 143
83 2961 1605
84 611 1384
85 3113 885
86 2597 1830
87 2586 1286
88 161 906
89 1429 134
90 742 1025
91 1625 1651
92 1187 706
93 1787 1009
94 22 987
95 3640 43
96 3756 882
97 776 392
98 1724 1642
99 198 1810
100 3950 1558

best_known_solution: 21282

使用本程序的时候只需要建立一个上述文件名的文档，
放在与源程序同目录下面，
并运行程序，输入文件名以及数据类型。
例如：
运行程序之后会遇到以下提升：
 input file_name and data type
 只需要输入
KroA100.tsp     2
即可得到一个启发解以及相应路径
更多的数据可以从TSPLIB下载。
*/





#include<bits/stdc++.h>
using namespace std;
// const
const int INF = 0x3f3f3f3f;
#define sqr(x) ((x)*(x))
#define eps 1e-8
//variables
string file_name;
int type;// type == 1 全矩阵, type == 2 二维欧拉距离
int N;//城市数量
double **dis;//城市间距离
double **pheromone;//信息素
double **herustic;//启发式值
double **info;// info = pheromone ^ delta * herustic ^ beta
double pheromone_0;//pheromone初始值，这里是1 / (avg * N)其中avg为图网中所有边边权的平均数。
int m;//种群数量
int delta, beta;//参数
double alpha;
int *r1, *s, *r;//agent k的出发城市，下一个点，当前点。
int MAX, iteration;//最大迭代次数，迭代计数变量
set<int> empty, *J;
struct vertex{
    double x, y;// 城市坐标
    int id;// 城市编号

    int input(FILE *fp){
        return fscanf(fp, "%d %lf %lf", &id, &x, &y);
    }

}*node;

typedef pair<int, int> pair_int;
struct Tour{//路径
    vector<pair_int> path;//path[i]，存储一条边(r,s)
    double L;

    void clean(){
        L = INF;
        path.clear();
        path.shrink_to_fit();
    }//清空

    void calc(){
        L = 0;
        int sz = path.size();
        for (int i = 0; i < sz; i ++){
            L += dis[path[i].first][path[i].second];
        }
    }//计算长度

    void push_back(int x, int y){
        path.push_back(make_pair(x, y));
    }

    int size(){
        return (int)path.size();
    }

    int r(int i){
        return path[i].first;
    }

    int s(int i){
        return path[i].second;
    }

    void print(FILE *fp){
        int sz = path.size();
        for (int i = 0; i < sz; i ++){
            fprintf(fp, "%d->", path[i].first + 1);
        }
        fprintf(fp, "%d\n", path[sz - 1].second + 1);
    }

    bool operator <(const Tour &a)const{
        return L < a.L;
    }//重载

} *tour, best_so_far;

double EUC_2D(const vertex &a, const vertex &b){
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

void io(){//输入
    printf("input file_name and data type\n");
    cin >> file_name >> type;
    FILE *fp = fopen(file_name.c_str(), "r");
    fscanf(fp, "%d", &N);
    node = new vertex[N + 5];
    dis = new double*[N + 5];
    double tmp = 0;
    int cnt = 0;
    if (type == 1){
        for (int i = 0; i < N; i ++){
            dis[i] = new double[N];
            for (int j = 0; j < N; j ++){
                fscanf(fp, "%lf", &dis[i][j]);
                tmp += i != j ? dis[i][j] : 0;// i == j的时候 dis不存在，所以不考虑。
                cnt += i != j ? 1 : 0;// i == j的时候 dis不存在，所以不考虑。
            }
        }
    }else{
        for (int i = 0; i < N; i ++)
            node[i].input(fp);
        for (int i = 0; i < N; i ++){
            dis[i] = new double[N];
            for (int j = 0; j < N; j ++){
                dis[i][j] = EUC_2D(node[i], node[j]);// 计算距离
                tmp += i != j ? dis[i][j] : 0;// i == j的时候 dis不存在，所以不考虑。
                cnt += i != j ? 1 : 0;// i == j的时候 dis不存在，所以不考虑。
            }
        }
    }
    pheromone_0 =  (double)cnt / (tmp * N);//pheromone初始值，这里是1 / (avg * N)其中avg为图网中所有边边权的平均数。
    fclose(fp);
    return;
}

void init(){//初始化
    alpha = 0.1;//evaporation parameter，挥发参数，每次信息素要挥发的量
    delta = 1;
    beta = 6;// delta 和 beta分别表示pheromones 和 herustic的比重
    m = N;
    pheromone = new double*[N + 5];
    herustic = new double*[N + 5];
    info = new double*[N + 5];
    r1 = new int[N + 5];
    r = new int[N + 5];
    s = new int[N + 5];
    J = new set<int>[N + 5];
    empty.clear();
    for (int i = 0; i < N; i ++){
        pheromone[i] = new double[N + 5];
        herustic[i] = new double[N + 5];
        info[i] = new double[N + 5];
        empty.insert(i);
        for (int j = 0; j < N; j ++){
            pheromone[i][j] = pheromone_0;
            herustic[i][j] = 1 / (dis[i][j] + eps);//加一个小数eps，防止被零除
        }
    }
    best_so_far.clean();
    iteration = 0;
    MAX = N * N;
}

double power(double x, int y){//快速幂，计算x ^ y，时间复杂度O(logn),感兴趣可以百度
    double ans = 1;
    while (y){
        if (y & 1) ans *= x;
        x *= x;
        y >>= 1;
    }
    return ans;
}

void reset(){
    tour = new Tour[m + 5];
    for (int i = 0; i < N; i ++){
        tour[i].clean();
        r1[i] = i;//初始化出发城市，
        J[i] = empty;
        J[i].erase(r1[i]);//初始化agent i需要访问的城市
        r[i] = r1[i];//当前在出发点
    }
    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++){
            info[i][j] = power(pheromone[i][j], delta) * power(herustic[i][j], beta);
        }//选择公式
}

int select_next(int k){
    if (J[k].empty()) return r1[k]; //如果J是空的，那么返回出发点城市
    double rnd = (double)(rand()) / (double)RAND_MAX;//产生0..1的随机数
    set<int>::iterator it = J[k].begin();
    double sum_prob = 0, sum = 0;
    for (; it != J[k].end(); it ++){
        sum += info[r[k]][*it];
    }//计算概率分布
    rnd *= sum;
    it = J[k].begin();
    for (; it != J[k].end(); it ++){
        sum_prob += info[r[k]][*it];
        if (sum_prob >= rnd){
            return *it;
        }
    }//依照概率选取下一步城市
}

void construct_solution(){
    for (int i = 0; i < N; i ++){
        for (int k = 0; k < m; k ++){
            int next = select_next(k);//选择下一步的最优决策
            J[k].erase(next);
            s[k] = next;
            tour[k].push_back(r[k], s[k]);
            r[k] = s[k];
        }
    }
}

void update_pheromone(){
    Tour now_best;
    now_best.clean();//初始化
    for (int i = 0; i < m; i ++){
        tour[i].calc();
        if (tour[i] < now_best)
            now_best = tour[i];//寻找当前迭代最优解
    }
    if (now_best < best_so_far){
        best_so_far = now_best;//更新最优解
    }
    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++)
            pheromone[i][j] *= (1 - alpha);//信息素挥发

    int sz = now_best.size();
    for (int i = 0; i < sz; i ++){
        pheromone[now_best.r(i)][now_best.s(i)] += 1. / (double)now_best.L;
        pheromone[now_best.s(i)][now_best.r(i)] = pheromone[now_best.r(i)][now_best.s(i)];//对称
    }//更新信息素含量

}

int main(){
    srand((unsigned) time(0));//初始化随机种子
    io();
    init();
    double last = INF;
    int bad_times = 0;
    for (; iteration < MAX; iteration ++){
        if (bad_times > N) break;//进入局部最优
        reset();//初始化agent信息
        construct_solution();//对于所有的agent构造一个完整的tour
        update_pheromone();//更新信息素
        printf("iteration %d:best_so_far = %.2lf\n", iteration, best_so_far.L);
        if (last > best_so_far.L)
            last = best_so_far.L, bad_times = 0;
        else bad_times ++;//记录当前未更新代数，若迭代多次未更新，认为进入局部最优
    }
    printf("best_so_far = %.2lf\n", best_so_far.L);//输出目标值
    best_so_far.print(stdout);//输出路径