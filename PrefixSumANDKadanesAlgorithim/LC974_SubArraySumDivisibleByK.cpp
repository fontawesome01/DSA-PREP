/*
 * Problem   : LC974 — Subarray Sums Divisible by K
 * Topic     : Arrays
 * Pattern   : Prefix Sum + HashMap (Modular Arithmetic)
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/subarray-sums-divisible-by-k/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Step 1 — Connect to LC 560
 *   LC 560: prefix[j] - prefix[i] == k         → look up (sum - k)
 *   LC 974: (prefix[j] - prefix[i]) % k == 0   → look up same remainder
 *
 * Step 2 — Key math insight
 *   (prefix[j] - prefix[i]) % k == 0
 *   → prefix[j] % k == prefix[i] % k
 *   → if two prefix sums have SAME remainder, their difference is divisible by k
 *
 * Step 3 — Algorithm
 *   store remainder frequency in hashmap
 *   at each step: count += how many earlier prefixes have same remainder
 *   then: record current remainder
 *
 * Step 4 — Negative remainder trap (C++ specific)
 *   C++: -1 % 5 = -1  (not 4)
 *   Fix: rem = ((current % k) + k) % k
 *   This converts negative remainders to positive equivalents
 *
 * ═══════════════════════════════════════════════════
 *
 * Visual:  nums = [4, 5, 0, -2, -3, 1], k = 5
 *
 *   prefix sums:  0,  4,  9,  9,  7,  4,  5
 *       mod 5:    0,  4,  4,  4,  2,  4,  0
 *
 *   i=0: sum=4  rem=4  map has no 4  → count=0  map={0:1, 4:1}
 *   i=1: sum=9  rem=4  map has 4(1)  → count=1  map={0:1, 4:2}
 *   i=2: sum=9  rem=4  map has 4(2)  → count=3  map={0:1, 4:3}
 *   i=3: sum=7  rem=2  map has no 2  → count=3  map={0:1, 4:3, 2:1}
 *   i=4: sum=4  rem=4  map has 4(3)  → count=6  map={0:1, 4:4, 2:1}
 *   i=5: sum=5  rem=0  map has 0(1)  → count=7  map={0:2, 4:4, 2:1}
 *
 *   Answer = 7 ✅
 *
 * Time  : O(n)
 * Space : O(k) — at most k distinct remainders
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> prefix;
        prefix[0] = 1;           // empty prefix has remainder 0
        int count = 0;
        int current = 0;

        for (int i = 0; i < n; i++) {
            current += nums[i];
            int rem = ((current % k) + k) % k;   // handle negative

            if (prefix.count(rem))
                count += prefix[rem];

            prefix[rem]++;
        }

        return count;
    }
};

int main() {
    Solution sol;

    auto test = [&](vector<int> nums, int k, int expected) {
        int res = sol.subarraysDivByK(nums, k);
        cout << "k=" << k << " Output: " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n";
    };

    test({4, 5, 0, -2, -3, 1}, 5, 7);
    test({5}, 9, 0);
    test({-1, 2, 9}, 2, 2);           // negative remainder test
    test({0, 0, 0}, 1, 6);            // everything divisible by 1

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : same remainder → difference divisible by k
 *                prefix[j] % k == prefix[i] % k
 *                → (prefix[j] - prefix[i]) % k == 0
 *
 * vs LC 560    : LC 560 stores prefix sum, looks up (sum - k)
 *                LC 974 stores prefix % k, looks up same remainder
 *                DON'T mix the two — no subtraction needed here
 *
 * C++ trap     : -1 % 5 = -1 in C++ (not 4)
 *                fix: ((x % k) + k) % k
 *                Python does this automatically, C++ doesn't
 *
 * Space note   : at most k distinct remainders (0 to k-1)
 *                so space is O(min(n, k))
 *
 * Common mistakes:
 *   ❌ Using (currentSum - k) % k — that's LC 560 logic, not this
 *   ❌ Forgetting negative remainder handling
 *   ❌ Computing ((current%k)+k)%k twice instead of reusing rem
 *   ❌ Forgetting prefix[0] = 1
 *
 * Connection   : LC 560 — prefix sum + hashmap (exact sum)
 *                LC 523 — continuous subarray sum (mod k, length ≥ 2)
 *                LC 1590 — make sum divisible by p (same mod idea)
 */