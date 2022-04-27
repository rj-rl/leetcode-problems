/*
  https://leetcode.com/problems/smallest-string-with-swaps/

  You are given a string 's', and an array of pairs of indices 'pairs'
  where 'pairs[i] = [a, b]' indicates 2 indices of the string 's'.
  For every pair '[a, b]' in 'pairs' you can swap 's[a]' and 's[b]'
  any number of times.

  Return the lexicographically smallest string that 's' can be
  morphed into by swapping the pairs defined by 'pairs'
/**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <utility>
#include <cassert>

using namespace std;

class DisjointSet {
public:
    DisjointSet(std::size_t size)
        : id_(size)
        , size_(size)
        , component_count_(size)
    {
        for (std::size_t i = 0; i < size; ++i) {
            id_[i] = i;
            size_[i] = 1;
        }
    }

    // returns number of components
    std::size_t count() const
    {
        return component_count_;
    }
    // returns component id for site 'p'
    std::size_t find(std::size_t p)
    {
        // make sure 'p' is a valid site id
        assert(p < id_.size());
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
    // returns true if 'p' and 'q' are in the same component
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
        --component_count_;
    }

private:
    std::vector<std::size_t> id_;    // site-indexed components
    std::vector<std::size_t> size_;  // sizes of trees
    std::size_t component_count_;              // number of components
};

string smallestStringWithSwaps(string s, const vector<vector<int>>& pairs)
{
    // build the disjoint set forest of unified components
    DisjointSet components(s.length());
    for (auto& pair : pairs) {
        components.unify(pair[0], pair[1]);
    }

    // build the heap for the root of each tree;
    // these heaps are then used to sort substrings corresponding to components
    unordered_map<
        size_t, 
        priority_queue<char, vector<char>, greater<>>
        > heapified_components;
    for (size_t i = 0u; i < s.length(); ++i) {
        auto root = components.find(i);
        heapified_components[root].push(s[i]);
    }

    // construct the string out of the sorted substrings
    for (size_t i = 0u; i < s.length(); ++i) {
        auto root = components.find(i);
        s[i] = heapified_components[root].top();
        heapified_components[root].pop();
    }
    return s;
}

//==============================================================================================//

int main()
{
    // TODO: ask for input, present the output
    string input_s = "dcab";
    vector<vector<int>> input = 
        {{0, 3},
         {1, 2},
         {0, 2}
        };
    cout << smallestStringWithSwaps(input_s, input) << '\n';

    return 0;
}
