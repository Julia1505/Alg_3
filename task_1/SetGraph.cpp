#include <cassert>
#include <iterator>

#include "SetGraph.h"

SetGraph::SetGraph(int count) {
    adjSet.resize(count);
}

SetGraph::SetGraph(const IGraph &graph) {
    adjSet.resize(graph.VerticesCount());
    for (int i = 0; i < adjSet.size(); ++i) {
        std::vector<int> nextVer = graph.GetNextVertices(i);
        for (auto elem: nextVer) {
            adjSet[i].insert(elem);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjSet.size());
    assert(to >= 0 && to < adjSet.size());
    adjSet[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return adjSet.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjSet.size());
    std::vector<int> nextVer = {};
    for (auto iter = adjSet[vertex].begin(); iter != adjSet[vertex].end(); ++iter) {
        nextVer.push_back(*iter);
    }
    return nextVer;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjSet.size());
    std::vector<int> prevVer;
    for (int i = 0; i < adjSet.size(); ++i) {
        for (auto iter = adjSet[i].begin(); iter != adjSet[i].end(); ++iter) {
            if (*iter == vertex) {
                prevVer.push_back(i);
            }
        }
    }
    return prevVer;
}
