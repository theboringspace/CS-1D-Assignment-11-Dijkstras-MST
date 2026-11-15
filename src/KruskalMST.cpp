#include "KruskalMST.h"
#include "Partition.h"
#include "PQ.h"

#include <vector>
#include <utility>
#include <functional>

// Stores edge weight and end vertices' indices
using KruskalEntry = std::pair<double, std::pair<int, int>>;

// Min heap based priority queue which processes edges in nondecreasing order by weight
using KruskalPQ = std::priority_queue<KruskalEntry, std::vector<KruskalEntry>, std::greater<KruskalEntry>>;

// Minimum Spanning tree using Kruskal's algorithm
MinimumSpanningTree kruskalMST(const Graph& graph)
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
            // Inserts an undirected edge only once
            if(u < edge.to)
                edges.push({edge.weight, {u, edge.to}});
        }
    }

    // Processes edges until MST is complete or priority queue is empty
    while(!edges.empty() && mst.edges.size() < static_cast<std::size_t>(n - 1))
    {
        // Remove edge with smallest weight
        KruskalEntry edge = edges.top();
        edges.pop();

        // Obtain edge weight and endpoint indices
        double weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        // Add edge to MST if the two clusters are different
        if(partition.unionSets(u, v))
        {
            mst.edges.push_back({u, v, weight});
            mst.totalWeight += weight;
        }
    }

    return mst;
}
