/*
Задача 2. Количество различных путей (3 балла)
Обязательная задача
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами.
Требования: сложность O(V+E).
Формат ввода.
v: кол-во вершин (макс. 50000),
n: кол-во ребер (макс. 200000),
n пар реберных вершин,
        пара вершин u, w для запроса.
Формат вывода.
Количество кратчайших путей от u к w.
*/


#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <unordered_set>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

class ListGraph: public IGraph {
public:
    ListGraph(int count);
    ListGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to)override;
    virtual int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjList;
};

ListGraph::ListGraph(int count) {
    adjList.resize(count);
}

ListGraph::ListGraph(const IGraph &graph) {
    adjList.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjList[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjList.size());
    assert(to >= 0 && to < adjList.size());
    adjList[from].push_back(to);
    adjList[to].push_back(from);
}

int ListGraph::VerticesCount() const {
    return adjList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    return adjList[vertex];
}

int BFS(const IGraph& graph, int from, int to) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::vector<int> numWays(graph.VerticesCount(), 0);
    std::queue<int> bfsQueue;
    std::unordered_set<int> layerSet;
    bfsQueue.push(from);
    visited[from] = true;
    numWays[from] = 1;

    while (bfsQueue.size() > 0) {
        while (bfsQueue.size() > 0) {
            int current = bfsQueue.front();
            bfsQueue.pop();
            std::vector<int> adjList = graph.GetNextVertices(current);

            for (int i = 0; i < adjList.size(); ++i) {
                if (!visited[adjList[i]]) {
                    layerSet.insert(adjList[i]);
                    numWays[adjList[i]] += numWays[current];
                }
            }
        }

        for (auto iter = layerSet.begin(); iter != layerSet.end(); ++iter) {
            int current = *iter;
            visited[current] = true;
            bfsQueue.push(current);
        }
        layerSet.clear();
    }
    return numWays[to];
}

int main() {
    int v = 0;
    std::cin >> v;
    IGraph *graph = new ListGraph(v);
    int n = 0;
    std::cin >> n;
    int u = 0;
    int w = 0;

    for (int i = 0; i < n; i++) {
        std::cin >> u >> w;
        graph->AddEdge(u, w);
    }
    int from;
    int to;
    std::cin >> from >> to;

    std::cout << BFS(*graph, from, to);
    return 0;
}
