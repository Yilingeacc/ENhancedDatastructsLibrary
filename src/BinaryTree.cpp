#include "../include/BinaryTree.h"

ostream &operator<<(ostream& os, const TreeNode& node) {
    os << node._value << '\t';
    return os;
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

vector<int> BinaryTree::preOrder(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> st;
    vector<int> v;
    st.push(root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        v.push_back(cur->_value);
        if (cur->_right) st.push(cur->_right);
        if (cur->_left) st.push(cur->_left);
    }
    return v;
}

vector<int> BinaryTree::inOrder(TreeNode* root) {
    if (!root) return {};
    TreeNode* cur = root;
    stack<TreeNode*> st;
    vector<int> v;
    while (cur || !st.empty()) {
        if (cur) {
            st.push(cur);
            cur = cur->_left;
        } else {
            cur = st.top(); st.pop();
            v.push_back(cur->_value);
            cur = cur->_right;
        }
    }
    return v;
}

vector<int> BinaryTree::postOrder(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> st;
    stack<TreeNode*> collect;
    vector<int> v;
    st.push(root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        collect.push(cur);
        if (cur->_left) st.push(cur->_left);
        if (cur->_right) st.push(cur->_right);
    }
    while (!collect.empty()) {
        v.push_back(collect.top()->_value);
        collect.pop();
    }
}

vector<int> BinaryTree::levelOrder(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> que;
    vector<int> v;
    que.push(root);
    while (!que.empty()) {
        TreeNode* cur = que.front(); que.pop();
        v.push_back(cur->_value);
        if (cur->_left) que.push(cur->_left);
        if (cur->_right) que.push(cur->_right);
    }
    return v;
}

vector<int> BinaryTree::morrisPreOrder(TreeNode* root) {
    TreeNode* cur = root;
    TreeNode* mostRight;
    vector<int> v;
    while (cur) {
        mostRight = cur->_left;
        if (mostRight) {
            while (mostRight->_right && mostRight->_right != cur) {
                mostRight = mostRight->_right;
            }
            if (!mostRight->_right) {
                v.push_back(cur->_value);
                mostRight->_right = cur;
                cur = cur->_left;
                continue;
            } else {
                mostRight->_right = nullptr;
            }
        } else {
            v.push_back(cur->_value);
        }
        cur = cur->_right;
    }
    return v;
}

vector<int> BinaryTree::morrisInOrder(TreeNode* root) {
    TreeNode* cur = root;
    TreeNode* mostRight;
    vector<int> v;
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
        v.push_back(cur->_value);
        cur = cur->_right;
    }
    return v;
}

vector<int> BinaryTree::morrisPostOrder(TreeNode* root) {
    TreeNode* cur = root;
    TreeNode* mostRight;
    vector<int> v;
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
                handleEdge(cur->_left, v);
            }
        }
        cur = cur->_right;
    }
    handleEdge(root,v);
    return v;
}

tuple<bool, int, int> BinaryTree::isBinarySearchTreeRecur(TreeNode* root) {
    tuple<bool, int, int> leftInfo = root->_left ? isBinarySearchTreeRecur(root->_left) : make_tuple(true, 0, 0);
    tuple<bool, int, int> rightInfo = root->_right ? isBinarySearchTreeRecur(root->_right) : make_tuple(true, 0, 0);
    if (!get<0>(leftInfo) || !get<0>(rightInfo)) return make_tuple(false, 0, 0);
    if (root->_value <= get<2>(leftInfo) || root->_value >= get<1>(rightInfo)) return make_tuple(false, 0, 0);
    return make_tuple(true, get<1>(leftInfo), get<2>(rightInfo));
}

bool BinaryTree::isBinarySearchTree(TreeNode* root) {
    return get<0>(isBinarySearchTreeRecur(root));
}

bool BinaryTree::isCompleteBinaryTree(TreeNode* root) {
    bool leaf = false;
    queue<TreeNode*> que;
    que.push(root);
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

bool BinaryTree::isFullBinaryTree(TreeNode* root) {
    if (!isCompleteBinaryTree(root)) return false;
    int depth = getCBTDepth(root);
    int nodeNum = getCBTNodeNum(root);
    return (1 << depth) - 1 == nodeNum;
}

int BinaryTree::getCBTNodeNum(TreeNode* root) {
    if (!isCompleteBinaryTree(root)) return -1;
    int depth = getCBTDepth(root);
    if (root->_right && getCBTDepth(root->_right) + 1 == depth) {
        return (1 << (depth - 1)) + getCBTNodeNum(root->_right);
    } else if (root->_left){
        return (1 << (depth - 2)) + getCBTNodeNum(root->_left);
    } else {
        return 1;
    }
}

int BinaryTree::getCBTDepth(TreeNode* root) {
    int depth = 0;
    TreeNode* cur = root;
    while (cur) {
        cur = cur->_left;
        depth++;
    }
    return depth;
}

string BinaryTree::serialByPreOrder(TreeNode* root) {
    return root ? root->serialByPreOrder() : "#_";
}

string BinaryTree::serialByInOrder(TreeNode* root) {
    return root ? root->serialByInOrder() : "#_";
}

string BinaryTree::serialByPostOrder(TreeNode* root) {
    return root ? root->serialByPostOrder() : "#_";
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

void BinaryTree::handleEdge(TreeNode* head, vector<int>& v) {
    TreeNode* tail = reverseEdge(head);
    TreeNode* cur = tail;
    while (cur) {
        v.push_back(cur->_value);
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
