
 /*
 * Problem   : LC239 — Sliding Window Maximum
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size + Monotonic Deque
 * Difficulty: Hard
 * Link      : https://leetcode.com/problems/sliding-window-maximum/
 *
 * Approach  :
 * - deque stores INDICES, front = index of maximum element
 * - deque is always decreasing (front = max, back = weakest)
 * - step 1: remove front if outside window (dq.front() < i-k+1)
 * - step 2: remove back if smaller than current (nums[back] < nums[i])
 * - step 3: push current index
 * - step 4: record answer when window formed (i >= k-1)
 *
 * Time      : O(n) — each element pushed and popped at most once
 * Space     : O(k) — deque stores at most k indices
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> dq;       // stores indices, front = max
        vector<int> result;

        for (int i = 0; i < n; i++) {
            // step 1 — remove front if outside window
            if (!dq.empty() && dq.front() < i - k + 1)
                dq.pop_front();

            // step 2 — remove smaller elements from back
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();

            // step 3 — push current index
            dq.push_back(i);

            // step 4 — window formed → record max
            if (i >= k - 1)
                result.push_back(nums[dq.front()]);
        }

        return result;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int k, vector<int> expected) {
        auto res = sol.maxSlidingWindow(nums, k);
        cout << "Input    : k=" << k << " → ";
        for (int x : nums) cout << x << " ";
        cout << "\nOutput   : ";
        for (int x : res) cout << x << " ";
        cout << "\nExpected : ";
        for (int x : expected) cout << x << " ";
        cout << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    // Test 1 — normal case
    run({1,3,-1,-3,5,3,6,7}, 3, {3,3,5,5,6,7});

    // Test 2 — k = 1 (every element is its own max)
    run({1,3,2,5,4}, 1, {1,3,2,5,4});

    // Test 3 — k = n (only one window)
    run({4,2,7,1}, 4, {7});

    // Test 4 — all same elements
    run({3,3,3,3}, 2, {3,3,3});

    // Test 5 — decreasing array
    run({5,4,3,2,1}, 3, {5,4,3});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : deque stores indices not values
 *                front = current maximum index
 *                back  = weakest candidate
 *                elements smaller than new arrival are useless → pop back
 *
 * MAX vs MIN   : MAX → remove smaller from back  nums[back] < nums[i]
 *                MIN → remove larger  from back  nums[back] > nums[i]
 *
 * Why O(n)     : each element pushed once + popped once = 2n ops total
 *
 * Bugs fixed   : dq.back() → dq.front() for outside window check
 *                > changed to < for max window (was giving min window)
 *
 * Edge cases   : k=1 → every element is max
 *                k=n → single window, max of whole array
 *
 * Mistakes made: checked dq.back() instead of dq.front() for stale index
 *                used > instead of < → was computing min not max
 */