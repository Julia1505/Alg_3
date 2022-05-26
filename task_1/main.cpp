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

int main() {
    IGraph* g = new ArcGraph(6);
    g->AddEdge(1,2);
    g->AddEdge(2,1);
    g->AddEdge(2,3);
    g->AddEdge(2,4);
    g->AddEdge(3,4);
    g->AddEdge(4,5);
    g->AddEdge(5,3);
    g->AddEdge(5,3);
    BFS(*g, 5, [](int v){std::cout << v << ", ";});

    return 0;
}
