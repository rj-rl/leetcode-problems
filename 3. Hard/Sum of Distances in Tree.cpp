/*
        https://leetcode.com/problems/sum-of-distances-in-tree/
*/
#include <iostream>
#include <vector>

using namespace std;

void build_tree(const vector<vector<int>>& edges, vector<vector<int>>& graph)
{
    for (auto edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }
}

// Post-order traversal (left-right-node) which correctly fills distances
// within all the subtrees and calculates their sizes.
// This is enough info to get the final answer for root
void first_pass(int root, int parent, const vector<vector<int>>& graph,
                vector<int>& sizes, vector<int>& distances)
{
    for (auto node : graph[root]) {
        if (node != parent) {
            first_pass(node, root, graph,
                       sizes, distances);
            sizes[root] += sizes[node];
            distances[root] += distances[node] + sizes[node];
        }
    }
}

// Pre-order traversal (node-left-right), fills in the distances for every node
// (starting from the root's children) using the distances[root] calculated in first_pass
void second_pass(int root, int parent, int n, const vector<vector<int>>& graph,
                 vector<int>& sizes, vector<int>& distances)
{
    for (auto node : graph[root]) {
        if (node != parent) {
            distances[node] = distances[root] + n - 2 * sizes[node];
            second_pass(node, root, n, graph, sizes, distances);
        }
    }
}

vector<int> sumOfDistancesInTree(int n, const vector<vector<int>>& edges)
{
    constexpr int max = 10'000;
    vector<vector<int>> graph(max);
    vector<int> sizes(n, 1);
    vector<int> distances(n, 0);

    build_tree(edges, graph);
    first_pass(0, 0, graph, sizes, distances);
    second_pass(0, 0, n, graph, sizes, distances);

    return distances;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter n of vertices:\n";
        int n, n_nodes;
        cin >> n;
        n_nodes = n;

        cout << "Enter the edges:\n";
        vector<vector<int>> v;
        while (n - 1) {
            int from, to;
            cin >> from >> to;
            v.push_back({ from, to });
            --n;
        }
        cout << "Sums of distances between the nodes:\n";
        auto res = sumOfDistancesInTree(n_nodes, v);
        for (auto sum : res) {
            cout << sum << ' ';
        }
        cout << '\n';
    }
    return 0;
}
