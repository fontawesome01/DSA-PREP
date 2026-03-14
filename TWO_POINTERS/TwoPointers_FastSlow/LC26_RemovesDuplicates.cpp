/*
 * Problem   : LC26 — Remove Duplicates from Sorted Array
 * Topic     : Arrays
 * Pattern   : Same Direction Two Pointers
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 *
 * Approach  :
 * - slow = last position where unique element was written
 * - fast = scanner moving through array
 * - if nums[fast] != nums[slow] → new unique value → write at ++slow
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// ───Solution ───────────────────────────────────
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0;
        int n = nums.size();
        if(n==1)
        return 1;
        for (int fast = 1; fast < n; fast++) {
            if (nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            }
        }
        return slow + 1;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int expected) {
        vector<int> original = nums;
        int len = sol.removeDuplicates(nums);
        cout << "Input  : ";
        for (int x : original) cout << x << " ";
        cout << "\nOutput : ";
        for (int i = 0; i < len; i++) cout << nums[i] << " ";
        cout << "\nLength : " << len
             << " | Expected: " << expected
             << (len == expected ? " ✅" : " ❌")
             << "\n\n";
    };

    // Test 1 — normal case with duplicates
    run({1, 1, 2, 3, 3}, 3);           // expected: 3 → [1,2,3]

    // Test 2 — all duplicates
    run({1, 1, 1, 1}, 1);              // expected: 1 → [1]

    // Test 3 — no duplicates
    run({1, 2, 3, 4, 5}, 5);           // expected: 5 → [1,2,3,4,5]

    // Test 4 — single element
    run({1}, 1);                        // expected: 1 → [1]

    // Test 5 — two same elements
    run({1, 1}, 1);                     // expected: 1 → [1]

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : slow tracks last written unique position
 *                fast scans — only writes when new value found
 *
 * Cleaner way  : compare nums[fast] with nums[slow] not nums[fast-1]
 *                fast++ once at end of loop not in both branches
 *
 * Edge cases   : single element → return 1 directly
 *                all duplicates → slow stays at 0 → return 1
 *
 * Mistakes made: here i use condn  nums[fast]!=nums[fast-1]
 */