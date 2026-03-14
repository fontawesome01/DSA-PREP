/*
 * Problem   : LC18 — 4Sum
 * Topic     : Arrays
 * Pattern   : Two Pointers — Opposite Ends + Sort
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/4sum/
 *
 * Approach  :
 * - sort array first
 * - fix i and j, use two pointers left=j+1, right=n-1
 * - skip duplicates for i (i>0) and j (j>i+1)
 * - use long long to avoid integer overflow
 *
 * Time      : O(n³)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int left  = j + 1;
                int right = n - 1;

                while (left < right) {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];

                    if (sum == (long long)target) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        left++;
                        right--;
                        while (left < right && nums[left]  == nums[left - 1])  left++;
                        while (left < right && nums[right] == nums[right + 1]) right--;
                    }
                    else if (sum < target) left++;
                    else                   right--;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int target) {
        cout << "Input  : target=" << target << " → ";
        for (int x : nums) cout << x << " ";
        cout << "\nOutput : ";
        auto res = sol.fourSum(nums, target);
        for (auto& v : res)
            cout << "[" << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "] ";
        cout << "\n\n";
    };

    run({1, 0, -1, 0, -2, 2}, 0);   // [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
    run({2, 2, 2, 2, 2},      8);   // [[2,2,2,2]]
    run({1000000000,1000000000,1000000000,1000000000}, 0); // [] — overflow test

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : extend 3Sum by adding one more fixed pointer
 *                j duplicate skip: j>i+1 not j>0
 *                long long cast on FIRST operand to avoid overflow
 *
 * Edge cases   : large values → integer overflow → use long long
 * Mistakes made: j>0 instead of j>i+1 for duplicate skip
 *                forgot long long → overflow on large inputs
 */
