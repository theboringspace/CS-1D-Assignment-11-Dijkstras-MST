#include "Dijkstra.h"
#include "PQ.h"

#include <limits>
#include <stack>
#include <algorithm>
#include <assert.h>
#include <stdexcept>

ShortestPaths Dijkstra::dijkstra(const Graph &graph, int source)
{
    assert(source > -1 && source < graph.vertexCount());

    // Constants
    const int VERTEX_COUNT{ graph.vertexCount() };

    // Initializations
    ShortestPaths result;
    result.source = source;
    result.distances = std::vector<double>(VERTEX_COUNT, std::numeric_limits<double>::infinity());
    result.previous  = std::vector<int>(VERTEX_COUNT, -1);
    result.distances[source] = 0.0;

    MinPQ pq;

    pq.push({0.0, source});

    while (!pq.empty())
    {
        auto [dist, currentVertex] = pq.top();
        pq.pop();

        // If entry is outdated, skip it.
        if (dist > result.distances[currentVertex]) continue;

        for (const auto& edge : graph.neighbors(currentVertex))
        {
            double potential{result.distances[currentVertex] + edge.weight};

            // Check if an edge provides a more cost-efficient path and update accordingly
            if (potential < result.distances[edge.to])
            {
                result.previous[edge.to] = currentVertex;
                result.distances[edge.to] = potential;

                pq.push({result.distances[edge.to], edge.to});
            }
        }
    }

    return result;
}

std::vector<int> Dijkstra::pathTo(const ShortestPaths& paths, int target)
{
    if (paths.distances[target] == std::numeric_limits<double>::infinity())
        throw std::runtime_error("Unreachable vertex: " + std::to_string(target));

    std::vector<int> result;
    std::stack<int> resultStack;

    resultStack.push(target);
    while (resultStack.top() != paths.source)
        resultStack.push(paths.previous[resultStack.top()]);


    while (!resultStack.empty())
    {
        result.push_back(resultStack.top());
        resultStack.pop();
    }

    return result;
}
