/*
 * Problem   : LC2090 — K Radius Subarray Averages
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/k-radius-subarray-averages/
 *
 * Approach  :
 * - window size = 2*k+1 (k left + center + k right)
 * - only indices k to n-k-1 have valid k-radius averages
 * - all other indices stay -1
 * - first window centered at index k
 * - slide: add nums[i+k], remove nums[i-k-1]
 *
 * Key insight:
 * - use long long — sum of large array can overflow int
 * - n <= 2*k means no valid averages exist → return all -1
 *
 * Time      : O(n)
 * Space     : O(1) — result array doesn't count
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> result(n, -1);

        if (k == 0) return nums;
        if (n <= 2 * k) return result;  // no valid averages

        long long sum = 0;
        int windowSize = 2 * k + 1;

        // build first window
        for (int i = 0; i < windowSize; i++)
            sum += nums[i];

        result[k] = sum / windowSize;

        // slide window — center moves from k+1 to n-k-1
        for (int i = k + 1; i < n - k; i++) {
            sum += nums[i + k];      // add right boundary
            sum -= nums[i - k - 1]; // remove left boundary
            result[i] = sum / windowSize;
        }

        return result;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int k, vector<int> expected) {
        auto res = sol.getAverages(nums, k);
        cout << "Input    : k=" << k << " → ";
        for (int x : nums) cout << x << " ";
        cout << "\nOutput   : ";
        for (int x : res) cout << x << " ";
        cout << "\nExpected : ";
        for (int x : expected) cout << x << " ";
        cout << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    // Test 1 — normal case
    run({7,4,3,9,1,8,5,2,6}, 3, {-1,-1,-1,5,4,4,-1,-1,-1});

    // Test 2 — k=0 returns nums itself
    run({1,2,3}, 0, {1,2,3});

    // Test 3 — n too small for k
    run({1,2}, 3, {-1,-1});

    // Test 4 — single valid average
    run({1,2,3,4,5}, 2, {-1,-1,3,-1,-1});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : window size = 2*k+1 (not k)
 *                center of window = current index i
 *                valid range = index k to n-k-1
 *
 * Why long long : nums[i] up to 10^5, n up to 10^5
 *                 max sum = 10^5 * 10^5 = 10^10 → overflows int
 *
 * Slide formula : add nums[i+k]     ← new right boundary
 *                 remove nums[i-k-1] ← old left boundary
 *
 * Edge cases   : k=0 → return nums directly
 *                n <= 2*k → no valid center exists → all -1
 *
 * Mistakes made: avg stored as int instead of long long — precision loss
 */