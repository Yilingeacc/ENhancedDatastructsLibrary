#include<iostream>
#include "include\Graph.h"

using namespace std;
using namespace rel_ops;

//class Elem {
//    friend ostream&operator<<(ostream&, Elem&);
//    friend struct hash<Elem>;
//public:
//    int _val;
//    explicit Elem(int val) : _val(val) { cout << "constructor" << endl; }
//    Elem(const Elem& elem) : _val(elem._val) { cout << "copy constructor" << endl; }
//    ~Elem() = default;
//    bool operator<(const Elem&rhs) const { return this->_val < rhs._val; }
//    bool operator==(const Elem&rhs) const { return this->_val == rhs._val; }
//};
//
//namespace std{
//    template<> struct hash<Elem> {
//        size_t operator()(const Elem& elem) const { return elem._val; }
//    };
//}
//
//
//ostream&operator<<(ostream&os, Elem&elem) {
//    os << elem._val << endl;
//    return os;
//}

void dijkstraTest() {
    Mat mat = {
            {0, 5, 2, 6, Graph::INF},
            {Graph::INF, 0, Graph::INF, Graph::INF, 1},
            {Graph::INF, 1, 0, 3, 5},
            {Graph::INF, Graph::INF, Graph::INF, 0, 2},
            {Graph::INF, Graph::INF, Graph::INF, Graph::INF, 0}
    };
    Graph graph(mat);
    Node* pHead = graph.getNode(0);
    unordered_map<Node*, double> res = dijkstra(graph, pHead);
    for (auto [pNode, distance] : res) {
        cout << *pNode << distance << endl;
    }
}

int main() {
    dijkstraTest();
    return 0;
}
