/*
 * Problem   : LC567 — Permutation in String
 * Topic     : Strings
 * Pattern   : Sliding Window — Fixed Size + Frequency Map
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/permutation-in-string/
 *
 * Approach  :
 * - window size = s1.size() (fixed)
 * - maintain frequency array of size 26 for s1 and current window
 * - slide window: add right char, remove left char
 * - if freq arrays match → permutation found
 *
 * Optimization (not implemented):
 * - use 'matches' counter instead of comparing full arrays
 * - increment matches when freq[c] becomes equal, decrement when unequal
 * - O(1) per slide instead of O(26)
 *
 * Time      : O(n) — O(26) comparison is O(1)
 * Space     : O(1) — fixed size 26 arrays
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s2.size();
        int k = s1.size();

        if (k > n) return false;

        vector<int> freq1(26, 0);
        vector<int> freq2(26, 0);

        // build frequency of s1 and first window
        for (char c : s1)          freq1[c - 'a']++;
        for (int i = 0; i < k; i++) freq2[s2[i] - 'a']++;

        if (freq1 == freq2) return true;

        // slide window
        for (int i = k; i < n; i++) {
            freq2[s2[i] - 'a']++;        // add incoming
            freq2[s2[i - k] - 'a']--;    // remove outgoing
            if (freq1 == freq2) return true;
        }

        return false;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](string s1, string s2, bool expected) {
        bool res = sol.checkInclusion(s1, s2);
        cout << "s1=" << s1 << " s2=" << s2
             << "\nOutput   : " << (res ? "true" : "false")
             << " | Expected: " << (expected ? "true" : "false")
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    
    run("ab", "eidbaooo", true);


    run("ab", "eidboaoo", false);

   
    run("abcd", "ab", false);

  
    run("abc", "cba", true);

    
    run("a", "b", false);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : permutation = same frequency of characters
 *                fixed window size = s1.length()
 *                freq array comparison instead of sorting
 *
 * Optimization : matches counter — O(1) per slide
 *                when freq2[c] == freq1[c] → matches++
 *                when freq2[c] != freq1[c] → matches--
 *                if matches == 26 → found
 *
 * Edge cases   : s1 longer than s2 → false immediately
 *                single character strings
 *
 * Mistakes made: [fill this yourself]
 */