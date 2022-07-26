#pragma once
#include<iostream>
#include<list>
#include<stack>
#include<queue>
#include<tuple>
#include<string>

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
    TreeNode(int value, TreeNode* left, TreeNode* right) : _value(value), _left(left), _right(right) { }
    ~TreeNode() { delete _left; delete _right; }
private:
    string serialByPreOrder();
    string serialByInOrder();
    string serialByPostOrder();
};

class BinaryTree {
    TreeNode* _root;
public:
    BinaryTree() : _root(nullptr) { }
    ~BinaryTree() { delete _root; }
    static vector<int> preOrder(TreeNode*);
    static vector<int> inOrder(TreeNode*);
    static vector<int> postOrder(TreeNode*);
    static vector<int> levelOrder(TreeNode*);
    static vector<int> morrisPreOrder(TreeNode*);
    static vector<int> morrisInOrder(TreeNode*);
    static vector<int> morrisPostOrder(TreeNode*);
    static bool isFullBinaryTree(TreeNode*);
    static bool isCompleteBinaryTree(TreeNode*);
    static bool isBinarySearchTree(TreeNode*);
    static int getCBTNodeNum(TreeNode*);
    static string serialByPreOrder(TreeNode*);
    static string serialByInOrder(TreeNode*);
    static string serialByPostOrder(TreeNode*);
    static TreeNode* reconByPreString(const string&);
    static TreeNode* reconByInString(const string&);
    static TreeNode* reconByPostString(const string&);
private:
    static int getCBTDepth(TreeNode*);
    static tuple<bool, int, int> isBinarySearchTreeRecur(TreeNode*);
    static TreeNode* reverseEdge(TreeNode*);
    static void handleEdge(TreeNode *head, vector<int>&);
    static list<string> getDataArray(const string& str);
    static TreeNode* reconPreOrder(list<string>&);
    static TreeNode* reconInOrder(list<string>&);
    static TreeNode* reconPostOrder(list<string>&);
};
