#pragma once
#include<iostream>
#include<list>
#include<stack>
#include<queue>
#include<tuple>

using namespace std;

class BinaryTree;

class TreeNode {
    friend ostream&operator<<(ostream&, const TreeNode&);
    friend class BinaryTree;
    int _value;
    TreeNode* _left;
    TreeNode* _right;
public:
    explicit TreeNode(int value) : _value(value), _left(nullptr), _right(nullptr) { }
    ~TreeNode() { delete _left; delete _right; }
    TreeNode(int value, TreeNode* left, TreeNode* right) : _value(value), _left(left), _right(right) { }
    void preOrder();
    void inOrder();
    void postOrder();
    tuple<bool, int, int> isBinarySearchTree();
    bool isCompleteBinaryTree();
    int getCBTNodeNum();
    string serialByPreOrder();
    string serialByInOrder();
    string serialByPostOrder();
private:
    int getCBTDepth();
};

class BinaryTree {
    TreeNode* _root;
public:
    BinaryTree() : _root(nullptr) { }
    ~BinaryTree() { delete _root; }
    void preOrder();
    void inOrder();
    void postOrder();
    void levelOrder();
    void preOrderRecur();
    void inOrderRecur();
    void postOrderRecur();
    void morrisPreOrder();
    void morrisInOrder();
    void morrisPostOrder();
    bool isBinarySearchTree();
    bool isCompleteBinaryTree();
    bool isFullBinaryTree();
    string serialByPreOrder();
    string serialByInOrder();
    string serialByPostOrder();
    static TreeNode* reconByPreString(const string&);
    static TreeNode* reconByInString(const string&);
    static TreeNode* reconByPostString(const string&);
private:
    static TreeNode* reverseEdge(TreeNode*);
    static void printEdge(TreeNode*);
    static list<string> getDataArray(const string& str);
    static TreeNode* reconPreOrder(list<string>&);
    static TreeNode* reconInOrder(list<string>&);
    static TreeNode* reconPostOrder(list<string>&);
};
