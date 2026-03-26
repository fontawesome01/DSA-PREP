/*
 * Problem   : LC303 — Range Sum Query - Immutable
 * Topic     : Arrays
 * Pattern   : Prefix Sum — O(1) Range Query
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/range-sum-query-immutable/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Step 1 — Brute force
 *   sum from left to right every call → O(n) per query
 *   if called q times → O(n * q) total
 *
 * Step 2 — Observation
 *   array never changes (immutable)
 *   → precompute something once, answer queries fast
 *
 * Step 3 — Prefix sum trick
 *   prefix[i] = sum of nums[0..i-1]
 *   prefix[0] = 0 (empty prefix — no elements)
 *
 *   sum(left, right) = prefix[right+1] - prefix[left]
 *
 * Step 4 — Why size n+1 with prefix[0] = 0?
 *   avoids if-else for left == 0 edge case
 *   sum(0, r) = prefix[r+1] - prefix[0] = prefix[r+1] - 0 ✅
 *
 * ═══════════════════════════════════════════════════
 *
 * Visual:
 *   nums   = [1,  2,  3,  4,  5]
 *   prefix = [0,  1,  3,  6, 10, 15]
 *             ↑
 *             always starts with 0
 *
 *   sumRange(1,3) = prefix[4] - prefix[1] = 10 - 1 = 9
 *                   (2 + 3 + 4 = 9) ✅
 *
 * Time  : O(n) build, O(1) per query
 * Space : O(n) — prefix array
 */

#include <bits/stdc++.h>
using namespace std;

class NumArray {
    vector<int> prefix;

public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

int main() {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray obj(nums);

    auto test = [&](int l, int r, int expected) {
        int res = obj.sumRange(l, r);
        cout << "sumRange(" << l << "," << r << ") = " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n";
    };

    test(0, 2, 1);    // -2 + 0 + 3 = 1
    test(2, 5, -1);   // 3 + (-5) + 2 + (-1) = -1
    test(0, 5, -3);   // entire array sum = -3

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : prefix[0] = 0 eliminates edge case for left == 0
 *
 * Formula      : sum(l, r) = prefix[r+1] - prefix[l]
 *                NOT prefix[r] - prefix[l-1] (would need l-1 >= 0 check)
 *
 * Why n+1 size : prefix[i] stores sum of first i elements
 *                prefix[0] = 0 → sum of zero elements
 *                prefix[n] = total array sum
 *
 * Connection   : this exact prefix array is used in:
 *                LC560 — prefix sum + hashmap
 *                LC974 — prefix sum + modular arithmetic
 *                LC862 — prefix sum + monotonic deque
 */