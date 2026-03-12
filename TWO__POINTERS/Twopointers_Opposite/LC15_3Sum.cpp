/*
 * Problem   : LC15 — 3Sum
 * Topic     : Arrays
 * Pattern   : Two Pointers — Opposite Ends + Sort
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/3sum/
 *
 * Approach  :
 * - sort array first
 * - fix i, use two pointers left=i+1, right=n-1
 * - skip duplicates for i (compare with i-1)
 * - skip duplicates for left and right after finding triplet
 *
 * Time      : O(n²)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (int i = 0; i < (int)nums.size() - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left  = i + 1;
            int right = nums.size() - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;
                    while (left < right && nums[left]  == nums[left - 1])  left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
                else if (sum < 0) left++;
                else              right--;
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> nums) {
        cout << "Input  : ";
        for (int x : nums) cout << x << " ";
        cout << "\nOutput : ";
        auto res = sol.threeSum(nums);
        for (auto& v : res) {
            cout << "[" << v[0] << "," << v[1] << "," << v[2] << "] ";
        }
        cout << "\n\n";
    };

    run({-1, 0, 1, 2, -1, -4});   // [[-1,-1,2],[-1,0,1]]
    run({0, 1, 1});                // []
    run({0, 0, 0});                // [[0,0,0]]

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : sort first → enables two pointer + easy dedup
 *                skip duplicates BEHIND (i-1, left-1, right+1)
 *
 * Edge cases   : all zeros, no valid triplet, all negative
 * Mistakes made: duplicate skip direction wrong — used left+1 instead of left-1
 *                j boundary was 0 instead of i+1
 */
