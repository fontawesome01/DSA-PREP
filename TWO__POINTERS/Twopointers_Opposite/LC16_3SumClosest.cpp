/*
 * Problem   : LC16 — 3Sum Closest
 * Topic     : Arrays
 * Pattern   : Two Pointers — Opposite Ends + Sort
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/3sum-closest/
 *
 * Approach  :
 * - sort array first
 * - fix i, use two pointers left=i+1, right=n-1
 * - track minimum difference and corresponding sum
 * - if exact match found → return immediately
 *
 * Time      : O(n²)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n       = nums.size();
        int mindiff = INT_MAX;
        int result  = 0;

        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left  = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum  = nums[i] + nums[left] + nums[right];
                int diff = abs(sum - target);

                if (diff < mindiff) {
                    mindiff = diff;
                    result  = sum;
                }

                if (sum == target) return sum;
                else if (sum < target) left++;
                else                   right--;
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int target, int expected) {
        int res = sol.threeSumClosest(nums, target);
        cout << "Input    : target=" << target << " → ";
        for (int x : nums) cout << x << " ";
        cout << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({-1, 2, 1, -4}, 1,  2);
    run({0, 0, 0},      1,  0);
    run({1, 1, 1, 1},   4, 3);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : track mindiff and result separately
 *                exact match → return immediately (diff=0)
 *
 * Edge cases   : all same elements, target very large/small
 * Mistakes made: [fill this yourself]
 */
