#pragma once
#include <unordered_set>

#include "IGraph.h"

class SetGraph: public IGraph {
public:
    SetGraph(int count);
    SetGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to)override;
    virtual int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> adjSet;
};