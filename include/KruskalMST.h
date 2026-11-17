/// @file   KruskalMST.h
/// @brief  Kruskal's algorithm for the graph's minimum spanning tree.

#pragma once

#include <vector>
#include "Graph.h"

/// Undirected edge in a Minimum Spanning Tree
struct MSTEdge
{
    int from;
    int to;
    double weight;
};

/// MST's edges and total weight
struct MinimumSpanningTree
{
    std::vector<MSTEdge> edges;
    double totalWeight = 0;
};

/// Kruskal Algorithm for MST no starting vertex required
MinimumSpanningTree kruskalMST(const Graph& graph);
