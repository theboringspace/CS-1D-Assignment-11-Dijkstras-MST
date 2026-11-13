#include <cstdlib>
#include <cstdio>

#include <print>
#include <string>
#include <exception>

#include <functional>

#include "Graph.h"
#include "GraphLoader.h"

#include "Dijkstra.h"

void displayDijkstra(const Graph& graph, const std::string& start);

int main()
{
    Graph cities;

    // Any error while loading or printing ends up here, reported once
    try
    {
        initializeGraphVertices(cities, "data/Vertices.txt");
        initializeGraphEdges(cities, "data/Edges.txt");
        cities.printInfo();

        displayDijkstra(cities, "Denver");
        displayDijkstra(cities, "Miami");

    }
    catch (const std::exception& e)
    {
        std::println(stderr, "Error: {}", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void displayDijkstra(const Graph& graph, const std::string& start)
{
    ShortestPaths paths{Dijkstra::dijkstra(graph, graph.indexOf(start))};

    std::println("Paths from {} to everything else:", start);
    for (int target{0}; target < graph.vertexCount(); ++target)
    {
        if (target == graph.indexOf(start)) continue;

        std::vector<int> path{Dijkstra::pathTo(paths, target)};

        std::print("{}", start);
        for (auto it = path.cbegin() + 1; it != path.cend(); ++it)
        {
            std::print(" -> {} ", graph.nameOf(*it));
        }
        std::println("\nTotal Distance: {} mi", paths.distances[target]);
    }
}
