/*
 * Problem   : LC88 — Merge Sorted Array
 * Topic     : Arrays
 * Pattern   : Two Pointers — Fill From Back
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/merge-sorted-array/
 *
 * Approach  :
 * - start from END of both arrays
 * - compare and place larger element at end of nums1
 * - if nums2 has remaining elements → copy them over
 *
 * Time      : O(m+n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;

        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }

        while (j >= 0) nums1[k--] = nums2[j--];
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> n1, int m, vector<int> n2, int n, vector<int> expected) {
        sol.merge(n1, m, n2, n);
        cout << "Output   : ";
        for (int x : n1) cout << x << " ";
        cout << "\nExpected : ";
        for (int x : expected) cout << x << " ";
        cout << (n1 == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({1,2,3,0,0,0}, 3, {2,5,6},  3, {1,2,2,3,5,6});
    run({1},           1, {},        0, {1});
    run({0},           0, {1},       1, {1});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : fill from back → no overwrite of unprocessed elements
 *                remaining nums2 elements → copy directly (nums1 already in place)
 *
 * Edge cases   : m=0 (nums1 empty), n=0 (nums2 empty)
 * Mistakes made: == instead of = assignment bug
 */
