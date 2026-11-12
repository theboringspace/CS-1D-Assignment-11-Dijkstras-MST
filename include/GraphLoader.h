#pragma once

#include <string>

class Graph;

/// Reads one vertex name per line from file and adds each to graph.
void initializeGraphVertices(Graph& graph, const std::string& file);

/// Reads one "From,To,Weight" edge per line from file and adds each to graph.
void initializeGraphEdges(Graph& graph, const std::string& file);

namespace GraphLoader
{
    /// Converts text to a finite weight; throws with lineNumber if it isn't a valid number.
    double parseWeight(const std::string& text, int lineNumber);

    /// Returns text with leading and trailing spaces, tabs, and '\r' removed.
    std::string trim(const std::string& text);
}
