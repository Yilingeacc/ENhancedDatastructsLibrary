#pragma once
#include<vector>
using namespace std;

class SegmentTree {
    int _len;
    vector<int> _arr; // arr[1...n] == origin[0...n - 1]
    vector<int> _sum;  // 以该节点为头的子树的叶节点之和
    vector<int> _lazy;  // 以该节点为头的子树add的累计值
    vector<bool> _update;  // 以该节点为头的子树是否update过
    vector<int> _change; // 以该节点为头的子树update的值
public:
    explicit SegmentTree(vector<int>&);
    void add(int, int, int);
    void update(int, int, int);
    int getSum(int, int);
private:
    void build(int, int, int);
    void add(int, int, int, int, int, int);
    void update(int, int, int, int, int, int);
    int query(int, int, int, int, int);
    void pushUp(int);
    void pushDown(int, int, int);
};
