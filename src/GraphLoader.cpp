#include "GraphLoader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <charconv>
#include <cmath>
#include <system_error>

#include "Graph.h"

void initializeGraphVertices(Graph& graph, const std::string& file)
{
    std::ifstream input(file);

    if (!input) throw std::runtime_error("Could not open file: " + file);

    std::string line;
    while (std::getline(input, line))
    {
        const std::string name{GraphLoader::trim(line)};

        // Skip blank lines (e.g. a trailing newline at the end of the file)
        if (name.empty()) continue;

        graph.addVertex(name);
    }
}

void initializeGraphEdges(Graph& graph, const std::string& file)
{
    std::ifstream input(file);

    if (!input) throw std::runtime_error("Could not open file: " + file);

    std::string from;
    std::string to;
    std::string stWeight;

    std::string line;
    int lineNumber{0};
    while (std::getline(input, line))
    {
        ++lineNumber;

        // Skip blank lines (e.g. a trailing newline at the end of the file)
        if (GraphLoader::trim(line).empty()) continue;

        // Split the line into its From, To, and Weight fields
        std::istringstream ss(line);

        if (!std::getline(ss, from, ',') || !std::getline(ss, to, ',') || !std::getline(ss, stWeight))
            throw std::invalid_argument("Too few fields: line #" + std::to_string(lineNumber));

        from     = GraphLoader::trim(from);
        to       = GraphLoader::trim(to);
        stWeight = GraphLoader::trim(stWeight);

        if (from.empty() || to.empty())
            throw std::invalid_argument("Empty vertex name: line #" + std::to_string(lineNumber));

        graph.addEdge(from, to, GraphLoader::parseWeight(stWeight, lineNumber));
    }
}

double GraphLoader::parseWeight(const std::string& text, int lineNumber)
{
    double value{};

    // from_chars reports errors through its return value instead of throwing
    const auto end{text.data() + text.size()};
    const auto [stoppedAt, error]{std::from_chars(text.data(), end, value)};

    // Non-numeric text, or a number too large/small to fit in a double
    if (error != std::errc{}) throw std::runtime_error("Line " + std::to_string(lineNumber) + ": Invalid weight '" + text + "'");

    // Parsing stopped before the end of the field
    if (stoppedAt != end) throw std::runtime_error("Line " + std::to_string(lineNumber) + ": Junk after weight '" + text + "'");

    // from_chars accepts "nan" and "inf", which are not real distances
    if (!std::isfinite(value)) throw std::runtime_error("Line " + std::to_string(lineNumber) + ": Weight must be a finite number '" + text + "'");

    return value;
}

std::string GraphLoader::trim(const std::string& text)
{
    constexpr std::string_view whitespace{" \t\r"};

    const std::size_t first{text.find_first_not_of(whitespace)};

    // All whitespace (or empty): nothing to keep
    if (first == std::string::npos) return "";

    const std::size_t last{text.find_last_not_of(whitespace)};

    return text.substr(first, last - first + 1);
}
