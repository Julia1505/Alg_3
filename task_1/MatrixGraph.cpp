#include <cassert>

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int count) {
    adjMatrix.resize(count);
    for (auto &row : adjMatrix) {
        row.resize(count, 0);
    }
}

MatrixGraph::MatrixGraph(const IGraph &graph): MatrixGraph(graph.VerticesCount()) {
    for (int i = 0; i < adjMatrix.size(); ++i) {
        std::vector<int> nextVer = graph.GetNextVertices(i);
        for (auto elem : nextVer) {
            adjMatrix[i][elem]++;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjMatrix.size());
    assert(to >= 0 && to < adjMatrix.size());
    adjMatrix[from][to]++;
}

int MatrixGraph::VerticesCount() const {
    return adjMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjMatrix.size());
    std::vector<int> nextVer = {};
    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[vertex][i] != 0) {
            nextVer.push_back(i);
        }
    }
    return nextVer;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjMatrix.size());
    std::vector<int> prevVer;
    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[i][vertex] != 0) {
            prevVer.push_back(i);
        }
    }
    return prevVer;
}
