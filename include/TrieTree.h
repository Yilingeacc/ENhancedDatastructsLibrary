#pragma once
#include<vector>
#include<string>
#include<unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

template<typename T>
class TrieNode {
    int _pass;
    int _end;
    unordered_map<T&, TrieNode<T>*> _nexts;
public:
    TrieNode() : _pass(0), _end(0) { }
    ~TrieNode() { for (auto [value, pNode] : _nexts) delete pNode; }
};

template<typename T>
class TrieTree {
    TrieNode<T>* _root = new TrieNode<T>();
public:
    ~TrieTree() { delete _root; }
    void insert(const vector<T>&);
    int search(const vector<T>&) const;
    void erase(const vector<T>&);
    int prefixNum(const vector<T>&) const;
private:
    TrieNode<T>*findNode(const vector<T>&) const;
};

template<typename T>
void TrieTree<T>::insert(const vector<T>& v) {
    TrieNode<T>* cur = _root;
    _root->_pass++;
    for (T& value : v) {
        if (cur->_nexts.find(value) == cur->_nexts.end()) cur->_nexts[value] = new TrieNode<T>();
        cur = cur->_nexts[value];
        cur->_pass++;
    }
    cur->_end++;
}

template<typename T>
int TrieTree<T>::search(const vector<T>& v) const {
    if (TrieNode<T>* cur = findNode(v)) return cur->_end;
    return 0;
}

template<typename T>
void TrieTree<T>::erase(const vector<T>& v) {
    if (search(v)) {
        TrieNode<T>* cur = _root;
        _root->_pass--;
        for (T& value : v) {
            cur = cur->_nexts[value];
            if (!--cur->_pass) {
                delete cur;
                return;
            }
        }
        cur->_end--;
    }
}

template<typename T>
int TrieTree<T>::prefixNum(const vector<T>& v) const {
    if (TrieNode<T>* cur = findNode(v)) return cur->_pass;
    return 0;
}

template<typename T>
TrieNode<T> *TrieTree<T>::findNode(const vector<T>& v) const {
    TrieNode<T>* cur = _root;
    for (T& value : v) {
        if (cur->_nexts.find(value) == cur->_nexts.end()) return nullptr;
        cur = cur->_nexts[value];
    }
    return cur;
}

template<>
class TrieNode<char> {
    friend class TrieTree<char>;
    int _pass = 0;
    int _end = 0;
    TrieNode<char>* _nexts[26] = { nullptr };
};

template<>
class TrieTree<char> {
    TrieNode<char>* _root = new TrieNode<char>();
public:
    void insert(const string&);
    [[nodiscard]] int search(const string&) const;
    void erase(const string&);
    [[nodiscard]] int prefixNum(const string&) const;
private:
    [[nodiscard]] TrieNode<char>*findNode(const string&) const;
};

void TrieTree<char>::insert(const string& str) {
    TrieNode<char>* cur = _root;
    _root->_pass++;
    for (auto ch : str) {
        int path = ch - 'a';
        if (!cur->_nexts[path]) cur->_nexts[path] = new TrieNode<char>();
        cur = cur->_nexts[path];
        cur->_pass++;
    }
    cur->_end++;
}

int TrieTree<char>::search(const string& str) const {
    if (TrieNode<char>* cur = findNode(str)) return cur->_end;
    return 0;
}

void TrieTree<char>::erase(const string& str) {
    if (search(str)) {
        TrieNode<char>* cur = _root;
        _root->_pass--;
        for (auto ch : str) {
            int path = ch - 'a';
            if (!--cur->_nexts[path]->_pass) {
                delete cur->_nexts[path];
                cur->_nexts[path] = nullptr;
                return;
            }
            cur = cur->_nexts[path];
        }
        cur->_end--;
    }
}

int TrieTree<char>::prefixNum(const string& str) const {
    if (TrieNode<char>* cur = findNode(str)) return cur->_pass;
    return 0;
}

TrieNode<char> *TrieTree<char>::findNode(const string& str) const {
    TrieNode<char>* cur = _root;
    for (auto ch : str) {
        int path = ch - 'a';
        if (!cur->_nexts[path]) return nullptr;
        cur = cur->_nexts[path];
    }
    return cur;
}

template<>
class TrieNode<int> {
    friend class TrieTree<int>;
    TrieNode<int>* _nexts[2] = { nullptr };
};

template<>
class TrieTree<int> {
    TrieNode<int>* _root = new TrieNode<int>();
public:
    void insert(int);
    int getMaxXorResult(int);
};

void TrieTree<int>::insert(int value) {
    TrieNode<int>* cur = _root;
    for (int i = 31; i >= 0; i--) {
        int path = (value >> i) & 1;
        if (!cur->_nexts[path]) cur->_nexts[path] = new TrieNode<int>();
        cur = cur->_nexts[path];
    }
}

#include<bitset>

int TrieTree<int>::getMaxXorResult(int value) {
    TrieNode<int>* cur = _root;
    int res = 0;
    for (int i = 31; i >= 0; i--) {
        int digit = (value >> i) & 1;
        int best = i == 31 ? digit : digit ^ 1;
        int choice = cur->_nexts[best] ? best : best ^ 1;
        cur = cur->_nexts[choice];
        res |= (digit ^ choice) << i;
    }
    return res;
}
