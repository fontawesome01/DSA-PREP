/*
 * Problem   : LC560 — Subarray Sum Equals K
 * Topic     : Arrays
 * Pattern   : Prefix Sum + HashMap
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/subarray-sum-equals-k/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Step 1 — Brute force
 *   check all subarrays → O(n²)
 *   for each (i, j) compute sum, check == k
 *
 * Step 2 — Key insight
 *   subarray sum(i, j) = prefix[j+1] - prefix[i]
 *   we want: prefix[j+1] - prefix[i] == k
 *   rearrange: prefix[i] == prefix[j+1] - k
 *   → at each j, ask: how many earlier prefixes equal (currentSum - k)?
 *
 * Step 3 — HashMap trick
 *   store frequency of every prefix sum seen so far
 *   at each step: count += prefixCount[currentSum - k]
 *   then: prefixCount[currentSum]++
 *
 * Step 4 — Why prefixCount[0] = 1?
 *   if currentSum == k exactly
 *   → currentSum - k = 0
 *   → need 0 in map with count 1
 *   → represents empty prefix (subarray from index 0)
 *
 * Step 5 — Why check BEFORE insert?
 *   if we insert first, currentSum - k might match itself
 *   → would count a zero-length subarray (invalid)
 *
 * ═══════════════════════════════════════════════════
 *
 * Visual:  nums = [1, 2, 3], k = 3
 *
 *   init:  prefixCount = {0: 1}, sum = 0, count = 0
 *
 *   i=0: sum=1  check: 1-3=-2 not in map  → count=0  insert {0:1, 1:1}
 *   i=1: sum=3  check: 3-3=0  in map(1)   → count=1  insert {0:1, 1:1, 3:1}
 *   i=2: sum=6  check: 6-3=3  in map(1)   → count=2  insert {0:1, 1:1, 3:1, 6:1}
 *
 *   Answer = 2 → subarrays [1,2] and [3]
 *
 * Time  : O(n)
 * Space : O(n) — hashmap stores at most n+1 prefix sums
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> prefixCount;
        prefixCount[0] = 1;       // empty prefix
        int currentSum = 0;
        int count = 0;

        for (int i = 0; i < n; i++) {
            currentSum += nums[i];

         
            if (prefixCount.count(currentSum - k)) {
                count += prefixCount[currentSum - k];
            }

           
            prefixCount[currentSum]++;
        }

        return count;
    }
};

int main() {
    Solution sol;

    auto test = [&](vector<int> nums, int k, int expected) {
        int res = sol.subarraySum(nums, k);
        cout << "k=" << k << " Output: " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n";
    };

    test({1, 1, 1}, 2, 2);            // [1,1] at index 0-1 and 1-2
    test({1, 2, 3}, 3, 2);            // [1,2] and [3]
    test({1}, 0, 0);                   // no subarray sums to 0
    test({0, 0, 0}, 0, 6);            // all subarrays sum to 0
    test({-1, -1, 1}, 0, 1);          // [-1, -1, 1] negatives work

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : prefix[j] - prefix[i] == k
 *                → look up (currentSum - k) in hashmap
 *
 * prefixCount[0] = 1 : handles subarray starting from index 0
 *                       without it, miss cases where currentSum == k exactly
 *
 * Order matters : check THEN insert
 *                 inserting first → might count zero-length subarray
 *
 * Why not sliding window?
 *   array has NEGATIVE numbers
 *   → expanding window can decrease sum
 *   → shrinking can increase sum
 *   → sliding window monotonicity breaks
 *   → must use prefix sum + hashmap
 *
 * Common mistakes:
 *   ❌ Forgetting prefixCount[0] = 1
 *   ❌ Inserting before checking
 *   ❌ Using sliding window (fails with negatives)
 *   ❌ Using int for nums.size() comparison (unsigned mismatch)
 *
 * Connection   : LC974 — same pattern but with modular arithmetic
 *                LC523 — continuous subarray sum (mod k)
 *                LC862 — shortest subarray sum ≥ k (deque)
 *                LC1 — Two Sum is same idea (find complement in map)
 */