#pragma once

#include <vector>
#include <algorithm>

//Tree based implementation of Partition ADT
class Partition 
{
    public:
        //construct partition of n elements, initializing n disjoint sets
        explicit Partition(int n);

        int find(int v);
        bool unionSets(int u, int v);

    private:
        std::vector<int> parent;
        std::vector<int> rank;
};

//initialize partition of n disjoint sets
inline Partition::Partition(int n) : parent(n), rank(n, 0)
{
   for(int v = 0; v < n; v++)
        parent[v] = v;
}

//recursively finds the root with path compression
inline int Partition::find(int v)
{
    if(parent[v] != v)
        parent[v] = find(parent[v]);

    return parent[v];
}

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