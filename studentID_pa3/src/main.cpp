
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include<algorithm>
#include <queue>
#include "../lib/tm_usage.h"
#include "data.h"
#define ll long long

using namespace std;

void help_message() {
    cout << "usage: cb <input_file> <output_file>" << endl;
}

int dequeue(queue<int> &Q){
    int val = Q.front();
    Q.pop();
    return val;
}

void BFS(Graph &G, int s){
    for (int i = 0; i < G.vertexCount; i++){
        Node &u = G.V[i];
        if (i == s){
            u.color= 'g';
            u.d = 0;
            u.pi = nullptr;
            continue;
        }
        u.color = 'w';
        u.d = INT_MAX;
        u.pi = nullptr;
    }
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()){
        int u = dequeue(Q);
        Node &U = G.V[u];
        for (auto v: G.adj[u]){
            
            Node &V = G.V[v];
            if (V.color == 'w'){
                V.color = 'g';
                V.d = U.d + 1; //TODO: weight func
                V.pi = &U;
                Q.push(v);
            }
        }
        U.color = 'b';
    }
    
}
int main(int argc, char* argv[]) {
    // ./bin/cb inputs/
    // for (int i = 0; i < 9; i ++){
    //     cout << "./bin/cb inputs/public_case_" << i<< ".in outputs/" << i<< ".out" << endl;
    // }
    if (argc != 3) {
        help_message();
        return 0;
    }

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
    fstream fin(argv[1]); // Open the input files
    if (!fin.is_open()) {
        cout << "Error: Unable to open input file." << endl;
        return 1;
    }

    fstream fout;
    fout.open(argv[2], ios::out);
    if (!fout.is_open()) {
        cout << "Error: Unable to open output file." << endl;
        return 1;
    }


    char type;
    int n,m;
    fin >> type;
    fin >> n;
    fin >> m;
    Graph G(n);
    // int num1, num2
    int i,j;
    int w;
    cout << "n = " << n << "\nm = " <<m << endl;
    for (int k = 0; k < m; k++){
        fin >> i >> j >> w;
        cout << i << "," << j << "," << w << endl;
        G.addEdge(i,j,w);
    }
    tmusg.periodStart();
    BFS(G,0);
    for (int i = 0; i < G.vertexCount; i++){
        Node v = G.V[i];
        cout <<"vertex num " << i << endl;
        cout << "color = " << v.color << endl;
        cout << "d = " << v.d << endl;
        cout << "-----------------------------\n";
        // cout << v.color
    }
    // init(verticeNum);

    // fout << maximumPlanarSubset(0,verticeNum-1) << endl;
    // // fout << mstBottomUp(verticeNum) << endl;//

    

    // output(fout, 0, verticeNum-1);
    
    tmusg.getPeriodUsage(stat);

    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout << "memory: " << stat.vmPeak << "KB" << endl; // Print peak memoss

 

    fin.close();
    fout.close();
    return 0;
}
