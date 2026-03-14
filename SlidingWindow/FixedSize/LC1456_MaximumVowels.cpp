/*
 * Problem   : LC1456 — Maximum Number of Vowels in a Substring
 *             of Given Length
 * Topic     : Strings
 * Pattern   : Sliding Window — Fixed Size
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/
 *
 * Approach  :
 * - build first window of size k → count vowels
 * - slide: if incoming is vowel → count++
 *          if outgoing is vowel → count--
 * - track maximum vowel count
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    int maxVowels(string s, int k) {
        int n = s.size();
        if (n < k) return 0;

        // helper lambda — avoids repeating 5 comparisons
        auto isVowel = [](char c) {
            return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
        };

        int vowelCount = 0;

        // build first window
        for (int i = 0; i < k; i++)
            if (isVowel(s[i])) vowelCount++;

        int maxVowel = vowelCount;

        // slide window
        for (int i = k; i < n; i++) {
            if (isVowel(s[i]))     vowelCount++;   // add incoming
            if (isVowel(s[i - k])) vowelCount--;   // remove outgoing
            maxVowel = max(maxVowel, vowelCount);   // always update
        }

        return maxVowel;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](string s, int k, int expected) {
        int res = sol.maxVowels(s, k);
        cout << "Input    : s=\"" << s << "\" k=" << k
             << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    // Test 1 — normal case
    run("abciiidef", 3, 3);

    // Test 2 — no vowels in best window
    run("aeiou", 2, 2);

    // Test 3 — all consonants
    run("bcd", 2, 0);

    // Test 4 — k equals string size
    run("leetcode", 3, 2);

    // Test 5 — single char
    run("a", 1, 1);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : just track vowel count in window
 *                add if incoming is vowel
 *                subtract if outgoing is vowel
 *
 * Bug fixed    : maxVowel update was inside if block due to missing {}
 *                must always run OUTSIDE the if
 *
 * Clean trick  : lambda isVowel() → avoids repeating 5 comparisons
 *
 * Edge cases   : all consonants → return 0
 *                k == n → single window
 *
 * Mistakes made: maxvowel = max() was inside if block — missing braces
 *                INT_MIN initialization unnecessary
 *                repeated vowel check 3 times instead of helper
 */