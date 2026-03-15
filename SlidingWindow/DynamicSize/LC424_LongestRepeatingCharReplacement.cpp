/*
 * Problem   : LC424 — Longest Repeating Character Replacement
 * Topic     : Strings
 * Pattern   : Sliding Window — Dynamic Size
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/longest-repeating-character-replacement/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Step 1 — What makes a window VALID?
 *   We want all same characters after at most k replacements
 *   Keep the most frequent char → replace everything else
 *   replacements needed = window size - maxFreq
 *   window is VALID when: window - maxFreq <= k
 *   window is INVALID when: window - maxFreq > k → shrink
 *
 * Step 2 — How to track maxFreq efficiently?
 *   freq[26] array tracks char counts in window
 *   maxFreq = max freq of any char in current window
 *   update maxFreq when expanding (adding s[right])
 *   DO NOT update maxFreq when shrinking — key insight below
 *
 * Step 3 — Why maxFreq never decreases?
 *   We only care about windows LONGER than current best
 *   If maxFreq decreases → window can only stay same or shrink
 *   → can never give longer answer
 *   → so no point recalculating maxFreq downward
 *   maxFreq only ever moves UP across the entire run
 *
 * Step 4 — Standard dynamic window template
 *   expand right → update freq + maxFreq
 *   shrink while invalid (window - maxFreq > k)
 *   update result
 *
 * ═══════════════════════════════════════════════════
 *
 * Time      : O(n)
 * Space     : O(1) — fixed size 26 array
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        vector<int> freq(26, 0);
        int left = 0;
        int result = 0;
        int maxFreq = 0;

        for (int right = 0; right < n; right++) {
            freq[s[right] - 'A']++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);

            while (right - left + 1 - maxFreq > k) {
                freq[s[left] - 'A']--;
                left++;
            }

            result = max(result, right - left + 1);
        }

        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](string s, int k, int expected) {
        int res = sol.characterReplacement(s, k);
        cout << "Input    : s=\"" << s << "\" k=" << k
             << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run("ABAB",    2, 4);
    run("AABABBA", 1, 4);
    run("AAAA",    2, 4);
    run("ABCD",    1, 2);
    run("A",       0, 1);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : valid window = window - maxFreq <= k
 *                keep most frequent char, replace the rest
 *
 * maxFreq trick: never recalculate downward when shrinking
 *                only care about windows longer than current best
 *                if maxFreq drops → window shrinks → not useful
 *                maxFreq only ever increases → O(n) guaranteed
 *
 * Mistakes made: INT_MIN for maxFreq — just use 0
 */