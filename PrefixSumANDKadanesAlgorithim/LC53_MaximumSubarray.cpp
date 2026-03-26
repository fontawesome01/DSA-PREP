/*
 * Problem   : LC53 — Maximum Subarray
 * Topic     : Arrays
 * Pattern   : Kadane's Algorithm
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/maximum-subarray/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Step 1 — Brute force
 *   check all subarrays → O(n²)
 *   for each start, expand end, track sum
 *
 * Step 2 — Key observation
 *   at each index, only 2 choices:
 *     (a) extend previous subarray → currentSum + nums[i]
 *     (b) start fresh from here    → nums[i]
 *   pick whichever is larger
 *
 * Step 3 — Why does this work?
 *   if currentSum < 0 → adding it hurts → start fresh
 *   if currentSum >= 0 → extending helps → keep going
 *   this is equivalent to: currentSum = max(nums[i], currentSum + nums[i])
 *
 * Step 4 — Track global maximum
 *   maxSum = max(maxSum, currentSum) at every step
 *
 * ═══════════════════════════════════════════════════
 *
 * Visual:
 *   nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 *
 *   i=0: curr=-2  max=-2
 *   i=1: curr= 1  max= 1  (fresh, -2 was hurting)
 *   i=2: curr=-2  max= 1
 *   i=3: curr= 4  max= 4  (fresh start)
 *   i=4: curr= 3  max= 4
 *   i=5: curr= 5  max= 5
 *   i=6: curr= 6  max= 6  ← answer
 *   i=7: curr= 1  max= 6
 *   i=8: curr= 5  max= 6
 *
 *   Answer = 6 → subarray [4, -1, 2, 1]
 *
 * Time  : O(n)
 * Space : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int maxSum = nums[0];
        int currentSum = nums[0];

        for (int i = 1; i < n; i++) {
            currentSum = max(nums[i], currentSum + nums[i]);
            maxSum = max(maxSum, currentSum);
        }

        return maxSum;
    }
};

int main() {
    Solution sol;

    auto test = [&](vector<int> nums, int expected) {
        int res = sol.maxSubArray(nums);
        cout << "Output: " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n";
    };

    test({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6);  // [4,-1,2,1]
    test({1}, 1);                                  // single element
    test({5, 4, -1, 7, 8}, 23);                   // entire array
    test({-1}, -1);                                // all negative single
    test({-3, -2, -1}, -1);                        // all negative

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : at each index → extend OR start fresh
 *                currentSum = max(nums[i], currentSum + nums[i])
 *
 * Init trap    : maxSum = 0 fails on all-negative arrays
 *                must init to nums[0], loop from i = 1
 *
 * INT_MIN trap : INT_MIN + negative = overflow (undefined behavior in C++)
 *                nums[0] init is safer and cleaner
 *
 * Equivalent   : if (currentSum < 0) currentSum = 0;
 *                currentSum += nums[i];
 *                → same logic, but fails if all negative (returns 0)
 *                → the max() version handles everything
 *
 * Connection   : Kadane's is a special case of DP
 *                dp[i] = max subarray ending at i
 *                dp[i] = max(nums[i], dp[i-1] + nums[i])
 *                we just compress dp[] into a single variable
 *
 * Variations   : LC152 — Maximum Product Subarray (track min too)
 *                LC918 — Max Subarray Sum Circular
 *                LC862 — Shortest Subarray Sum ≥ K (deque)
 */