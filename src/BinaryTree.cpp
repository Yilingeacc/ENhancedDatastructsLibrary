#include "../include/BinaryTree.h"

ostream &operator<<(ostream& os, const TreeNode& node) {
    os << node._value << '\t';
    return os;
}

void TreeNode::preOrder() {
    cout << *this;
    if (this->_left) this->_left->preOrder();
    if (this->_right) this->_right->preOrder();
}

void TreeNode::inOrder() {
    if (this->_left) this->_left->inOrder();
    cout << *this;
    if (this->_right) this->_right->inOrder();
}

void TreeNode::postOrder() {
    if (this->_left) this->_left->postOrder();
    if (this->_right) this->_right->postOrder();
    cout << *this;
}

tuple<bool, int, int> TreeNode::isBinarySearchTree() {
    tuple<bool, int, int> leftInfo = this->_left ? this->_left->isBinarySearchTree() : make_tuple(true, 0, 0);
    tuple<bool, int, int> rightInfo = this->_right ? this->_right->isBinarySearchTree() : make_tuple(true, 0, 0);
    if (!get<0>(leftInfo) || !get<0>(rightInfo)) return make_tuple(false, 0, 0);
    if (this->_value <= get<2>(leftInfo) || this->_value >= get<1>(rightInfo)) return make_tuple(false, 0, 0);
    return make_tuple(true, get<1>(leftInfo), get<2>(rightInfo));
}

bool TreeNode::isCompleteBinaryTree() {
    bool leaf = false;
    queue<TreeNode*> que;
    que.push(this);
    while (!que.empty()) {
        TreeNode* cur = que.front(); que.pop();
        if (!cur->_left && cur->_right) return false;
        if (leaf && (cur->_left || cur->_right)) return false;
        if (!cur->_left || !cur->_right) leaf = true;
        if (cur->_left) que.push(cur->_left);
        if (cur->_right) que.push(cur->_right);
    }
    return true;
}

int TreeNode::getCBTNodeNum() {
    int depth = this->getCBTDepth();
    if (_right && _right->getCBTDepth() + 1 == depth) {
        return (1 << (depth - 1)) + _right->getCBTNodeNum();
    } else if (_left){
        return (1 << (depth - 2)) + _left->getCBTNodeNum();
    } else {
        return 1;
    }
}

int TreeNode::getCBTDepth() {
    int depth = 0;
    TreeNode* cur = this;
    while (cur) {
        cur = cur->_left;
        depth++;
    }
    return depth;
}

string TreeNode::serialByPreOrder() {
    string str = to_string(_value) + '_';
    str += _left ? _left->serialByPreOrder() : "#_";
    str += _right ? _right->serialByPreOrder() : "#_";
    return str;
}

string TreeNode::serialByInOrder() {
    string str = _left ? _left->serialByPreOrder() : "#_";
    str += to_string(_value) + '_';
    str += _right ? _right->serialByPreOrder() : "#_";
    return str;
}

string TreeNode::serialByPostOrder() {
    string str = _left ? _left->serialByPreOrder() : "#_";
    str += _right ? _right->serialByPreOrder() : "#_";
    str += to_string(_value) + '_';
    return str;
}

void BinaryTree::preOrder() {
    if (!_root) return;
    stack<TreeNode*> st;
    st.push(_root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        cout << *cur;
        if (cur->_right) st.push(cur->_right);
        if (cur->_left) st.push(cur->_left);
    }
}

void BinaryTree::inOrder() {
    if (!_root) return;
    TreeNode* cur = _root;
    stack<TreeNode*> st;
    while (cur || !st.empty()) {
        if (cur) {
            st.push(cur);
            cur = cur->_left;
        } else {
            cur = st.top(); st.pop();
            cout << *cur;
            cur = cur->_right;
        }
    }
}

void BinaryTree::postOrder() {
    if (!_root) return;
    stack<TreeNode*> st;
    stack<TreeNode*> collect;
    st.push(_root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        collect.push(cur);
        if (cur->_left) st.push(cur->_left);
        if (cur->_right) st.push(cur->_right);
    }
    while (!collect.empty()) {
        cout << *collect.top(); collect.pop();
    }
}

void BinaryTree::levelOrder() {
    if (!_root) return;
    queue<TreeNode*> que;
    que.push(_root);
    while (!que.empty()) {
        TreeNode* cur = que.front(); que.pop();
        cout << *cur;
        if (cur->_left) que.push(cur->_left);
        if (cur->_right) que.push(cur->_right);
    }
}

void BinaryTree::preOrderRecur() {
    _root->preOrder();
}

void BinaryTree::inOrderRecur() {
    _root->inOrder();
}

void BinaryTree::postOrderRecur() {
    _root->postOrder();
}

