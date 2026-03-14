/*
 * Problem   : LC480 — Sliding Window Median
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size + Two Heaps + Lazy Deletion
 * Difficulty: Hard
 * Link      : https://leetcode.com/problems/sliding-window-median/
 *
 * Why normal sliding window fails:
 * - sum/count depend on all elements equally → O(1) slide works
 * - median depends on sorted order → no formula exists
 *   new_median ≠ old_median - outgoing + incoming
 *   middle position shifts unpredictably on every insert/delete
 *
 * Approach — Two Heaps + Lazy Deletion:
 * - maxHeap → lower half of window (top = largest of lower half)
 * - minHeap → upper half of window (top = smallest of upper half)
 * - median  → maxHeap.top() (odd k) or avg of both tops (even k)
 *
 * Heap balance rules:
 * - maxHeap.size() == minHeap.size()     (even window)
 * - maxHeap.size() == minHeap.size() + 1 (odd window)
 * - maxHeap.top() <= minHeap.top() always
 *
 * Lazy deletion:
 * - heaps don't support arbitrary deletion
 * - mark element in toDelete map
 * - only actually remove when it reaches the top
 *
 * Time      : O(n log k)
 * Space     : O(k)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    priority_queue<int> maxH;
    priority_queue<int, vector<int>, greater<int>> minH;
    unordered_map<int, int> toDelete;

    void addNum(int num) {
        if (maxH.empty() || num <= maxH.top())
            maxH.push(num);
        else
            minH.push(num);
        rebalance();
    }

    void removeNum(int num) {
        toDelete[num]++;
        cleanTops();
        rebalance();
        cleanTops();
    }

    void rebalance() {
        if (maxH.size() > minH.size() + 1) {
            minH.push(maxH.top());
            maxH.pop();
        }
        if (minH.size() > maxH.size()) {
            maxH.push(minH.top());
            minH.pop();
        }
    }

    void cleanTops() {
        while (!maxH.empty() && toDelete[maxH.top()]) {
            toDelete[maxH.top()]--;
            maxH.pop();
        }
        while (!minH.empty() && toDelete[minH.top()]) {
            toDelete[minH.top()]--;
            minH.pop();
        }
    }

    double getMedian(int k) {
        if (k % 2 == 1)
            return maxH.top();
        return ((double)maxH.top() + minH.top()) / 2.0;
    }

public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> result;

        for (int i = 0; i < k; i++)
            addNum(nums[i]);

        result.push_back(getMedian(k));

        for (int i = k; i < n; i++) {
            addNum(nums[i]);
            removeNum(nums[i - k]);
            result.push_back(getMedian(k));
        }

        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int k, vector<double> expected) {
        auto res = sol.medianSlidingWindow(nums, k);
        cout << "Input    : k=" << k << " → ";
        for (int x : nums) cout << x << " ";
        cout << fixed << setprecision(1);
        cout << "\nOutput   : ";
        for (double x : res) cout << x << " ";
        cout << "\nExpected : ";
        for (double x : expected) cout << x << " ";
        cout << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    // Test 1 — odd k
    run({1,3,-1,-3,5,3,6,7}, 3, {1.0,-1.0,-1.0,3.0,5.0,6.0});

    // Test 2 — even k
    run({1,2,3,4,2,3,1,4,2}, 3, {2.0,3.0,3.0,3.0,2.0,3.0,2.0});

    // Test 3 — k=1
    run({1,3,2}, 1, {1.0,3.0,2.0});

    // Test 4 — all same
    run({2,2,2,2}, 2, {2.0,2.0,2.0});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : two heaps maintain sorted halves at all times
 *                median always at tops → O(1) query
 *                insert/delete → O(log k)
 *
 * Why lazy deletion:
 *   heaps only support remove from top
 *   outgoing element might be anywhere in heap
 *   mark it → skip when it reaches top naturally
 *
 * Why clean twice in removeNum:
 *   first clean  → remove stale tops before rebalance
 *   rebalance    → moves elements between heaps
 *   second clean → new tops might also be stale after rebalance
 *
 * Revisit after : Heaps chapter
 *                 code from scratch after learning heap internals
 *
 * Mistakes made : 
 */