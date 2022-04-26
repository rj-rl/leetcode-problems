/*
  https://leetcode.com/problems/min-cost-to-connect-all-points/

  You are given an 'array' points representing integer coordinates
  of some points on a 2D-plane.

  Return the minimum cost to make all points connected. The cost of connecting
  two points is the manhattan distance between them. All points are connected
  if there is exactly one simple path between any two points
/**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

class DisjointSet {
public:
    DisjointSet(std::size_t size)
        : id_(size)
        , size_(size)
        , count_(size)
    {
        for (std::size_t i = 0; i < size; ++i) {
            id_[i] = i;
            size_[i] = 1;
        }
    }

    // returns number of components
    std::size_t count() const
    {
        return count_;
    }
    // returns true if 'p' and 'q' are in the same component
    std::size_t find(std::size_t p)
    {
        // find the root, i.e. the component id for p
        auto root = p;
        while (id_[root] != root) {
            root = id_[root];
        }
        // path compression: point all links on the way directly to component's root
        // which reduces the tree's height
        while (id_[p] != p) {
            auto old_parent = id_[p];
            id_[p] = root;
            p = old_parent;
        }
        return p;
    }
    // same as regular 'find' but compresses the path travelled
    bool connected(std::size_t p, std::size_t q)
    {
        auto pID = find(p);
        auto qID = find(q);
        return pID == qID;
    }
    // connects sites 'p' and 'q'
    void unify(std::size_t p, std::size_t q)
    {
        auto pID = find(p);
        auto qID = find(q);
        if (pID == qID) return;

        if (size_[pID] < size_[qID]) {
            id_[pID] = qID;
            size_[qID] += size_[pID];
        }
        else {
            id_[qID] = pID;
            size_[pID] += size_[qID];
        }
        // two components are merging together, decrease the count
        --count_;
    }

private:
    std::vector<std::size_t> id_;    // site-indexed components
    std::vector<std::size_t> size_;  // sizes of trees
    std::size_t count_;              // number of components
};

struct Edge {
    size_t start = 0;
    size_t end = 0;
    int weight = 0;

    Edge(size_t s, size_t e, int w)
        : start {s}, end {e}, weight {w}
    { }
};

int distance(int x_a, int y_a, int x_b, int y_b)
{
    return abs(x_a - x_b) + abs(y_a - y_b);
}

int minCostConnectPoints(const vector<vector<int>>& points)
{
    size_t vertice_count = points.size();
    if (vertice_count < 2) return 0;

    vector<Edge> edges;
    for (size_t i = 0; i < vertice_count; ++i) {
        for (size_t j = i + 1; j < vertice_count; ++j) {
            edges.emplace_back(
                i, j,
                distance(points[i][0], points[i][1],
                         points[j][0], points[j][1])
            );
        }
    }

    auto comp = [](const Edge& a, const Edge& b)
        {
            return a.weight > b.weight;
        };
    make_heap(begin(edges), end(edges), comp);

    DisjointSet components(vertice_count);
    auto edge = edges.front();
    pop_heap(begin(edges), end(edges), comp);
    edges.pop_back();

    components.unify(edge.start, edge.end);
    int min_cost_path = edge.weight;
    size_t initial = edge.start;

    while (components.count() > 1) {
        auto edge = edges.front();
        pop_heap(begin(edges), end(edges), comp);
        edges.pop_back();
        if (!components.connected(edge.start, edge.end)) {
            components.unify(edge.start, edge.end);
            min_cost_path += edge.weight;
        }
    }
    return min_cost_path;
}

//==============================================================================================//

int main()
{
    while (true) {
        vector<vector<int>> input;
        // TODO ask for input
        cout << minCostConnectPoints(input) << '\n';
    }
    return 0;
}
