#pragma once

#include <unordered_map>
#include <vector>
#include <string>

/// Undirected weighted adjacency-list graph that stores vertices as indices 0 to V-1
/// internally and maps to indices at the edges of the API.
class Graph
{
private:
    struct Edge
    {
        int to;                                                                     ///< index of the neighbor vertex
        double weight;                                                              ///< weight (distance) of the edge
    };
public:
    Graph() = default;

    int addVertex(const std::string& name);                                         ///< returns its index
    void addEdge(int from, int to, double weight);                                  ///< adds edge from vertex v to vertex u via index
    void addEdge(const std::string& from, const std::string& to, double weight);    ///< adds edge from vertex v to vertex u via name

    const std::vector<Edge>& neighbors(int v) const;                                ///< returns an array of edges for a vertex
    int vertexCount() const;                                                        ///< returns the number of vertices
    int edgeCount() const;                                                          ///< returns the number of undirected edges

    int indexOf(const std::string& name) const;                                     ///< returns the index for a vertex name; throws if not found
    const std::string& nameOf(int v) const;                                         ///< returns the name for a vertex index; throws if out of range

    // Testing Functions
    void printInfo() const;                                                         ///< prints each vertex with its index and neighbors

private:
    std::vector<std::vector<Edge>> adjacency_list;                                  ///< adjacency_list[v] holds the edges of vertex v
    std::vector<std::string> names;                                                 ///< names[v] is the name of vertex v
    std::unordered_map<std::string, int> index;                                     ///< maps a vertex name to its index

    bool edgeExists(int from, int to) const;                                        ///< true if from already has an edge to to
    bool indexExists(int v) const;                                                  ///< true if v is a valid vertex index
    bool nameExists(const std::string& name) const;                                 ///< true if a vertex with this name exists
};
