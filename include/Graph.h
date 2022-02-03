#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include"UnionFindSet.h"
#include"NodeHeap.h"

using namespace std;
using Mat = vector<vector<int>>;

class Node;
class Edge;
class Graph;
class NodeHeap;
vector<Node*> sortedTopology(Graph&);
unordered_set<Edge*> kruskalMST(Graph&);
unordered_set<Edge*> primMST(Graph&);
unordered_map<Node*, double> dijkstra(Graph&, Node*);

class Node {
    friend ostream&operator<<(ostream&os, Node&node);
    friend struct hash<Node>;
    friend class Graph;
    friend class NodeHeap;
    friend vector<Node*> sortedTopology(Graph&);
    friend unordered_set<Edge*> primMST(Graph&);
    friend unordered_map<Node*, double> dijkstra(Graph&, Node*);
    int _id;
    int _in;
    int _out;
    vector<Node*> _nexts;
    vector<Edge*> _edges;
public:
    explicit Node(int id) : _id(id), _in(0), _out(0), _nexts(vector<Node*>()), _edges(vector<Edge*>()) { }
    bool operator==(Node& rhs) const { return this->_id == rhs._id; }
};

namespace std {
    template<>
    struct hash<Node> {
        size_t operator()(const Node& node) const { return node._id; }
    };
}

class Edge {
    friend ostream&operator<<(ostream&os, Edge&edge);
    friend struct CmpEdgePtrs;
    friend class NodeHeap;
    friend unordered_set<Edge*> kruskalMST(Graph&);
    friend unordered_set<Edge*> primMST(Graph&);
    friend unordered_map<Node*, double> dijkstra(Graph&, Node*);
    double _w;
    Node* _src;
    Node* _dst;
public:
    Edge(double w, Node* src, Node* dst) : _w(w), _src(src), _dst(dst) { }
    [[nodiscard]] double getWeight() const { return _w; }
};

struct CmpEdgePtrs {
    bool operator()(const Edge* lhs, const Edge* rhs) const {
        return lhs->_w > rhs->_w;
    }
};

class Graph {
    friend class NodeHeap;
    friend vector<Node*> sortedTopology(Graph&);
    friend unordered_set<Edge*> kruskalMST(Graph&);
    friend unordered_set<Edge*> primMST(Graph&);
    friend unordered_map<Node*, double> dijkstra(Graph&, Node*);
    unordered_map<int, Node*> _nodes;
    unordered_set<Edge*> _edges;
public:
    static const int INF = 0x7fffffff;
    explicit Graph(Mat&);
    Node* getNode(int id) { return _nodes[id]; }
    ~Graph();
    static void dfs(Node*);
    static void bfs(Node*);
};
