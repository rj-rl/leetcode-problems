/*
  https://leetcode.com/problems/last-stone-weight/
/**/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int lastStoneWeight(vector<int>& stones)
{
    make_heap(begin(stones), end(stones));

    while (stones.size() > 1) {
        int biggest = stones.front();
        pop_heap(begin(stones), end(stones));
        stones.pop_back();

        int slightly_smaller = stones.front();
        pop_heap(begin(stones), end(stones));
        stones.pop_back();

        int leftover = biggest - slightly_smaller;
        if (leftover > 0) {
            stones.push_back(leftover);
            push_heap(begin(stones), end(stones));
        }
    }
    return stones.empty() ? 0 : stones[0];
}

// requires no extra memory
int lastStoneWeight_ez_version(vector<int>& stones)
{
    priority_queue queue(begin(stones), end(stones));

    while (queue.size() > 1) {
        int biggest = queue.top();
        queue.pop();
        int slightly_smaller = queue.top();
        queue.pop();

        int leftover = biggest - slightly_smaller;
        if (leftover > 0) queue.push(leftover);
    }
    return queue.empty() ? 0 : queue.top();
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter the array size:\n";
        int n {};
        cin >> n;
        
        cout << "Enter the array:\n";
        vector<int> stones;
        while (n-- > 0) {
            int x {};
            cin >> x;
            stones.push_back(x);
        }

        cout << "What's left is\n"
            << lastStoneWeight(stones) << '\n';
    }
    return 0;
}
