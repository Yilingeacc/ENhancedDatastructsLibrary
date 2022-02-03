#include "..\include\Graph.h"

ostream &operator<<(ostream &os, Node& node) {
    os << "Node " << node._id << ' ';
    return os;
}

ostream &operator<<(ostream &os, Edge& edge) {
    os << "weight: " << edge._w << " from: " << *edge._src << " to: " << *edge._dst << endl;
    return os;
}

Graph::Graph(Mat& mat) {
    const size_t SIZE = mat.size();
    for (int i = 0; i < SIZE; i++) {
        _nodes[i] = new Node(i);
    }
    for (int i = 0; i < SIZE; i++) {
        Node* cur = _nodes[i];
        for (int j = 0; j < SIZE; j++) {
            if (i == j || mat[i][j] == INF) continue;
            cur->_out++;
            _nodes[j]->_in++;
            cur->_nexts.push_back(_nodes[j]);
            Edge* newEdge = new Edge(mat[i][j], cur, _nodes[j]);
            cur->_edges.push_back(newEdge);
            _edges.insert(newEdge);
        }
    }
}

Graph::~Graph() {
    for (auto & _node : _nodes) delete _node.second;
    for (auto _edge : _edges) delete _edge;
}

void Graph::dfs(Node* pNode) {
    if (!pNode) return;
    stack<Node*> path;
    unordered_set<Node*> visited;
    path.push(pNode);
    visited.insert(pNode);
    cout << *pNode;
    while (!path.empty()) {
        Node* cur = path.top(); path.pop();
        for (Node* next : cur->_nexts) {
            if (visited.find(next) != visited.end()) {
                path.push(cur);
                path.push(next);
                visited.insert(next);
                cout << *next;
                break;
            }
        }
    }
}

void Graph::bfs(Node* pNode) {
    if (!pNode) return;
    queue<Node*> queue;
    unordered_set<Node*> visited;
    queue.push(pNode);
    visited.insert(pNode);
    while (!queue.empty()) {
        Node* cur = queue.front(); queue.pop();
        cout << *cur;
        for (Node* next : cur->_nexts) {
            if (visited.find(next) == visited.end()) {
                queue.push(next);
                visited.insert(next);
            }
        }
    }
}

vector<Node*> sortedTopology(Graph& graph) {
    unordered_map<Node*, int> inMap;
    queue<Node*> zeroInQueue;
    for (auto& _node : graph._nodes) {
        Node* cur = _node.second;
        inMap[cur] = cur->_in;
        if (!cur->_in) zeroInQueue.push(cur);
    }
    vector<Node*> res;
    while (!zeroInQueue.empty()) {
        Node* cur = zeroInQueue.front(); zeroInQueue.pop();
        res.push_back(cur);
        for (Node* next : cur->_nexts) {
            inMap[next]--;
            if (!inMap[next]) zeroInQueue.push(next);
        }
    }
    return res;
}

unordered_set<Edge*> kruskalMST(Graph& graph) {
    UnionFindSet<Node> unionFindSet;
    unionFindSet.makeSet(graph._nodes);
    priority_queue<Edge*, vector<Edge*>, CmpEdgePtrs> priorityQueue;
    for (Edge* pEdge : graph._edges) {
        priorityQueue.push(pEdge);
    }
    unordered_set<Edge*> res;
    while (!priorityQueue.empty()) {
        Edge* pEdge = priorityQueue.top(); priorityQueue.pop();
        if (!unionFindSet.isSameSet(*pEdge->_src, *pEdge->_dst)) {
            res.insert(pEdge);
            unionFindSet.unionSet(*pEdge->_src, *pEdge->_dst);
        }
    }
    return res;
}

unordered_set<Edge*> primMST(Graph& graph) {
    priority_queue<Edge*, vector<Edge*>, CmpEdgePtrs> priorityQueue;
    unordered_set<Node*> visited;
    unordered_set<Edge*> res;
    for (auto& _node : graph._nodes) {
        Node* cur = _node.second;
        if (visited.find(cur) == visited.end()) {
            visited.insert(cur);
            for (Edge* pEdge : cur->_edges) {
                priorityQueue.push(pEdge);
            }
            while (!priorityQueue.empty()) {
                Edge* pEdge = priorityQueue.top(); priorityQueue.pop();
                if (visited.find(pEdge->_dst) == visited.end()) {
                    visited.insert(pEdge->_dst);
                    res.insert(pEdge);
                    for (Edge* nextEdge : pEdge->_dst->_edges) priorityQueue.push(nextEdge);
                }
            }
        }
    }
    return res;
}

unordered_map<Node*, double> dijkstra(Graph& graph, Node* pHead) {
    NodeHeap nodeHeap(graph._nodes.size());
    nodeHeap.updateIfCloser(pHead, 0);
    unordered_map<Node*, double> res;
    while (!nodeHeap.empty()) {
        Node* pNode;
        double distance;
        tie(pNode, distance) = nodeHeap.pop();
        for (Edge* pEdge : pNode->_edges) {
            nodeHeap.updateIfCloser(pEdge->_dst, pEdge->_w + distance);
        }
        res[pNode] = distance;
    }
    return res;
}