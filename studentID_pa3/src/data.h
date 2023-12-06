
#include <cstdint>
#include <climits>
#include <vector>

using namespace std;


struct Node{
    // uint64_t num;
    char color;
    int d;
    Node *pi;
    Node() :  color('w'), d(INT_MAX), pi(nullptr) {}
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
        int edgeCount;
        vector<Node> V;
        int vertexCount;
        vector<vector<int>> adj;
        Graph(int numVertices) {
             V.resize(numVertices);
             edgeCount = 0;
             vertexCount = numVertices;
             adj.resize(numVertices);
        }
        ~Graph(){

        }
        void addNode(){
            V.push_back(Node());
            adj.resize(++vertexCount);
        }
        void addEdge(int u, int v, int weight){
            E.push_back(Edge(u,v,weight));
            edgeCount++;
            adj[u].push_back(v);
        }
    private:
        //fucj
};