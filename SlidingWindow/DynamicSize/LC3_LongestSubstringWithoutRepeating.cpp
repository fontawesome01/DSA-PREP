/*
 * Problem   : LC3 — Longest Substring Without Repeating Characters
 * Topic     : Strings
 * Pattern   : Sliding Window — Dynamic Size
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *
 * Approach  :
 * - expand right — add s[right] to window
 * - shrink left while duplicate exists in window
 * - result = max window size seen
 *
 * Time      : O(n)
 * Space     : O(min(n,m)) — m = charset size
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int left = 0;
        int result = 0;
        unordered_set<char> seen;

        for (int right = 0; right < n; right++) {
            while (seen.count(s[right])) {
                seen.erase(s[left]);
                left++;
            }
            seen.insert(s[right]);
            result = max(result, right - left + 1);
        }

        return result;
    }
};

int main() {
    Solution sol;

    auto run = [&](string s, int expected) {
        int res = sol.lengthOfLongestSubstring(s);
        cout << "Input    : \"" << s << "\""
             << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run("abcabcbb", 3);
    run("bbbbb",    1);
    run("pwwkew",   3);
    run("",         0);
    run("au",       2);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : hashset tracks chars in current window
 *                shrink left until duplicate removed
 *                each char inserted once + removed once = O(n)
 *
 * Optimization : HashMap version — jump left directly
 *                left = max(left, lastSeen[s[right]] + 1)
 *                avoids while loop entirely
 *
 * First attempt: used isduplicate() scanning whole window → O(n²)
 *                used string window with erase() → O(n) per op
 *                fix: use hashset directly in main loop → O(1)
 *
 * Mistakes made: [fill this yourself]
 */