cmake_minimum_required(VERSION 3.20)
project(ClionProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(ClionProject main.cpp include/UnionFindSet.h src/Graph.cpp include/Graph.h include/Heap.h include/NodeHeap.h src/NodeHeap.cpp include/TrieTree.h include/BinaryTree.h src/BinaryTree.cpp include/SkipList.h src/SegmentTree.cpp include/SegmentTree.h)
