#pragma once
#include<vector>
#include<stack>
#include<unordered_map>

using std::vector;
using std::stack;
using std::unordered_map;

template <typename T>
class Element {
    T* _pValue;
public:
    explicit Element(T* pValue) : _pValue(pValue) { }
};

template <typename T>
class UnionFindSet {
    unordered_map<T*, Element<T>*> _elementMap;
    unordered_map<Element<T>*, Element<T>*> _fatherMap;
    unordered_map<Element<T>*, int> _sizeMap;
public:
    UnionFindSet() = default;
    explicit UnionFindSet(vector<T>&);
    ~UnionFindSet();
    bool isSameSet(T&, T&);
    void unionSet(T&, T&);
    void makeSet(unordered_map<int, T*>&);
private:
    Element<T>* findHead(Element<T>*);
};

template<typename T>
inline UnionFindSet<T>::UnionFindSet(vector<T>& v) {
    _elementMap.reserve(v.size());
    _fatherMap.reserve(v.size());
    _sizeMap.reserve(v.size());
    for (T& value : v) {
        auto* element = new Element<T>(&value);
        _elementMap[&value] = element;
        _fatherMap[element] = element;
        _sizeMap[element] = 1;
    }
}

template<typename T>
inline UnionFindSet<T>::~UnionFindSet() {
    for (auto [node, element] : _elementMap) {
        delete element;
    }
}

template<typename T>
inline bool UnionFindSet<T>::isSameSet(T& a, T& b) {
    if (_elementMap.find(&a) != _elementMap.end() && _elementMap.find(&b) != _elementMap.end()) {
        return findHead(_elementMap[&a]) == findHead(_elementMap[&b]);
    }
    return false;
}

template<typename T>
inline void UnionFindSet<T>::unionSet(T& a, T& b) {
    if (_elementMap.find(&a) != _elementMap.end() && _elementMap.find(&b) != _elementMap.end()) {
        Element<T>* aHead = findHead(_elementMap[&a]);
        Element<T>* bHead = findHead(_elementMap[&b]);
        if (aHead != bHead) {
            Element<T>* larger = _sizeMap[aHead] >= _sizeMap[bHead] ? aHead : bHead;
            Element<T>* smaller = larger == aHead ? bHead : aHead;
            _fatherMap[smaller] = larger;
            _sizeMap[larger] = _sizeMap[larger] + _sizeMap[smaller];
            _sizeMap.erase(smaller);
        }
    }
}

template<typename T>
inline Element<T>* UnionFindSet<T>::findHead(Element<T>* element) {
    stack<Element<T>*> path;
    while (element != _fatherMap[element]) {
        path.push(element);
        element = _fatherMap[element];
    }
    while (!path.empty()) {
        _fatherMap[path.top()] = element;
        path.pop();
    }
    return element;
}

template<typename T>
void UnionFindSet<T>::makeSet(unordered_map<int, T*>& map) {
    for (auto [id, pNode] : map) {
        auto* element = new Element<T>(pNode);
        _elementMap[pNode] = element;
        _fatherMap[element] = element;
        _sizeMap[element] = 1;
    }
}
