#include"../include/NodeHeap.h"

NodeHeap::NodeHeap(int size) : Heap<pair<Node*, double>>(size) {
    _heapIndexMap.reserve(size);
    _distanceMap.reserve(size);
}

void NodeHeap::swap(int index1, int index2) {
    _heapIndexMap[_v[index1].first] = index2;
    _heapIndexMap[_v[index2].first] = index1;
    auto temp = move(_v[index1]);
    _v[index1] = move(_v[index2]);
    _v[index2] = move(temp);
}

pair<Node*, double> NodeHeap::pop() {
    pair<Node*, double> ret = Heap::pop();
    _heapIndexMap[ret.first] = -1;
    _distanceMap.erase(ret.first);
    return ret;
}

void NodeHeap::updateIfCloser(Node* pNode, double distance) {
    if (isInHeap(pNode)) {
        _distanceMap[pNode] = min(_distanceMap[pNode], distance);
        _v[_heapIndexMap[pNode]].second = _distanceMap[pNode];
        heapInsert(_heapIndexMap[pNode]);
    }
    if (!isEntered(pNode)) {
        pair<Node*, double> newNode(pNode, distance);
        _heapIndexMap[pNode] = _heapSize;
        _distanceMap[pNode] = distance;
        push(newNode);
    }
}

