/*
Задача 3. «Города» (4 балла)
Обязательная задача
Требуется отыскать самый выгодный маршрут между городами.
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
Формат входных данных.
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.
*/

#include <iostream>
#include <vector>
#include <set>
#include <cassert>

struct IGraph {
    virtual ~IGraph() {}

    struct Weight {
        int weight;
        int to;

        Weight(int weight, int to):weight(weight), to(to){};
    };

    virtual void AddEdge(int from, int to, int weigh) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<Weight> GetNextVertices(int vertex) const = 0;
};

class WeighListGraph: public IGraph {
public:
    WeighListGraph(int count);
    WeighListGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to, int weigh)override;
    virtual int VerticesCount() const override;
    std::vector<Weight> GetNextVertices(int vertex) const override;

private:
    std::vector<std::vector<Weight>> adjList;
};

WeighListGraph::WeighListGraph(int count) {
    adjList.resize(count);
}

WeighListGraph::WeighListGraph(const IGraph &graph) {
    adjList.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjList[i] = graph.GetNextVertices(i);
    }
}

void WeighListGraph::AddEdge(int from, int to, int weigh) {
    assert(from >= 0 && from < adjList.size());
    assert(to >= 0 && to < adjList.size());
    adjList[from].push_back(Weight(weigh, to));
    adjList[to].push_back(Weight(weigh, from));
}

int WeighListGraph::VerticesCount() const {
    return adjList.size();
}

std::vector<IGraph::Weight> WeighListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    return adjList[vertex];
}

bool Relax(std::vector<int> &weight, const int from, IGraph::Weight &vertexWeight) {
    if (weight[vertexWeight.to] > weight[from] + vertexWeight.weight) {
        int tempWeigh = weight[vertexWeight.to];
        weight[vertexWeight.to] = weight[from] + vertexWeight.weight;

        vertexWeight.weight = tempWeigh;
        return true;
    }
    return false;
}

int Djkstra( const IGraph &graph, const int from, const int to) {
    std::vector<int> weigh(graph.VerticesCount());
    weigh.assign(weigh.size(), INT32_MAX);
    weigh[from] = 0;

    std::set<std::pair<int, int>> waysSet;
    waysSet.insert(std::pair<int, int>(from, weigh[from]));

    while (!waysSet.empty()) {
        auto iter = waysSet.begin();

        std::vector<IGraph::Weight> nextVertex = graph.GetNextVertices(iter->first);
        for (int i = 0; i < nextVertex.size(); ++i) {
            if (weigh[nextVertex[i].to] == INT32_MAX) {
                weigh[nextVertex[i].to] = weigh[iter->first] + nextVertex[i].weight;
                waysSet.insert(std::pair<int, int> (nextVertex[i].to, weigh[nextVertex[i].to]));
            } else if (Relax(weigh, iter->first, nextVertex[i])) {
                waysSet.erase(std::pair<int, int> (nextVertex[i].to, nextVertex[i].weight));
                waysSet.insert(std::pair<int, int>(nextVertex[i].to, nextVertex[i].weight));
            }
        }
        waysSet.erase(iter);
    }
    return weigh[to];
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    IGraph *graph = new WeighListGraph(n);
    int from = 0;
    int to = 0;
    int weigh = 0;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> weigh;
        graph->AddEdge(from, to, weigh);
    }
    std::cin >> from >> to;
    int res = Djkstra(*graph, from, to);

    std::cout << res;

    return 0;
}
