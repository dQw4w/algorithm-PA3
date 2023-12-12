
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
bool deleteValueFromVector(std::vector<int>& myVector, int valueToDelete) {
    auto it = std::find(myVector.begin(), myVector.end(), valueToDelete);

    // If the value exists, erase it from the vector
    if (it != myVector.end()) {
        myVector.erase(it);
        return true; // Value deleted successfully
    } else {
        return false; // Value not found in the vector
    }
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
bool DFSVisit(Graph &G, int u, bool directed, int &totalWeight, vector<pair<int,int>> &removedEdges){
    Node &U = G.V[u];
    U.color = 'u';
    // cout << "curnode = " << u << endl;
    for (auto v : G.adj[u]){
        // if (v == U.pi->num){
        //     continue;
        // }
        Node &V = G.V[v];
        
        
        switch (V.color)
        {
        case 'w':
            V.pi = &U;
            if (DFSVisit(G,v, directed, totalWeight, removedEdges)){
                return true;
            };
            break;
        case 'u':
            if (!U.pi){
                break;
            }
            if (v != U.pi->num){
                cout << "has cycle\n";
                Node* ptr = &U;
                int minWeight = INT_MAX;
                int node1, node2;
                while (ptr && ptr->pi){
                    // if (minWeight > G.w[ptr->num][ptr->pi->num]){
                    //     minWeight = G.w[ptr->num][ptr->pi->num];
                    // }
                     cout << ptr->num << endl;
                    if (ptr->num == v){
                        break;
                    }
                    if (minWeight > G.w[ptr->num][ptr->pi->num]){
                        minWeight = G.w[ptr->num][ptr->pi->num];
                        node1 = ptr->num;
                        node2 = ptr->pi->num;
                    }
                    ptr = ptr->pi;
                }
                cout << "min weight = "<< minWeight << endl;
                deleteValueFromVector(G.adj[node2],node1);
                G.w[node2][node1] = INT_MAX;

                if (directed){
                    deleteValueFromVector(G.adj[node1],node2);
                    G.w[node1][node2] = INT_MAX;
                }
                totalWeight += minWeight;
                removedEdges.push_back(make_pair(node1,node2));

                // for (int i = 0; i < G.adj.size(); i++){
                //     cout << i << ": ";
                //     for (int j = 0; j < G.adj[i].size(); j++){                  
                //         cout << j << " ";
                //     }
                //     cout << endl;
                // }
                // G.haha();
                cout << "vistit returned true"<< endl;
                return true;
            }
            break;
        default:
            break;
        }
        // if (V.color == 'w'){
            
        //     continue;
        // }
        // if (V.color)
    }
    U.color = 'b';
    cout << "visit returned false " << endl;

    return false;
}
bool DFS(Graph &G, bool directed,int &totalWeight, vector<pair<int,int>> &removedEdges){
    cout << "DFS called" << endl;
    for (auto &U : G.V){
        U.color= 'w';
        U.d = 0;
        U.pi = nullptr;
    }
    for (int u = 0; u < G.vertexCount; u++){
        cout << "DFS visit on node "<< u << endl;
        if (G.V[u].color == 'w'){
            
                    cout << "white is the node "<< u << endl;


            bool flag = DFSVisit(G,u, directed, totalWeight, removedEdges);
            if (flag){
                cout << "DFS accept visit return false " << endl;
                cout << "DFS returned true" << endl;
                return true;
            }
            // if (DFSVisit(G,u, directed, totalWeight, removedEdges)){
            //     cout << "DFS returned true" << endl;
            //     return true;
            // }
            else{
                cout << "DFS accept visit return false " << endl;
            }
        }
        cout << "DFS visit on node "<< u <<  " is over"<< endl;

    }
    cout << "DFS returned false" << endl;
    return false;
    

}
int main(int argc, char* argv[]) {
    // ./bin/cb inputs/
    // for (int i = 0; i < 9; i ++){
    //     cout << "./bin/cb inputs/public_case_" << i<< ".in outputs/" << i<< ".out" << endl;
    // }
    // cout << "jfjfjfjf "<< endl;//
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

    // cout << "here" << endl;
    char type;
    int n,m;
    bool directed = false;
    fin >> type;
    if (type == 'u'){
        directed = true;
    }
    fin >> n;
    fin >> m;
    // cout << "heressss" << endl;

    Graph G(n);
            // cout << "heress" << endl;
    
    // int num1, num2
    int i,j;
    int w;
    // cout << "n = " << n << "\nm = " <<m << endl;//
    for (int k = 0; k < m; k++){
        fin >> i >> j >> w;
        // cout << i << ' '<< j<< ' '<< w << endl;
        // cout << i << "," << j << "," << w << endl;//
        G.addEdge(i,j,w);
        if (directed){
            G.addEdge(j,i,w);
        }
        // if (i == 7){
        //     // G.haha();
        // }
    }
    // G.haha();

    tmusg.periodStart();
    // 。(G,0);
    // G.printEdge();/////
    int totalWeight = 0; 
    vector<pair<int,int>> removedEdges = {};
    while (true){
        if (!DFS(G,directed,totalWeight,removedEdges)){
            break;
        }
        else {
            cout << "returned true" << endl;
        }
    };
    fout << totalWeight << endl;
    for (auto i : removedEdges){
        fout << i.first << " " << i.second << endl;
    }
    // for (int i = 0; i < G.vertexCount; i++){
    //     Node v = G.V[i];
    //     cout <<"vertex num " << i << endl;
    //     cout << "color = " << v.color << endl;
    //     cout << "d = " << v.d << endl;
    //     cout << "-----------------------------\n";//
    //     // cout << v.color
    // }
    // init(verticeNum);

    // fout << maximumPlanarSubset(0,verticeNum-1) << endl;
    // // fout << mstBottomUp(verticeNum) << endl;//

    

    // output(fout, 0, verticeNum-1);
    
    tmusg.getPeriodUsage(stat);

    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout << "memory: " << stat.vmPeak << "KB" << endl; // Print peak memoss

    G.haha();

    fin.close();
    fout.close();
    return 0;
}
