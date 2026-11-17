#include <cstdlib>
#include <cstdio>

#include <format>
#include <print>
#include <string>
#include <exception>

#include <functional>

#include "Graph.h"
#include "GraphLoader.h"

#include "Dijkstra.h"
#include "KruskalMST.h"

void printHeader(const std::string& title);
void displayDijkstra(const Graph& graph, const std::string& start);
void displayKruskal(const Graph& graph);

int main()
{
    Graph cities;

    // Any error while loading or printing ends up here, reported once
    try
    {
        initializeGraphVertices(cities, "data/Vertices.txt");
        initializeGraphEdges(cities, "data/Edges.txt");

        printHeader("GRAPH INFORMATION");
        cities.printInfo();

        printHeader("DIJKSTRA'S ALGORITHM RESULT STARTING AT DENVER");
        displayDijkstra(cities, "Denver");

        printHeader("MINIMUM SPANNING TREE RESULT");
        displayKruskal(cities);
    }
    catch (const std::exception& e)
    {
        std::println(stderr, "Error: {}", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/// Prints a banner announcing the next block of output
void printHeader(const std::string& title)
{
    const std::string bar(70, '=');
    std::println("\n{}\n{}\n{}", bar, title, bar);
}

void displayDijkstra(const Graph& graph, const std::string& start)
{
    ShortestPaths paths{Dijkstra::dijkstra(graph, graph.indexOf(start))};

    std::println("{:<20}{:<15}{}", "DESTINATION", "DISTANCE", "PATH");
    for (int target{0}; target < graph.vertexCount(); ++target)
    {
        if (target == graph.indexOf(start)) continue;

        std::vector<int> path{Dijkstra::pathTo(paths, target)};

        std::print("{:<20}{:<15}{}", graph.nameOf(target),
                   std::format("{} mi", paths.distances[target]), start);
        for (auto it = path.cbegin() + 1; it != path.cend(); ++it)
        {
            std::print(" -> {}", graph.nameOf(*it));
        }
        std::println();
    }
}

void displayKruskal(const Graph& graph)
{
    MinimumSpanningTree mst = kruskalMST(graph);

    for(const auto& edge : mst.edges)
    {
        std::println("{} -- {} : {} mi", 
                     graph.nameOf(edge.from),       
                     graph.nameOf(edge.to),
                     edge.weight);
    }

    std::println("\nTotal Mileage: {} mi", mst.totalWeight);
}
