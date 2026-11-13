#pragma once

#include <vector>
#include "Graph.h"

struct ShortestPaths
{
    int source;
    std::vector<double> distances; ///< Infinity if unreachable
    std::vector<int> previous;     ///< -1 for source and unreachable
};

namespace Dijkstra
{
    /// Get all the shortest paths from vertex 'source' to every other reachable
    /// vertex.
    ShortestPaths dijkstra(const Graph& graph, int source);

    /// Traverse through a struct of ShortestPaths to find the most efficient path.
    std::vector<int> pathTo(const ShortestPaths& paths, int target);
}
