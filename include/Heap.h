#include<vector>
#include<cassert>

using std::vector;
using std::less;
using std::move;
class NodeHeap;

template <typename T, typename Comp=less<T>>
class Heap {
    friend class NodeHeap;
    vector<T> _v;
    int _heapSize;
    Comp _comp = Comp();
public:
    Heap() : _heapSize(0) { }
    explicit Heap(int size) : _heapSize(0) { _v.reserve(size); }
    explicit Heap(vector<T>&);
    void push(T&);
    virtual T pop();
    T peek();
    void update(int, T&);
    [[nodiscard]] int size() const { return this->_heapSize; }
    [[nodiscard]] bool empty() const { return !this->_heapSize; }
private:
    void heapInsert(int);
    void heapify(int);
    virtual void swap(int, int);
};

template<typename T, typename Comp>
Heap<T, Comp>::Heap(vector<T>& v) : _heapSize(v.size()) {
    _v = v;
    for (int i = (_heapSize - 1) >> 1; i >= 0; i--) {
        heapify(i);
    }
}

template<typename T, typename Comp>
void Heap<T, Comp>::push(T& value) {
    _v.push_back(value);
    heapInsert(_heapSize++);
}

template<typename T, typename Comp>
T Heap<T, Comp>::pop() {
    assert(_heapSize > 0);
    swap(0, --_heapSize);
    heapify(0);
    T& ret = _v[_heapSize];
    _v.pop_back();
    return ret;
}

template<typename T, typename Comp>
T Heap<T, Comp>::peek() {
    assert(_heapSize > 0);
    return _v[0];
}

template<typename T, typename Comp>
void Heap<T, Comp>::swap(int a, int b) {
    T temp(move(_v[a]));
    _v[a] = move(_v[b]);
    _v[b] = move(temp);
}

template<typename T, typename Comp>
void Heap<T, Comp>::heapInsert(int index) {
    while (index && _comp(_v[index], _v[(index - 1) >> 1])) {
        swap(index, (index - 1) >> 1);
        index = (index - 1) >> 1;
    }
}

template<typename T, typename Comp>
void Heap<T, Comp>::heapify(int index) {
    int left = (index << 1) | 1;
    while (left < _heapSize) {
        int up = left + 1 < _heapSize && _comp(_v[left + 1], _v[left]) ? left + 1 : left;
        up = _comp(_v[index], _v[up]) ? index : up;
        if (index == up) break;
        swap(index, up);
        index = up;
        left = index << 1 | 1;
    }
}

template<typename T, typename Comp>
void Heap<T, Comp>::update(int index, T& obj) {
    if (_comp(obj, _v[index])) {
        _v[index] = move(obj);
        heapInsert(index);
    } else if (_comp(_v[index], obj)){
        _v[index] = move(obj);
        heapify(index);
    }
}
