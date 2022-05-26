#pragma once
#include "IGraph.h"

class MatrixGraph: public IGraph {
public:
    MatrixGraph(int count);
    MatrixGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to)override;
    virtual int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjMatrix;
};