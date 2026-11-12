#include <cstdlib>
#include <cstdio>

#include <print>
#include <string>
#include <exception>

#include <functional>

#include "Graph.h"
#include "GraphLoader.h"


int main()
{
    Graph cities;

    // Any error while loading or printing ends up here, reported once
    try
    {
        initializeGraphVertices(cities, "data/Vertices.txt");
        initializeGraphEdges(cities, "data/Edges.txt");
        cities.printInfo();
    }
    catch (const std::exception& e)
    {
        std::println(stderr, "Error: {}", e.what());
        return EXIT_FAILURE;
    }





    return EXIT_SUCCESS;
}
