#include <cassert>

#include "ArcGraph.h"

ArcGraph::ArcGraph(int count) {
    arPair.resize(count);
}

ArcGraph::ArcGraph(const IGraph &graph) {
    for (int i = 0; i < arPair.size(); ++i) {
        std::vector<int> nextVer = graph.GetNextVertices(i);
        for (auto elem: nextVer) {
            arPair.push_back(std::make_pair(i, elem));
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 && to < arPair.size());
    assert(from >= 0 && to < arPair.size());
    arPair.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
    return arPair.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < arPair.size());
    std::vector<int> nextVer;
    for (int i = 0; i < arPair.size(); ++i) {
        if (arPair[i].first == vertex) {
            nextVer.push_back(arPair[i].second);
        }
    }
    return nextVer;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < arPair.size());
    std::vector<int> prevVer;
    for (int i = 0; i < arPair.size(); ++i) {
        if (arPair[i].second == vertex) {
            prevVer.push_back(arPair[i].first);
        }
    }
    return prevVer;
}
