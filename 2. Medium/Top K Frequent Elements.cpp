/*
  https://leetcode.com/problems/top-k-frequent-elements/

  Given an integer array 'nums' and an integer 'k', return the 'k' most frequent elements.
  You may return the answer in any order
/**/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <stdexcept>

using namespace std;

template <class TComparable>
class IndexedPriorityQueue {
public:
    using Id = int;
public:
    IndexedPriorityQueue(size_t max_size = 0u)
        : pq_(max_size + 1)
        , qp_(max_size + 1, -1)
        , items_(max_size + 1)
        , N_ {0u}
    { }

    bool        isEmpty() const
    {
        return N_ == 0;
    }
    bool        contains(Id id) const
    {
        return qp_[id] != -1;
    }
    size_t      size() const
    {
        return N_;
    }
    size_t      maxSize() const
    {
        return pq_.size() - 1;  // guaranteed to be >= 0
    }
    TComparable delMax();
    TComparable max() const
    {
        if (isEmpty()) throw runtime_error("max called on empty queue");
        return items_[pq_[1]];
    }
    Id          maxId() const { return pq_[1]; }
    void        insert(Id id, TComparable v);
    void        change(Id id, TComparable v);
    void        changePriority(Id id, int newPriority);
    void        increasePriority(Id id, int boost = 1);
    void        remove(Id id);

private:
    size_t              N_;     // number of elements in the queue
    vector<Id>          pq_;    // priority queue using 1-based indexing
    vector<size_t>      qp_;    // inverse of pq_: pq_[qp_[i]] = qp_[pq_[i]] = i
    vector<TComparable> items_; // stored items with priorities

    void sink(size_t i);
    void swim(size_t i);
    bool less(size_t i, size_t j);
    void exch(size_t i, size_t j);
};

template <class TComparable>
TComparable IndexedPriorityQueue<TComparable>::delMax()
{
    if (isEmpty()) throw runtime_error("delMax called on empty queue");

    TComparable max = move(items_[pq_[1]]);
    exch(1, N_);
    --N_;
    sink(1);
    return max;
}

template <class TComparable>
void IndexedPriorityQueue<TComparable>::insert(Id id, TComparable v)
{
    ++N_;
    items_[id] = move(v);
    pq_[N_] = id;
    qp_[id] = N_;
    swim(N_);
}

template <class TComparable>
void IndexedPriorityQueue<TComparable>::change(Id id, TComparable v)
{
    if (!contains(id)) throw runtime_error("change called for non-existent id");

    items_[id] = move(v);
    sink(qp_[id]);
    swim(qp_[id]);
}

template<class TComparable>
void IndexedPriorityQueue<TComparable>::changePriority(Id id, int newPriority)
{
    if (!contains(id)) throw runtime_error("change called for non-existent id");

    items_[id].priority = newPriority;
    sink(qp_[id]);
    swim(qp_[id]);
}

template<class TComparable>
void IndexedPriorityQueue<TComparable>::increasePriority(Id id, int boost)
{
    if (!contains(id)) throw runtime_error("increase called for non-existent id");

    items_[id].priority += boost;
    sink(qp_[id]);
    swim(qp_[id]);
}

template<class TComparable>
void IndexedPriorityQueue<TComparable>::remove(Id id)
{
    if (isEmpty()) throw runtime_error("remove called on empty queue");

    items_[id] = TComparable {};    // empty the slot

    auto pq_idx = qp_[id];
    exch(pq_idx, N_);
    --N_;
    sink(pq_idx);
    swim(pq_idx);

    qp_[id] = -1;
}

template <class TComparable>
void IndexedPriorityQueue<TComparable>::sink(size_t k)
{
    while (2 * k <= N_) {
        size_t bigger_child_idx {2 * k};
        if (bigger_child_idx < N_ && less(pq_[bigger_child_idx], pq_[bigger_child_idx + 1])) {
            ++bigger_child_idx;
        }
        if (pq_[k] < pq_[bigger_child_idx]) {
            exch(k, bigger_child_idx);
            k = bigger_child_idx;
        }
        else break;
    }
}

