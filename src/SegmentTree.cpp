#include "../include/SegmentTree.h"

SegmentTree::SegmentTree(vector<int>& v) {
    _len = v.size();
    _arr.resize(_len + 1);
    copy(v.begin(), v.end(), _arr.begin() + 1);
    _sum.resize(_len << 2);
    _change.resize(_len << 2);
    _lazy.resize(_len << 2);
    _update.resize(_len << 2);
    build(1, _len, 1);
}

void SegmentTree::add(int L, int R, int C) {
    add(L, R, C, 1, _len, 1);
}

void SegmentTree::update(int L, int R, int C) {
    update(L, R, C, 1, _len, 1);
}

int SegmentTree::getSum(int L, int R) {
    return query(L, R, 1, _len, 1);
}

void SegmentTree::build(int l, int r, int rt) {
    if (l == r) {
        _sum[rt] = _arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    pushUp(rt);
}

void SegmentTree::add(int L, int R, int C, int l, int r, int rt) {
    if (L <= l && R >= r) {
        _lazy[rt] += C;
        _sum[rt] += C * (r - l + 1);
    }
    int mid = (l + r) >> 1;
    pushDown(rt, mid - l + 1, r - mid);
    if (L <= mid) {
        add(L, R, C, l, mid, rt << 1);
    }
    if (R > mid) {
        add(L, R, C, mid + 1, r, rt << 1 | 1);
    }
    pushUp(rt);
}

void SegmentTree::update(int L, int R, int C, int l, int r, int rt) {
    if (L <= l && R >= r) {
        _update[rt] = true;
        _change[rt] = C;
        _sum[rt] = C * (r - l + 1);
        return;
    }
    int mid = (l + r) >> 1;
    pushDown(rt, mid - l + 1, r - mid);
    if (L <= mid) {
        update(L, R, C, l, mid, rt << 1);
    }
    if (R > mid) {
        update(L, R, C, mid + 1, r, rt << 1 | 1);
    }
    pushUp(rt);
}

int SegmentTree::query(int L, int R, int l, int r, int rt) {
    if (L <= l && R >= r) {
        return _sum[rt];
    }
    int mid = (l + r) >> 1;
    pushDown(rt, mid - l + 1, r - mid);
    int ans = 0;
    if (L <= mid) {
        ans += query(L, R, l, mid, rt << 1);
    }
    if (R > mid) {
        ans += query(L, R, mid + 1, r, rt << 1 | 1);
    }
    return ans;
}

// _sum 自下而上更新
void SegmentTree::pushUp(int rt) {
    _sum[rt] = _sum[rt << 1] + _sum[rt << 1 | 1];
}

// 自上而下分发任务, 先发update再发add
void SegmentTree::pushDown(int rt, int ln, int rn) {
    if (_update[rt]) {
        _update[rt << 1] = true;
        _update[rt << 1 | 1] = true;
        _change[rt << 1] = _change[rt];
        _change[rt << 1 | 1] = _change[rt];
        _lazy[rt << 1] = 0;
        _lazy[rt << 1 | 1] = 0;
        _sum[rt << 1] = _change[rt] * ln;
        _sum[rt << 1 | 1] = _change[rt] * rn;
        _update[rt] = false;
    }
    if (_lazy[rt] != 0) {
        _lazy[rt << 1] += _lazy[rt];
        _lazy[rt << 1 | 1] += _lazy[rt];
        _sum[rt << 1] += _lazy[rt] * ln;
        _sum[rt << 1 | 1] += _lazy[rt] * rn;
    }
}
