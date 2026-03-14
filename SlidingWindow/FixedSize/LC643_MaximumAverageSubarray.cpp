/*
 * Problem   : LC643 — Maximum Average Subarray I
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/maximum-average-subarray-i/
 *
 * Approach  :
 * - build first window of size k → get initial sum
 * - slide window: add nums[i], remove nums[i-k]
 * - track maximum average throughout
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double windowSum = 0;

        // build first window
        for (int i = 0; i < k; i++)
            windowSum += nums[i];

        double maxAvg = windowSum / k;

        // slide window
        for (int i = k; i < n; i++) {
            windowSum += nums[i];
            windowSum -= nums[i - k];
            maxAvg = max(maxAvg, windowSum / k);
        }

        return maxAvg;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int k, double expected) {
        double res = sol.findMaxAverage(nums, k);
        cout << "Input    : k=" << k << " → ";
        for (int x : nums) cout << x << " ";
        cout << fixed << setprecision(5);
        cout << "\nOutput   : " << res
             << " | Expected: " << expected
             << (abs(res - expected) < 1e-5 ? " ✅" : " ❌")
             << "\n\n";
    };

  
    run({1, 12, -5, -6, 50, 3}, 4, 12.75000);


    run({5, 5, 5}, 3, 5.00000);

    
    run({-1, -12, -5, -6}, 2, -6.00000);

  
    run({0, 1, 1, 3, 3}, 1, 3.00000);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : don't recalculate sum from scratch each time
 *                add incoming element, remove outgoing element → O(n)
 *
 * Edge cases   : k == n (only one window)
 *                all negative numbers → still works
 *
 * Mistakes made: 
 */