#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
const int SIZE = 29;//城市数量
const int MAX_ITERATION = 50;//最大迭代次数
const int ANT_NUM = 40;//蚁群个数

string tsp_inf("/Users/pangyusheng/Desktop/PROG/C++/TSP_AC/bays29.tsp");
int dis;
const int delta = 1;//浓度有关的系数
const int beta = 5;//启发值eta有关的参数
double rho = 0.8;//信息素挥发率

double dis_mtx[SIZE][SIZE];
double (*p)[SIZE];
double tab_pheromones[SIZE][SIZE];//记录各个边信息素的值
double record_iter_sol[MAX_ITERATION + 10][SIZE + 10];
int Node_Set[SIZE];

void separate(){
    cout << "=========================================="<< endl;
}
void io(string path, bool show = false){
    p = dis_mtx;
    int num;
    int n = 1;
    stringstream num_line;//ss流，用于string 2 int
    ifstream ReadFile;//文件输入流
    ReadFile.open(path);
    string line;//读取行
    bool to_matrix_begin = false;
    bool to_matrix_end = false;
    if(ReadFile.is_open()){
        cout <<"Open Success!" <<endl;
        while(!ReadFile.eof() && !to_matrix_begin){
            getline(ReadFile, line);
            if(line == "EDGE_WEIGHT_SECTION"){
                cout << "GET" << endl;
                separate();
                cout << "No." << n << " line" <<endl;
                to_matrix_begin = true;
            }
        n++;
        }
        int i=0,j = 0;
        while(!ReadFile.eof() && !to_matrix_end){

            getline(ReadFile, line);
            if(line == "DISPLAY_DATA_SECTION"){
                cout << "matrix to the end" << endl;
                separate();
                to_matrix_end = true;
            }
            else{
                num_line << line;
                while(num_line >> num){
                    p[i][j] = num;
                    j++;
                }
                num_line.clear();//不清理缓冲区的话，都是零
                j = 0;
                i++;
            }
        }
    }
    ReadFile.close();
    if(show) {
        cout << "DISTANCE MATRIX:" << endl;
        separate();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
                cout << dis_mtx[i][j] << ' ';
            cout << endl;
        }
    }
}//将.tsp文件导入到dis_mtx中
void init_pheromones(){
    double mean = 0;
    for(int i = 0;i < SIZE; i++)
        for(int j = i;j < SIZE; j++)
            mean += dis_mtx[i][j];
    mean = (SIZE - 1)/(2*mean);

    for(int i = 0;i < SIZE; i++)
        for(int j = 0;j < SIZE; j++)
            tab_pheromones[i][j] = mean;

}//初始化<i,j>的信息素的值
void init_Node_SET(){
    for(int i = 0;i < SIZE;i++){
        Node_Set[i] = i + 1;
    }
};//产生一个包含node需要的数组
//double gen_rand(){srand((double)time(0));return ((double)rand()/RAND_MAX);}

