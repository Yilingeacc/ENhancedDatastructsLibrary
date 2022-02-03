#pragma once
#include<unordered_map>
#include<utility>
#include"Heap.h"

using std::min;
using std::pair;
using std::unordered_map;
using namespace std::rel_ops;

class Node;

inline bool operator<(const pair<Node*, double>&lhs, const pair<Node*, double>&rhs) { return lhs.second < rhs.second; }
inline bool operator==(const pair<Node*, double>&lhs, const pair<Node*, double>&rhs) { return lhs.second == rhs.second; }

class NodeHeap : public Heap<pair<Node*, double>> {
    unordered_map<Node*, int> _heapIndexMap;
    unordered_map<Node*, double> _distanceMap;
public:
    explicit NodeHeap(int size);
    bool isEntered(Node* pNode) { return _heapIndexMap.find(pNode) != _heapIndexMap.end(); }
    bool isInHeap(Node* pNode) { return isEntered(pNode) && _heapIndexMap[pNode] != -1; }
    pair<Node*, double> pop() override;
    void updateIfCloser(Node*, double);
private:
    void swap(int, int) override;
};
