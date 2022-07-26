#pragma once

#include<random>
using std::max;
using std::default_random_engine;

class SkipList::SkipListNode {
    T _value;
    SkipListNode*[] _next;
public:
    SkipListNode(int value, int level) : _value(value) {
        this._next = SkipListNode*[level]{};
    }
};


template <typename T, typename Comp=less<T>>
class SkipList {
    class SkipListNode;
    static const int MAX_LEVEL = 32;
    int _topLevel = 0;
    SkipListNode _head = SkipListNode(nullptr, MAX_LEVEL);
    Comp _comp = Comp();
    std::default_random_engine _e;
    std::uniform_real_distribution<double> _u = std::uniform_real_distribution(0, 1);
public:
    SkipList() {
        _e.seed(time(0));
    }
    bool search(T&);
    void add(T&);
    void erase(T&);
private:
    int generateRandomLevel();
};

template<typename T, typename Comp>
bool SkipList<T, Comp>::search(T& target) {
    int curLevel = _topLevel;
    SkipListNode curNode = _head;
    while (curLevel >= 0) {
        while (curNode._next[curLevel] != nullptr && !_comp(target, curNode._next[curLevel]._value)) {
            curNode = curNode.next[curLevel];
            if (cur._value == target) return true;
        }
        curLevel--;
    }
    return false;
}

template<typename T, typename Comp>
void SkipList<T, Comp>::add(T& target) {
    int level = generateRandomLevel();
    SkipListNode newNode = SkipListNode(target, level);
    _topLevel = std::max(_topLevel, level);
    int curLevel = _topLevel;
    SkipListNode curNode = head;
    while (curLevel >= 0) {
        while (curNode._next[curLevel] != nullptr && _comp(cur._next[curLevel]._value, target)) {
            curNode = curNode._next[curLevel];
        }
        if (curLevel < level) {
            newNode._next[curLevel] = curNode._next[curLevel];
            curNode._next[curLevel] = newNode;
        }
        curLevel--;
    }
}

template<typename T, typename Comp>
void SkipList<T, Comp>::erase(T& target) {
    if (!search(target)) return false;
    int curLevel = _topLevel;
    SkipListNode curNode = _head;
    while (curLevel >= 0) {
        while (curNode._next[curLevel] != nullptr && _comp(curNode._next[curLevel], target)) {
            curNode = curNode.next[curLevel];
        }
        if (curNode._next[curLevel] != nullptr, curNode._next[curLevel]._value == target) {
            curNode._next[curLevel] = curNode._next[curLevel]._next[curLevel];
        }
        curLevel--;
    }
    return true;
}

template<typename T, typename Comp>
int SkipList<T, Comp>::generateRandomLevel() {
    int level = 1;
    while (level < MAX_LEVEL && _u(_e) < 0.5) {
        level++;
    }
    return level;
}
