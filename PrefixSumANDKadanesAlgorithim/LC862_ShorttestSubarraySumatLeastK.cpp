/*
 * Problem   : LC862 — Shortest Subarray with Sum at Least K
 * Topic     : Arrays
 * Pattern   : Prefix Sum + Monotonic Deque
 * Difficulty: Hard
 * Link      : https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Step 1 — Why not sliding window?
 *   array has NEGATIVE numbers
 *   → expanding window can decrease sum
 *   → shrinking can increase sum
 *   → sliding window monotonicity breaks
 *
 * Step 2 — Reframe with prefix sums
 *   sum(i, j) = prefix[j] - prefix[i]
 *   we want: prefix[j] - prefix[i] >= k
 *   find shortest (j - i)
 *
 * Step 3 — What makes a good starting point i?
 *   we want prefix[i] as SMALL as possible
 *   → bigger difference prefix[j] - prefix[i]
 *   → if prefix[i1] >= prefix[i2] and i1 < i2
 *   → i1 is useless: i2 gives same or better difference AND shorter subarray
 *   → remove i1 from back of deque
 *
 * Step 4 — When is a starting point used up?
 *   if prefix[j] - prefix[i] >= k → valid answer found
 *   any later j' > j would give j' - i > j - i → longer subarray
 *   → i is used up, pop from front
 *
 * Step 5 — Deque maintains increasing order of prefix sums
 *   front removal → found valid answer, consume it
 *   back removal  → remove useless larger prefix sums
 *
 * ═══════════════════════════════════════════════════
 *
 * Visual:  nums = [2, -1, 2], k = 3
 *
 *   prefix = [0, 2, 1, 3]
 *
 *   j=0: prefix=0  dq=[]       → push 0       dq=[0]
 *   j=1: prefix=2  check front: 2-0=2 < 3     → no pop
 *                   check back:  0 < 2         → no pop
 *                   push 1                      dq=[0,1]
 *   j=2: prefix=1  check front: 1-0=1 < 3     → no pop
 *                   check back:  prefix[1]=2 >= 1 → pop 1
 *                   check back:  prefix[0]=0 < 1  → stop
 *                   push 2                      dq=[0,2]
 *   j=3: prefix=3  check front: 3-0=3 >= 3    → ans=3, pop 0
 *                   check front: 3-1=2 < 3     → stop
 *                   check back:  prefix[2]=1 < 3 → stop
 *                   push 3                      dq=[2,3]
 *
 *   Answer = 3 ✅ (entire array)
 *
 * Time  : O(n) — each index pushed and popped at most once
 * Space : O(n) — prefix array + deque
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }

        deque<int> dq;
        int ans = n + 1;

        for (int i = 0; i <= n; i++) {
            // front: consume valid answers (shortest first)
            while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
                ans = min(ans, i - dq.front());
                dq.pop_front();
            }

            // back: remove useless larger prefix sums
            while (!dq.empty() && prefix[dq.back()] >= prefix[i]) {
                dq.pop_back();
            }

            dq.push_back(i);
        }

        return ans == n + 1 ? -1 : ans;
    }
};

int main() {
    Solution sol;

    auto test = [&](vector<int> nums, int k, int expected) {
        int res = sol.shortestSubarray(nums, k);
        cout << "k=" << k << " Output: " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n";
    };

    test({1}, 1, 1);
    test({1, 2}, 4, -1);               // no subarray sums to 4
    test({2, -1, 2}, 3, 3);            // entire array
    test({84, -37, 32, 40, 95}, 167, 3); // [32, 40, 95]
    test({-28, 81, -20, 28, -29}, 89, -1);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : monotonic deque on prefix sums (increasing order)
 *                front pop → consume valid answer
 *                back pop  → remove useless starting points
 *
 * vs LC 239    : LC 239 — deque tracks max in fixed window (decreasing deque)
 *                LC 862 — deque tracks best starting point (increasing deque)
 *                same tool, different purpose
 *
 * Why long long: values up to 10^5 elements × 10^5 each = 10^10
 *                overflows int (max ~2.1 × 10^9)
 *
 * Why ans = n+1: max possible subarray length is n
 *                n+1 means "no valid answer found"
 *                cleaner than INT_MAX for length comparison
 *
 * Why each index O(1) amortized:
 *   every index enters deque once, leaves once
 *   total operations = 2n → O(n)
 *
 * Common mistakes:
 *   ❌ Using sliding window (fails with negatives)
 *   ❌ Using int for prefix sums (overflow)
 *   ❌ Confusing k as window size vs target sum
 *   ❌ Not popping front after finding valid answer
 *   ❌ Applying LC 239 template directly (different problem)
 *
 * Connection   : LC 239 — monotonic deque (max in window)
 *                LC 209 — shortest subarray sum >= k (positive only, use sliding window)
 *                LC 560 — subarray sum equals k (hashmap)
 *                LC 974 — subarray sum divisible by k (hashmap + mod)
 */