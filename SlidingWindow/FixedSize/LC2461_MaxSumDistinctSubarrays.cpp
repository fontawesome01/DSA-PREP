/*
 * Problem   : LC2461 — Maximum Sum of Distinct Subarrays With Length K
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size + HashMap
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/
 *
 * Approach  :
 * - maintain frequency map of current window
 * - track distinctCount — elements with freq exactly 1
 * - adding element   : freq++ → if freq==1 count++, if freq==2 count--
 * - removing element : freq-- → if freq==1 count++, if freq==0 count--
 * - window is valid when distinctCount == k
 *
 * Time      : O(n)
 * Space     : O(k) — at most k elements in frequency map
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> freq;
        long long windowSum = 0;
        long long maxSum = 0;
        int distinctCount = 0;

        for (int i = 0; i < k; i++) {
            windowSum += nums[i];
            freq[nums[i]]++;
            if (freq[nums[i]] == 1) distinctCount++;
            if (freq[nums[i]] == 2) distinctCount--;
        }

        if (distinctCount == k) maxSum = windowSum;

        for (int i = k; i < n; i++) {
            int in  = nums[i];
            int out = nums[i - k];

            freq[in]++;
            windowSum += in;
            if (freq[in] == 1) distinctCount++;
            if (freq[in] == 2) distinctCount--;

            freq[out]--;
            windowSum -= out;
            if (freq[out] == 1) distinctCount++;
            if (freq[out] == 0) distinctCount--;

            if (distinctCount == k) maxSum = max(maxSum, windowSum);
        }

        return maxSum;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int k, long long expected) {
        long long res = sol.maximumSubarraySum(nums, k);
        cout << "Input    : k=" << k << " → ";
        for (int x : nums) cout << x << " ";
        cout << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({1,5,4,2,9,9,3}, 3, 15);
    run({4,4,4},          3, 0);
    run({1,2,3,4,5},      3, 12);
    run({1,1,1,7,8,9},    3, 24);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : don't scan window for distinctness → O(n*k)
 *                track distinctCount with freq map → O(n)
 *
 * The 4 rules  :
 *   add in    → freq==1 → count++  (new unique)
 *   add in    → freq==2 → count--  (became duplicate)
 *   remove out → freq==1 → count++ (back to unique)
 *   remove out → freq==0 → count-- (fully gone)
 *
 * Recommendation:
 *   group all freq + distinctCount ops together before windowSum update
 *   makes code easier to read and debug
 *
 * Mistakes made: [fill this yourself]
 */