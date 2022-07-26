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

class Node {
    friend ostream&operator<<(ostream&os, Node&node);
    friend struct hash<Node>;
    friend class Graph;
    friend class NodeHeap;
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
    friend class Graph;
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
    unordered_map<int, Node*> _nodes;
    unordered_set<Edge*> _edges;
public:
    static const int INF = 0x7fffffff;
    explicit Graph(Mat&);
    Node* getNode(int id) { return _nodes[id]; }
    ~Graph();
    static vector<int> dfs(Node*);
    static vector<int> bfs(Node*);
    static vector<Node*> sortedTopology(Graph&);
    static unordered_set<Edge*> kruskalMST(Graph&);
    static unordered_set<Edge*> primMST(Graph&);
    static unordered_map<Node*, double> dijkstra(Graph&, Node*);
};