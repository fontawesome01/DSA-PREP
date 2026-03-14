/*
 * Problem   : LC438 — Find All Anagrams in a String
 * Topic     : Strings
 * Pattern   : Sliding Window — Fixed Size + Frequency Map
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/find-all-anagrams-in-a-string/
 *
 * Approach  :
 * - window size = p.size() (fixed)
 * - maintain frequency arrays for p and current window
 * - slide window: add right char, remove left char
 * - if freq arrays match → anagram found → push start index (i-k+1)
 *
 * Time      : O(n) — O(26) comparison is O(1)
 * Space     : O(1) — fixed size 26 arrays
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size();
        int k = p.size();

        if (k > n) return {};

        vector<int> freqp(26, 0);
        vector<int> freqs(26, 0);
        vector<int> result;

        // build frequency of p and first window
        for (char c : p)            freqp[c - 'a']++;
        for (int i = 0; i < k; i++) freqs[s[i] - 'a']++;

        if (freqs == freqp) result.push_back(0);

        // slide window
        for (int i = k; i < n; i++) {
            freqs[s[i] - 'a']++;          // add incoming
            freqs[s[i - k] - 'a']--;      // remove outgoing
            if (freqs == freqp)
                result.push_back(i - k + 1);  // start index
        }

        return result;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](string s, string p, vector<int> expected) {
        auto res = sol.findAnagrams(s, p);
        cout << "s=" << s << " p=" << p;
        cout << "\nOutput   : ";
        for (int x : res) cout << x << " ";
        cout << "\nExpected : ";
        for (int x : expected) cout << x << " ";
        cout << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    // Test 1 — multiple anagrams
    run("cbaebabacd", "abc", {0, 6});

    // Test 2 — consecutive anagrams
    run("abab", "ab", {0, 1, 2});

    // Test 3 — no anagram
    run("abcd", "xyz", {});

    // Test 4 — p longer than s
    run("ab", "abc", {});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : anagram = same character frequency
 *                start index = i - k + 1 (not i or i-k)
 *
 * vs LC567     : exact same logic
 *                LC567 → return true on first match
 *                LC438 → collect ALL match indices
 *
 * Optimization : matches counter (same as LC567 optimization)
 *                O(1) per slide instead of O(26)
 *
 * Edge cases   : p longer than s → return empty
 *                no anagram found → return empty
 *
 * Mistakes made: [fill this yourself]
 */