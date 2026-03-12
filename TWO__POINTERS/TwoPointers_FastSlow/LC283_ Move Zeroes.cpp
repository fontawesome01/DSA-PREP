/*
 * Problem   : LC283 — Move Zeroes
 * Topic     : Arrays
 * Pattern   : Same Direction Two Pointers
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/move-zeroes/
 *
 * Approach  :
 * - left  = position where next non-zero should be written
 * - right = scanner moving through array
 * - when nums[right] != 0 → swap with left → move left forward
 * - zeroes naturally bubble to the end via swaps
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        for (int right = 0; right < n; right++) {
            if (nums[right] != 0) {
                swap(nums[left], nums[right]);
                left++;
            }
        }
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> nums, vector<int> expected) {
        vector<int> original = nums;
        sol.moveZeroes(nums);
        cout << "Input    : ";
        for (int x : original) cout << x << " ";
        cout << "\nOutput   : ";
        for (int x : nums) cout << x << " ";
        cout << "\nExpected : ";
        for (int x : expected) cout << x << " ";
        cout << (nums == expected ? " ✅" : " ❌");
        cout << "\n\n";
    };

    // Test 1 — normal case
    run({0, 1, 0, 3, 12}, {1, 3, 12, 0, 0});

    // Test 2 — all zeroes
    run({0, 0, 0}, {0, 0, 0});

    // Test 3 — no zeroes
    run({1, 2, 3}, {1, 2, 3});

    // Test 4 — single element zero
    run({0}, {0});

    // Test 5 — zero at end already
    run({1, 2, 0}, {1, 2, 0});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : left = write pointer for non-zeroes
 *                swap moves non-zero forward, zero backward naturally
 *
 * Edge cases   : all zeroes → no swaps, array unchanged
 *                no zeroes  → every element swaps with itself
 *
 * Mistakes made: "by mistake first i iterate the loop till n-1,but then i realized that i have to
 *                   iterate over all element as we are not checking withh nums[right+1]"
 */