#include "Graph.h"

#include <print>
#include <stdexcept>
#include <algorithm>

int Graph::addVertex(const std::string& name)
{
    if (nameExists(name)) throw std::invalid_argument("Vertex already exists: " + name);

    // Add vertex name to list of vectors
    names.push_back(name);

    std::size_t newIndex{names.size() - 1};

    // Add assign index to new vertex
    index.insert({name, newIndex});

    // Create empty neighbors list for new vertex
    adjacency_list.push_back({});

    return static_cast<int>(newIndex);
}

void Graph::addEdge(int from, int to, double weight)
{
    if (from == to) throw std::invalid_argument("No self-loops: " + std::to_string(from) + " - " + std::to_string(to));
    if (edgeExists(from, to)) throw std::invalid_argument("Edge already exists, cannot be overwritten: " + std::to_string(from) + " - " + std::to_string(to));
    if (weight < 0.0) throw std::invalid_argument("Negative weight between vertices: '" + nameOf(from) + " - " + nameOf(to) + "'");
    adjacency_list.at(from).push_back({to, weight});
}

void Graph::addEdge(const std::string& from, const std::string& to, double weight)
{
    int fromIndex{indexOf(from)};
    int toIndex{indexOf(to)};

    addEdge(fromIndex, toIndex, weight);
}

const std::vector<Graph::Edge>& Graph::neighbors(int v) const
{
    return adjacency_list.at(v);
}

int Graph::vertexCount() const
{
    return names.size();
}

int Graph::edgeCount() const
{
    int count{0};

    for (const auto& elem : adjacency_list)
    {
        count += elem.size();
    }

    // Each undirected edge is stored once in each direction
    return count / 2;
}

int Graph::indexOf(const std::string& name) const
{
    if (!nameExists(name)) throw std::out_of_range("Invalid vertex name: " + name);

    return index.at(name);
}

const std::string& Graph::nameOf(int v) const
{
    if (!indexExists(v)) throw std::out_of_range("Invalid vertex index: " + std::to_string(v));

    return names.at(v);
}

void Graph::printInfo() const
{
    std::println("{:<20}{:<15}{:<10}", "NAME", "INDEX", "NEIGHBORS");
    // Print names, their index, then the adjacency list for each.
    for (const auto& name : names)
    {
        const int index{indexOf(name)};
        std::print("{:<20}{:<15}", name, index);
        for (const auto& neighbor : neighbors(indexOf(name)))
        {
            const std::string neighborName = nameOf(neighbor.to);
            const double neighborWeight       = neighbor.weight;

            const std::string outputString = "[" + neighborName + "(" + std::to_string(neighborWeight) + ")" + "]";

            std::print("{:<25}", outputString);
        }
        std::println();
    }

    std::println("# of vertices: {}", vertexCount());
    std::println("# of edges: {}", edgeCount());
}

bool Graph::edgeExists(int from, int to) const
{
    if (!indexExists(from)) throw std::out_of_range("Invalid vertex index: " + std::to_string(from));
    if (!indexExists(to)) throw std::out_of_range("Invalid vertex index: " + std::to_string(to));

    const auto& edges = neighbors(from);

    return std::any_of(edges.begin(), edges.end(), [to](const Edge& e) { return e.to == to; });
}

bool Graph::indexExists(int v) const
{
    return v >= 0 && v < static_cast<int>(names.size());
}

bool Graph::nameExists(const std::string& name) const
{
    auto it = std::find(names.begin(), names.end(), name);
    return it != names.end();
}
