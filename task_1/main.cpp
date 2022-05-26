#include <iostream>
#include <vector>
#include <queue>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void BFS(const IGraph& graph, int vertex, void (*visit)(int)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> bfsQueue;
    bfsQueue.push(vertex);
    visited[vertex] = true;
    while (bfsQueue.size() > 0) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        visit(current);
        std::vector<int> adjList = graph.GetNextVertices(current);
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[adjList[i]]) {
                bfsQueue.push(adjList[i]);
                visited[adjList[i]] = true;
            }
        }
    }
}

bool testVerticesCount(IGraph* l, IGraph* m, IGraph* s, IGraph* a) {
    int res = l->VerticesCount();
    if (res == m->VerticesCount() && res == s->VerticesCount() && res == a->VerticesCount()) {
        return true;
    }
    return false;
}

bool testGetNextVertices(IGraph* l, IGraph* m, IGraph* s, IGraph* a) {
    for (int i = 0; i < l->VerticesCount(); ++i) {
        int res = l->GetNextVertices(i).size();
        if (res != m->GetNextVertices(i).size() || res != s->GetNextVertices(i).size() || res != a->GetNextVertices(i).size()) {
            return false;
        }
    }
    return true;
}

bool testGetPrevVertices(IGraph* l, IGraph* m, IGraph* s, IGraph* a) {
    for (int i = 0; i < l->VerticesCount(); ++i) {
        int res = l->GetPrevVertices(i).size();
        if (res != m->GetPrevVertices(i).size() || res != s->GetPrevVertices(i).size() || res != a->GetPrevVertices(i).size()) {
            return false;
        }
    }
    return true;
}

int main() {
    IGraph* l = new ListGraph(6);
    l->AddEdge(1,2);
    l->AddEdge(2,1);
    l->AddEdge(2,3);
    l->AddEdge(2,4);
    l->AddEdge(3,4);
    l->AddEdge(4,5);
    l->AddEdge(5,3);
    IGraph* m = new MatrixGraph(*l);
    IGraph* s = new SetGraph(*l);
    IGraph* a = new ArcGraph(*l);

    if (testVerticesCount(l, m, s, a) && testGetNextVertices(l, m, s, a) && testGetPrevVertices(l, m, s, a)) {
        std::cout << "Test ok" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }

    return 0;
}
