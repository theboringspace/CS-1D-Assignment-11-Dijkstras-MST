/// @file   Partition.h
/// @brief  Union-find (Partition ADT) with path compression and union by rank.

#pragma once

#include <vector>
#include <algorithm>

/// Tree based implementation of Partition ADT
class Partition 
{
    public:
        /// Constructs a partition of n elements, initializing n disjoint sets
        explicit Partition(int n);

        int find(int v);
        bool unionSets(int u, int v);

    private:
        std::vector<int> parent;
        std::vector<int> rank;
};

/// Initialize partition of n disjoint sets
inline Partition::Partition(int n) : parent(n), rank(n, 0)
{
   for(int v = 0; v < n; v++)
        parent[v] = v;
}

/// Recursively finds the root of a set using path compression
inline int Partition::find(int v)
{
    if(parent[v] != v)
        parent[v] = find(parent[v]);

    return parent[v];
}

/// Merges two disjoint sets using union by rank
inline bool Partition::unionSets(int u, int v)
{
    int rootU = find(u);
    int rootV = find(v);

    if(rootU == rootV)
        return false;

    if(rank[rootU] < rank[rootV])
        std::swap(rootU, rootV);

    //union
    parent[rootV] = rootU;

    if(rank[rootU] == rank[rootV])
        rank[rootU]++;

    return true;
}
