/*
 * Problem   : LC1052 — Grumpy Bookstore Owner
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size + Base Count
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/grumpy-bookstore-owner/
 *
 * Approach  :
 * Step 1 — count base satisfied customers (grumpy[i] == 0)
 * Step 2 — sliding window of size 'minutes' to find max EXTRA
 *           customers gained by suppressing grumpy owner
 *           window only adds/removes customers where grumpy[i] == 1
 * Step 3 — answer = base + maxExtra
 *
 * Key insight:
 * - don't think of it as "best window"
 * - think of it as "base + best bonus"
 * - base = always satisfied (grumpy=0)
 * - bonus = extra from suppressing grumpy in best window
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = grumpy.size();

        // step 1 — base: always satisfied customers
        int base = 0;
        for (int i = 0; i < n; i++)
            if (grumpy[i] == 0) base += customers[i];

        // step 2 — window: max extra from suppressing grumpy window
        int windowSum = 0;
        for (int i = 0; i < minutes; i++)
            if (grumpy[i] == 1) windowSum += customers[i];

        int maxExtra = windowSum;

        for (int i = minutes; i < n; i++) {
            if (grumpy[i] == 1)           windowSum += customers[i];
            if (grumpy[i - minutes] == 1) windowSum -= customers[i - minutes];
            maxExtra = max(maxExtra, windowSum);
        }

        // step 3 — answer
        return base + maxExtra;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> customers, vector<int> grumpy,
                   int minutes, int expected) {
        int res = sol.maxSatisfied(customers, grumpy, minutes);
        cout << "Customers: ";
        for (int x : customers) cout << x << " ";
        cout << "\nGrumpy   : ";
        for (int x : grumpy) cout << x << " ";
        cout << "\nMinutes  : " << minutes
             << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    // Test 1 — normal case
    run({1,0,1,2,1,1,7,5}, {0,1,0,1,0,1,0,1}, 3, 16);

    // Test 2 — owner never grumpy
    run({1,2,3}, {0,0,0}, 2, 6);

    // Test 3 — always grumpy
    run({1,2,3}, {1,1,1}, 2, 3);

    // Test 4 — minutes = n (suppress entire time)
    run({4,2,3}, {1,1,1}, 3, 9);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : split into base + bonus thinking
 *                base   = customers where grumpy=0 (always satisfied)
 *                bonus  = extra customers in best suppression window
 *                answer = base + max bonus
 *
 * Window trick : only add/subtract when grumpy==1
 *                grumpy=0 customers already counted in base
 *                counting them again would double-count
 *
 * Edge cases   : all grumpy=0 → bonus=0, answer=sum of all customers
 *                all grumpy=1 → base=0, answer=best window sum
 *                minutes=n   → suppress entire array, answer=total
 *
 * Mistakes made: [fill this yourself]
 */