#pragma once

#include <queue>
#include <vector>

using PQEntry = std::pair<double, int>;                                                     // distance, vertex index
using MinPQ   = std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>>;  // Min-based priority queue