template <class TComparable>
void IndexedPriorityQueue<TComparable>::swim(size_t k)
{
    while (k > 1 && less(pq_[k / 2], pq_[k])) {
        exch(k, k / 2);
        k /= 2;
    }
}

template <class TComparable>
bool IndexedPriorityQueue<TComparable>::less(size_t i, size_t j)
{
    return items_[i] > items_[j];
}

template <class TComparable>
void IndexedPriorityQueue<TComparable>::exch(size_t i, size_t j)
{
    swap(qp_[pq_[i]], qp_[pq_[j]]);
    swap(pq_[i], pq_[j]);
}

//==============================================================================================//

struct NumWithPriority {
    int num = 0;
    int priority = 0;
};

bool operator>(NumWithPriority left, NumWithPriority right)
{
    return left.priority > right.priority;
}

//==============================================================================================//

// HOMEBREW IndexedPriorityQueue VERSION
vector<int> topKFrequentMyVersion(const vector<int>& nums, int k)
{
    int size = nums.size();
    IndexedPriorityQueue<NumWithPriority> queue(size);

    for (auto num : nums) {
        if (queue.contains(num)) {
            queue.increasePriority(num);
        }
        else {
            queue.insert(num, NumWithPriority {num, 1});
            if (queue.size() > k) queue.delMax();
        }
    }

    vector<int> result;
    while (!queue.isEmpty()) {
        result.push_back(queue.delMax().num);
    }
    return result;
}

struct CompareGreater {
    bool operator()(NumWithPriority left, NumWithPriority right)
    {
        return left.priority > right.priority;
    }
};

// STL ez version
vector<int> topKFrequentTETETE(const vector<int>& nums, int k)
{
    if (nums.size() == k) return nums;

    // count all the frequencies
    unordered_map<int, int> num_frequencies;
    for (auto num : nums) {
        ++num_frequencies[num];
    }

    priority_queue<
        NumWithPriority,
        vector<NumWithPriority>,
        CompareGreater
    > queue;
    // populate the priority queue
    for (auto [num, freq] : num_frequencies) {
        queue.push(NumWithPriority {num, freq});
        if (queue.size() > k) queue.pop();
    }

    vector<int> result;
    while (!queue.empty()) {
        result.push_back(queue.top().num);
        queue.pop();
    }
    return result;
}

// without using a priority queue at all
vector<int> topKFrequent(const vector<int>& nums, int k)
{
    if (nums.size() == k) return nums;

    // count all the frequencies
    unordered_map<int, int> num_frequencies;
    for (auto num : nums) {
        ++num_frequencies[num];
    }

    unordered_map<int, vector<int>> freq_nums;
    // need to remember the max frequency to be able to iterate backwards 
    // over the 'freq_nums' hashtable in the range [0, max_freq]
    int max_freq = 0;
    for (auto [num, freq] : num_frequencies) {
        freq_nums[freq].push_back(num);
        if (freq > max_freq) max_freq = freq;
    }

    vector<int> result;
    while (max_freq > 0) {
        if (freq_nums.count(max_freq) > 0) {
            for (auto num : freq_nums[max_freq]) {
                result.push_back(num);
                --k;
                if (k == 0) return result;
            }
        }
        --max_freq;
    }
    return result;
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter n:\n";
        int n {};
        cin >> n;

        cout << "Enter the array:\n";
        vector<int> nums;
        while (n-- > 0) {
            int x {};
            cin >> x;
            nums.push_back(x);
        }

        cout << "Enter k:\n";
        int k {};
        cin >> k;

        auto topK = topKFrequent(nums, k);
        cout << "Here's the top k most frequent numbers\n";
        for (auto num : topK) {
            cout << num << ' ';
        }
        cout << '\n';
    }
    return 0;
}
