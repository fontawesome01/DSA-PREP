/*
 * Problem   : LC1343 — Number of Subarrays of Size K and
 *             Average Greater than or Equal to Threshold
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/
 *
 * Approach  :
 * - build first window of size k
 * - slide: add right, remove left
 * - instead of dividing: check windowSum >= threshold * k
 *   avoids integer division precision loss
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = arr.size();
        int windowSum = 0;
        int count = 0;
        int target = threshold * k;  // avoid division entirely

        // build first window
        for (int i = 0; i < k; i++)
            windowSum += arr[i];

        if (windowSum >= target) count++;

        // slide window
        for (int i = k; i < n; i++) {
            windowSum += arr[i];
            windowSum -= arr[i - k];
            if (windowSum >= target) count++;
        }

        return count;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> arr, int k, int threshold, int expected) {
        int res = sol.numOfSubarrays(arr, k, threshold);
        cout << "Input    : k=" << k << " threshold=" << threshold << " → ";
        for (int x : arr) cout << x << " ";
        cout << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌")
             << "\n\n";
    };

    // Test 1 — normal case
    run({2, 2, 2, 2, 5, 5, 5, 8}, 3, 4, 3);

    // Test 2 — no valid subarray
    run({1, 1, 1, 1, 1}, 3, 5, 0);

    // Test 3 — all valid
    run({5, 5, 5, 5}, 2, 4, 3);

    // Test 4 — single window
    run({1, 2, 3}, 3, 2, 1);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : avg >= threshold  →  sum >= threshold * k
 *                multiply once, avoid division every iteration
 *
 * Edge cases   : no valid subarray → count stays 0
 *                all windows valid → count = n - k + 1
 *
 * Mistakes made: integer division loses precision — use sum comparison
 *                declared avg variable twice — shadows outer variable
 */