void BinaryTree::morrisPreOrder() {
    TreeNode* cur = _root;
    TreeNode* mostRight;
    while (cur) {
        mostRight = cur->_left;
        if (mostRight) {
            while (mostRight->_right && mostRight->_right != cur) {
                mostRight = mostRight->_right;
            }
            if (!mostRight->_right) {
                cout << *cur;
                mostRight->_right = cur;
                cur = cur->_left;
                continue;
            } else {
                mostRight->_right = nullptr;
            }
        } else {
            cout << *cur;
        }
        cur = cur->_right;
    }
}

void BinaryTree::morrisInOrder() {
    TreeNode* cur = _root;
    TreeNode* mostRight;
    while (cur) {
        mostRight = cur->_left;
        if (mostRight) {
            while (mostRight->_right && mostRight->_right != cur) {
                mostRight = mostRight->_right;
            }
            if (!mostRight->_right) {
                mostRight->_right = cur;
                cur = cur->_left;
                continue;
            } else {
                mostRight->_right = nullptr;
            }
        }
        cout << *cur;
        cur = cur->_right;
    }
}

void BinaryTree::morrisPostOrder() {
    TreeNode* cur = _root;
    TreeNode* mostRight;
    while (cur) {
        mostRight = cur->_left;
        if (mostRight) {
            while (mostRight->_right && mostRight->_right != cur) {
                mostRight = mostRight->_right;
            }
            if (!mostRight->_right) {
                mostRight->_right = cur;
                cur = cur->_left;
                continue;
            } else {
                mostRight->_right = nullptr;
                printEdge(cur->_left);
            }
        }
        cur = cur->_right;
    }
    printEdge(_root);
}

bool BinaryTree::isBinarySearchTree() {
    return get<0>(this->_root->isBinarySearchTree());
}

bool BinaryTree::isCompleteBinaryTree() {
    return _root == nullptr || _root->isCompleteBinaryTree();
}

bool BinaryTree::isFullBinaryTree() {
    if (!isCompleteBinaryTree()) return false;
    int depth = _root->getCBTDepth();
    int nodeNum = _root->getCBTNodeNum();
    return 1 << (depth - 1) == nodeNum;
}

string BinaryTree::serialByPreOrder() {
    return _root ? _root->serialByPreOrder() : "#_";
}

string BinaryTree::serialByInOrder() {
    return _root ? _root->serialByInOrder() : "#_";
}

string BinaryTree::serialByPostOrder() {
    return _root ? _root->serialByPostOrder() : "#_";
}

TreeNode *BinaryTree::reconByPreString(const string& str) {
    list<string> dataArray = getDataArray(str);
    return reconPreOrder(dataArray);
}

TreeNode *BinaryTree::reconByInString(const string& str) {
    list<string> dataArray = getDataArray(str);
    return reconInOrder(dataArray);
}

TreeNode *BinaryTree::reconByPostString(const string& str) {
    list<string> dataArray = getDataArray(str);
    return reconPostOrder(dataArray);
}

TreeNode *BinaryTree::reconPreOrder(list<string>& ls) {
    if (ls.front() == "#") return nullptr;
    auto* root = new TreeNode(stoi(ls.front()));
    ls.erase(ls.begin());
    root->_left = reconPreOrder(ls);
    root->_right = reconPreOrder(ls);
    return root;
}

TreeNode *BinaryTree::reconInOrder(list<string>& ls) {
    if (ls.front() == "#") return nullptr;
    auto* left = reconPreOrder(ls);
    auto* root = new TreeNode(stoi(ls.front()));
    ls.erase(ls.begin());
    root->_left = left;
    root->_right = reconPreOrder(ls);
    return root;
}

TreeNode *BinaryTree::reconPostOrder(list<string>& ls) {
    if (ls.front() == "#") return nullptr;
    auto* left = reconPreOrder(ls);
    auto* right = reconPreOrder(ls);
    auto* root = new TreeNode(stoi(ls.front()), left, right);
    ls.erase(ls.begin());
    return root;
}

TreeNode* BinaryTree::reverseEdge(TreeNode* head) {
    TreeNode* pre = nullptr;
    while (head) {
        TreeNode* next = head->_right;
        head->_right = pre;
        pre = head;
        head = next;
    }
    return pre;
}

void BinaryTree::printEdge(TreeNode* head) {
    TreeNode* tail = reverseEdge(head);
    TreeNode* cur = tail;
    while (cur) {
        cout << *cur;
        cur = cur->_right;
    }
    reverseEdge(tail);
}

list<string> BinaryTree::getDataArray(const string& str) {
    list<string> res;
    string s;
    for (auto& ch : str) {
        if (ch == '_') {
            res.push_back(s);
            s.clear();
        } else {
            s.push_back(ch);
        }
    }
    return res;
}
