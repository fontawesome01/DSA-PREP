/*
 * Problem   : LC76 — Minimum Window Substring
 * Topic     : Strings
 * Pattern   : Sliding Window — Dynamic Size (Shortest Valid Window)
 * Difficulty: Hard
 * Link      : https://leetcode.com/problems/minimum-window-substring/
 *
 * ═══════════════════════════════════════════════════
 * HOW TO THINK OF THIS PROBLEM
 * ═══════════════════════════════════════════════════
 *
 * Step 1 — Understand what valid means
 *   window must contain ALL chars of t (with correct frequency)
 *   find the SHORTEST such window
 *
 * Step 2 — This is Type 2 dynamic window (shortest)
 *   Type 1 (longest): expand as much as possible
 *   Type 2 (shortest): expand until valid → then shrink as much as possible
 *   → record answer while shrinking → smallest valid window
 *
 * Step 3 — How to check if window contains all of t?
 *   Approach A: scan both maps every check → O(t) per step → O(n*t) total
 *   Approach B: have/need counters → O(1) per step → O(n) total
 *
 * Step 4 — have/need counter trick
 *   need = number of unique chars in t that must be satisfied
 *   have = number of unique chars currently satisfied in window
 *   char c is "satisfied" when freqs[c] >= freqt[c]
 *
 *   when adding s[right]:
 *     freqs[s[right]]++
 *     if freqs[s[right]] == freqt[s[right]] → have++
 *
 *   when removing s[left]:
 *     if freqs[s[left]] == freqt[s[left]] → have-- (just became unsatisfied)
 *     freqs[s[left]]--
 *
 *   window is valid when have == need
 *
 * Step 5 — Shrink while valid
 *   while have == need:
 *     update minimum window
 *     remove s[left], left++
 *     update have if char becomes unsatisfied
 *
 * ═══════════════════════════════════════════════════
 *
 * Time      : O(n + m) — n = s.size(), m = t.size()
 * Space     : O(m) — frequency maps
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Approach 1 — Your Solution (containsMap) ────────
// O(n * t) — correct but slower
class SolutionBrute {
    bool containsMap(unordered_map<char,int>& A,
                     unordered_map<char,int>& B) {
        for (auto& p : B) {
            if (A.count(p.first) == 0 || A[p.first] < p.second)
                return false;
        }
        return true;
    }

public:
    string minWindow(string s, string t) {
        if (t == "") return "";
        int n = s.size();
        int left = 0;
        int result = INT_MAX;
        int l = 0, r = 0;
        unordered_map<char,int> freqt, freqs;

        for (char c : t) freqt[c]++;

        for (int right = 0; right < n; right++) {
            freqs[s[right]]++;

            while (containsMap(freqs, freqt)) {
                if (result > right - left + 1) {
                    result = right - left + 1;
                    l = left;
                    r = right;
                }
                freqs[s[left]]--;
                left++;
            }
        }

        return result == INT_MAX ? "" : s.substr(l, result);
    }
};

// ─── Approach 2 — Optimal (have/need counter) ────────
// O(n + m) — O(1) per step
class Solution {
public:
    string minWindow(string s, string t) {
        if (t == "") return "";
        int n = s.size();
        int left = 0;
        int result = INT_MAX;
        int resL = 0;
        int have = 0;
        int need = 0;
        unordered_map<char,int> freqt, freqs;

        for (char c : t) freqt[c]++;
        need = freqt.size();   // unique chars to satisfy

        for (int right = 0; right < n; right++) {
            freqs[s[right]]++;
            if (freqt.count(s[right]) &&
                freqs[s[right]] == freqt[s[right]])
                have++;        // this char is now satisfied

            while (have == need) {
                if (right - left + 1 < result) {
                    result = right - left + 1;
                    resL = left;
                }
                if (freqt.count(s[left]) &&
                    freqs[s[left]] == freqt[s[left]])
                    have--;    // removing this will unsatisfy it
                freqs[s[left]]--;
                left++;
            }
        }

        return result == INT_MAX ? "" : s.substr(resL, result);
    }
};

int main() {
    Solution sol;

    auto run = [&](string s, string t, string expected) {
        string res = sol.minWindow(s, t);
        cout << "s=\"" << s << "\" t=\"" << t << "\""
             << "\nOutput   : \"" << res << "\""
             << " | Expected: \"" << expected << "\""
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run("ADOBECODEBANC", "ABC", "BANC");
    run("a",             "a",   "a");
    run("a",             "aa",  "");
    run("aa",            "aa",  "aa");
    run("cabwefgewcwaefgcf", "cae", "cwae");

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : have/need counters → O(1) validity check per step
 *                have == need → window contains all of t
 *
 * have/need    : need = unique chars in t
 *                have++ when freqs[c] reaches freqt[c] exactly
 *                have-- when freqs[c] drops below freqt[c] on shrink
 *
 * Type 2 window: expand until valid → shrink while valid
 *                record minimum inside the shrink loop
 *
 * Mistakes made: containsMap() scans entire map → O(n*t)
 *                unused l=0, r=0 declared at top then redeclared inside
 *                fix: have/need counter → O(1) per step
 */