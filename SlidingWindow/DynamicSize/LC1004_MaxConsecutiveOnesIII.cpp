/*
 * Problem   : LC1004 — Max Consecutive Ones III
 * Topic     : Arrays
 * Pattern   : Sliding Window — Dynamic Size
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/max-consecutive-ones-iii/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Step 1 — Reframe the problem
 *   "flip at most k zeros" = "find longest window with at most k zeros"
 *   don't think about flipping → think about window validity
 *
 * Step 2 — What makes window VALID?
 *   zeros in window <= k
 *   zeros = window size - count of ones
 *   valid when: (right - left + 1) - count <= k
 *
 * Step 3 — Track ones count
 *   count++ when nums[right] == 1
 *   count-- when nums[left] == 1 (on shrink)
 *   zeros = window - count (no separate zero counter needed)
 *
 * Step 4 — Same pattern as LC424
 *   LC424: window - maxFreq <= k  (chars to replace)
 *   LC1004: window - count <= k   (zeros to flip)
 *   exact same structure!
 *
 * ═══════════════════════════════════════════════════
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0;
        int result = 0;
        int count = 0;

        for (int right = 0; right < n; right++) {
            if (nums[right] == 1) count++;

            while (right - left + 1 - count > k) {
                if (nums[left] == 1) count--;
                left++;
            }

            result = max(result, right - left + 1);
        }

        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int k, int expected) {
        int res = sol.longestOnes(nums, k);
        cout << "Input    : k=" << k << " → ";
        for (int x : nums) cout << x << " ";
        cout << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({1,1,1,0,0,0,1,1,1,1,0}, 2, 6);
    run({0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, 3, 10);
    run({1,1,1,1},  0, 4);
    run({0,0,0,0},  4, 4);
    run({0,0,0},    0, 0);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : zeros in window = window - count of ones
 *                shrink when zeros > k
 *                same pattern as LC424 (window - maxFreq <= k)
 *
 * Connection   : LC424 → chars to replace = window - maxFreq
 *                LC1004 → zeros to flip   = window - count
 *                identical structure, different variables
 *
 * Mistakes made: added unused freq vector — remove it
 */