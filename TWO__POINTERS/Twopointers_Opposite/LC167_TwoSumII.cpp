/*
 * Problem   : LC167 — Two Sum II
 * Topic     : Arrays
 * Pattern   : Two Pointers — Opposite Ends
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * Approach  :
 * - array is sorted → use opposite end pointers
 * - sum too big  → move right left
 * - sum too small → move left right
 * - sum == target → found answer
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        vector<int> result;

        while (left < right) {
            if (numbers[left] + numbers[right] == target) {
                result.push_back(left + 1);
                result.push_back(right + 1);
                return result;
            }
            if (numbers[left] + numbers[right] > target)
                right--;
            else
                left++;
        }
        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int target, vector<int> expected) {
        vector<int> res = sol.twoSum(nums, target);
        cout << "Input    : target=" << target << " → ";
        for (int x : nums) cout << x << " ";
        cout << "\nOutput   : [" << res[0] << "," << res[1] << "]"
             << " | Expected: [" << expected[0] << "," << expected[1] << "]"
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({2, 7, 11, 15}, 9,  {1, 2});
    run({2, 3, 4},      6,  {1, 3});
    run({-1, 0},        -1, {1, 2});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : sorted array → opposite pointers work
 *                sum > target → right-- (reduce sum)
 *                sum < target → left++  (increase sum)
 *
 * Edge cases   : negative numbers, target = 0
 * Mistakes made: forgot return result after pushing — caused wrong output
 */
