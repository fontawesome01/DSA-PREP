/*
 * Problem   : LC977 — Squares of a Sorted Array
 * Topic     : Arrays
 * Pattern   : Two Pointers — Fill From Back
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/squares-of-a-sorted-array/
 *
 * Approach  :
 * - square all elements first
 * - largest squares are at either end (most negative or most positive)
 * - use two pointers from both ends, fill result from back
 *
 * Time      : O(n)
 * Space     : O(n) — result array
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);

        for (int i = 0; i <= n - 1; i++) nums[i] = nums[i] * nums[i];

        int left = 0, right = n - 1, pos = n - 1;

        while (left <= right) {
            if (nums[left] > nums[right]) {
                result[pos] = nums[left];
                left++;
            } else {
                result[pos] = nums[right];
                right--;
            }
            pos--;
        }
        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> nums, vector<int> expected) {
        auto res = sol.sortedSquares(nums);
        cout << "Output   : ";
        for (int x : res) cout << x << " ";
        cout << "\nExpected : ";
        for (int x : expected) cout << x << " ";
        cout << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({-4,-1,0,3,10}, {0,1,9,16,100});
    run({-7,-3,2,3,11}, {4,9,9,49,121});
    run({-3,-1},        {1,9});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : largest squares always at ends of sorted array
 *                fill result from back with larger square each step
 *
 * Edge cases   : all negative, all positive, single element
 * Mistakes made: compared before squaring — square during comparison step
 */
