#include "KruskalMST.h"
#include "Partition.h"
#include "PQ.h"

#include <vector>
#include <utility>
#include <functional>

using KruskalEntry = std::pair<double, std::pair<int, int>>;

using KruskalPQ = std::priority_queue<KruskalEntry, std::vector<KruskalEntry>, std::greater<KruskalEntry>>;

MinimumSpanningTree kruskal(const Graph& graph)
{
    int n = graph.vertexCount();
    MinimumSpanningTree mst;

    if(n == 0)
        return mst;

    //Elementary cluster for each vertex in graph
    Partition partition(n);

    //initialize priority queue to contain all edges in G, weights as keys
    KruskalPQ edges;

    for(int u = 0; u < n; u++)
    {
        for(const auto& edge : graph.neighbors(u))
        {
            if(u < edge.to)
                edges.push({edge.weight, {u, edge.to}});
        }
    }

    while(!edges.empty() && mst.edges.size() < static_cast<std::size_t>(n - 1))
    {
        KruskalEntry edge = edges.top();
        edges.pop();

        double weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if(partition.unionSets(u, v))
        {
            mst.edges.push_back({u, v, weight});
            mst.totalWeight += weight;
        }
    }

    return mst;
}