
#include <cstdint>
#include <climits>
#include <vector>

using namespace std;


struct Node{
    int num;
    char color;
    int d;
    Node *pi;
    Node() :  color('w'), d(INT_MAX), pi(nullptr) {}
    Node(int n) : num(n){}
    // Node(uint64_t num) : num(num), color('w'), d(INT_MAX), pi(nullptr) {}
    // Constructor with parameters
    Node(  char c, int distance, Node* parent) :  color(c), d(distance), pi(parent) {}
};

struct Edge{
    int u;
    int v;
    int  weight;
    // Constructor with parameters
    Edge(int u , int v,int weight) : u(u), v(v), weight(weight) {}
};



class Graph{
    public:
        vector<Edge> E;
        int edgeCount= 0;
        vector<Node> V;
        int vertexCount = 0;
        vector<vector<int>> adj;
        vector<vector<int>> w;
        Graph(int numVertices) {
            for(int i = 0; i < numVertices; i++){
                addNode();
            }
            //  V.resize(numVertices);
            // edgeCount = 0;
            // cout << "end" << endl;
            w.resize(vertexCount);
            for (auto &i : w){
                i.resize(vertexCount);
                for (auto &j : i){
                    j = INT_MAX;
                }
            }
            //  vertexCount = numVertices;
            //  adj.resize(numVertices);
        }
        ~Graph(){

        }
        void addNode(){
            // V.push_back(Node());
            V.push_back(Node(vertexCount));
            adj.resize(++vertexCount);
        }
        void addEdge(int u, int v, int weight){
            E.push_back(Edge(u,v,weight));
            edgeCount++;
            // cout << "adding " << u << " " << v << endl;
            adj[u].push_back(v);
            // for (auto i : adj[u]){
            //     cout << i << endl;
            // }
            w[u][v] = weight;
        }
        void haha(){
            for (int i = 0; i < adj.size(); i++){
                    cout << i << ": ";
                    for (int j = 0; j < adj[i].size(); j++){                  
                        cout << adj[i][j] << " ";
                    }
                    cout << endl;
                }
        }
        void printEdge(){
            for (int i = 0; i < vertexCount; i++){
                for (int j = 0; j < vertexCount; j++){
                    cout << "w[" << i<< "][" << j << "] = " << w[i][j] << endl;
                }
            }
        }
    private:
        //fucj
};