class ant{
public:
    const double (*dis_inf)[SIZE];//读取距离信息
    const double (*tab_inf)[SIZE];//读取各个边信息素的值
    set<int>unvisited_node;//未选取节点
    list<int>visited_node;//已选取节点
    double random;
    int current_node;//当前节点
    int start_node;
    int next_node;
    double dis = 0.0;
    ant();
    ant(int str_node, const double (*dis)[SIZE], const double (*tab_)[SIZE]){
        start_node = str_node;
        current_node = str_node;
        dis_inf = dis;
        tab_inf = tab_;
//        copy(Node_Set + 0, Node_Set + SIZE, unvisited_node);
        for(int x:Node_Set)
            unvisited_node.insert(x);

//        visited_node.push_back(start_node);
    };
    void next_step(){
//        double rand = gen_rand();
//        cout << rand <<endl;
        double sum = 0.0;
        double sum_2 = 0.0;
        auto it = unvisited_node.begin();
        //先求总和，因为要归一化
        for(auto itt = unvisited_node.begin(); itt != unvisited_node.end();itt++)
            if(*itt != start_node)
                sum_2 += pow(tab_inf[current_node - 1][*itt - 1], delta)*pow(1.0/dis_inf[current_node - 1][*itt - 1], beta);
            else
                continue;//当unvisited.size() == 1的时候，跳过这个，sum_2 = 0.0

        if(!sum_2){
            dis += dis_inf[current_node - 1][start_node - 1];
            visited_node.push_back(start_node);
            unvisited_node.clear();
            return;
        }

        random = rand()/double(RAND_MAX);
//        cout << random<< endl;

        for(; unvisited_node.size() != 1; it++){
            if(*it == start_node)
                continue;
            else{
                sum += (pow(tab_inf[current_node - 1][*it - 1], delta)*pow(1.0/dis_inf[current_node - 1][*it - 1], beta)/sum_2);
                if(sum >= random){
                    next_node = *it;
                    dis += dis_inf[current_node - 1][next_node - 1];

                    visited_node.push_back(current_node);
                    current_node = next_node;
                    unvisited_node.erase(current_node);
                    break;
                }
            }
        }
    }
    void clear(bool test = false){//这里有点深坑啊，直接把unvisited_node清除了，应该改成把所有节点又添加到unvisited_node中
        current_node = start_node;

        visited_node.clear();
//        visited_node.push_back(start_node);

        unvisited_node.clear();
        for(int x:Node_Set)
            unvisited_node.insert(x);
        dis = 0.0;
        if(test)
            cout <<"clear success" << endl;
    }
    void show(){
        cout << "总爬行距离： " << dis << endl;
        cout << "路径: " << endl;
        auto x = visited_node.begin();
        for(; x != --visited_node.end(); x++)
            cout << *x << " -> ";
        cout << *x;
        cout << endl;

    }

};

void update(vector<ant> &group) {
    for (int i = 0; i < SIZE; i++)
        for (int j = i; j < SIZE; j++)
            tab_pheromones[i][j] *= rho;
    for (auto it = group.begin(); it != group.end(); it++) {//每一只蚂蚁
        for (auto start = (it->visited_node).begin();
             start != --(it->visited_node).end(); start++) {//每一只蚂蚁的visited_node
            tab_pheromones[*start - 1][*(++start) - 1] += 1.0 / (it->dis);
        }
    }
}


int main() {
    srand(time(NULL));//这个的位置别放错了，不然生成的随机数都是一样的。。
    io(tsp_inf);
    init_pheromones();
    init_Node_SET();
    double tol_dis = 0;
    double min = 8000;
    vector<int>it_best_res;
    double it_min=8000;
    vector<int>best(29);
    vector<ant>group;
    for(int ant_num = 0; ant_num < ANT_NUM; ant_num++)
        group.push_back(ant(5, dis_mtx, tab_pheromones));

    for(int it = 0; it < MAX_ITERATION; it++) {
       for(int ant_num = 0; ant_num < ANT_NUM;ant_num++){
            for (int i = 0; i < SIZE; i++)
                group[ant_num].next_step();

            if(group[ant_num].dis < it_min)
                it_min = group[ant_num].dis;
            if(group[ant_num].dis < min) {
                min = group[ant_num].dis;
                copy(group[ant_num].visited_node.begin(), group[ant_num].visited_node.end(), best.begin());
            }
       }
       it_best_res.push_back(it_min);
       it_min = 8000;
       update(group);
       for(auto it = group.begin(); it != group.end();it++)
           it->clear();
    }
    cout << "shortest path distance: " << min << endl;
    cout << "best result of iteration:  "<< endl;
    for(int result : it_best_res)
        cout << result << endl;
//    cout << "shortest path: " << endl;
//    auto x = best.begin();
//    for(; x != --best.end(); x++)
//        cout << *x << " -> ";
//    cout << *x;
//    cout << endl;
    return 0;
}
