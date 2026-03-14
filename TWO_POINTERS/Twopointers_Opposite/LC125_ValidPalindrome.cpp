/*
 * Problem   : LC125 — Valid Palindrome
 * Topic     : Arrays / Strings
 * Pattern   : Two Pointers — Opposite Ends
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/valid-palindrome/
 *
 * Approach  :
 * - skip non-alphanumeric characters from both ends
 * - compare lowercase of both characters
 * - if mismatch → not palindrome
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            while (left < right && !isalnum(s[left]))  left++;
            while (left < right && !isalnum(s[right])) right--;

            if (tolower(s[left]) != tolower(s[right])) return false;

            left++;
            right--;
        }
        return true;
    }
};

int main() {
    Solution sol;

    auto run = [&](string s, bool expected) {
        bool res = sol.isPalindrome(s);
        cout << "Input    : \"" << s << "\""
             << "\nOutput   : " << (res ? "true" : "false")
             << " | Expected: " << (expected ? "true" : "false")
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run("A man, a plan, a canal: Panama", true);
    run("race a car",                     false);
    run(" ",                              true);
    run("Was it a car or a cat I saw?",   true);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : skip non-alphanumeric first, then compare
 *                isalnum() handles both letters and digits
 *                tolower() handles case insensitive compare
 *
 * Edge cases   : empty string, only spaces, all special chars
 * Mistakes made: [fill this yourself]
 */
