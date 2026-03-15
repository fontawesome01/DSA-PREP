/*
 * Problem   : LC904 — Fruit Into Baskets
 * Topic     : Arrays
 * Pattern   : Sliding Window — Dynamic Size + HashMap
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/fruit-into-baskets/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Reframe: "2 baskets, each holds 1 type" =
 *          "longest subarray with at most 2 distinct values"
 *
 * Step 1 — What makes window VALID?
 *   at most 2 distinct fruit types
 *   track with HashMap: type → count in window
 *   invalid when map.size() > 2
 *
 * Step 2 — Why HashMap not HashSet?
 *   set removes type completely on erase
 *   but type might still exist elsewhere in window
 *   map tracks frequency → only remove type when freq == 0
 *
 * Step 3 — Shrink condition
 *   while map.size() > 2:
 *     freq[left]--
 *     if freq[left] == 0 → erase from map (type gone)
 *     left++
 *
 * ═══════════════════════════════════════════════════
 *
 * Time      : O(n)
 * Space     : O(1) — map has at most 3 entries at any time
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int left = 0;
        int result = 0;
        unordered_map<int, int> type;

        for (int right = 0; right < n; right++) {
            type[fruits[right]]++;

            while (type.size() > 2) {
                type[fruits[left]]--;
                if (type[fruits[left]] == 0)
                    type.erase(fruits[left]);
                left++;
            }

            result = max(result, right - left + 1);
        }

        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> fruits, int expected) {
        int res = sol.totalFruit(fruits);
        cout << "Input    : ";
        for (int x : fruits) cout << x << " ";
        cout << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({1,2,1},       3);
    run({0,1,2,2},     3);
    run({1,2,3,2,2},   4);
    run({3,3,3,1,2,1}, 4);
    run({1,1,1,1},     4);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : 2 baskets = at most 2 distinct values in window
 *                HashMap not HashSet — tracks frequency not just presence
 *                erase type only when freq == 0 (fully left window)
 *
 * General form : "at most k distinct" → same pattern
 *                LC904 is k=2 specific case
 *                LC992 is harder generalization
 *
 * Mistakes made: used unordered_set — erases type even if still in window
 *                fix: unordered_map tracks frequency correctly
 */