#pragma once

#include <vector>
#include "Graph.h"

struct MSTEdge
{
    int from;
    int to;
    double weight;
};

struct MinimumSpanningTree
{
    std::vector<MSTEdge> edges;
    double totalWeight = 0;
};

MinimumSpanningTree kruskal(const Graph& graph);