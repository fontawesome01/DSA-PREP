/*
 * Problem   : LC1652 — Defuse the Bomb
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size + Circular Array
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/defuse-the-bomb/
 *
 * ─── Approach 1 — Brute Force ────────────────────────
 * For each index i:
 *   k > 0 → sum next k elements  using (i+j) % n
 *   k < 0 → sum prev |k| elements using (i-j+n) % n
 *   k = 0 → result is 0
 *
 * Time  : O(n * k)
 * Space : O(1)
 *
 * ─── Approach 2 — Sliding Window (Optimal) ──────────
 * Double the array → no circular wrapping needed
 * k > 0 → window starts at index 1     (next k elements of index 0)
 * k < 0 → window starts at index n+k   (prev |k| elements of index 0)
 * Build first window → slide for remaining n-1 positions
 *
 * Circular trick:
 *   % modulo    → for single element access
 *   double array → for sliding window (cleaner)
 *
 * Time  : O(n)
 * Space : O(n) — doubled array
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Approach 1 — Brute Force ────────────────────────
class SolutionBrute {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        vector<int> result(n, 0);

        if (k == 0) return result;

        for (int i = 0; i < n; i++) {
            int sum = 0;
            if (k > 0) {
                for (int j = 1; j <= k; j++)
                    sum += code[(i + j) % n];        // circular next
            } else {
                for (int j = 1; j <= abs(k); j++)
                    sum += code[(i - j + n) % n];    // circular prev
            }
            result[i] = sum;
        }
        return result;
    }
};

// ─── Approach 2 — Sliding Window ─────────────────────
class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        vector<int> result(n, 0);

        if (k == 0) return result;

        // double array → handles circular without %
        vector<int> doubled(code.begin(), code.end());
        doubled.insert(doubled.end(), code.begin(), code.end());

        int start = (k > 0) ? 1 : n + k;  // window start index
        int m     = abs(k);                // window size

        // build first window
        int windowSum = 0;
        for (int i = start; i < start + m; i++)
            windowSum += doubled[i];

        result[0] = windowSum;

        // slide window
        for (int i = 1; i < n; i++) {
            windowSum += doubled[start + i + m - 1];  // add incoming
            windowSum -= doubled[start + i - 1];      // remove outgoing
            result[i] = windowSum;
        }

        return result;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;
    SolutionBrute brute;

    auto run = [&](vector<int> code, int k, vector<int> expected) {
        auto res1 = brute.decrypt(code, k);
        auto res2 = sol.decrypt(code, k);

        cout << "Input    : k=" << k << " → ";
        for (int x : code) cout << x << " ";
        cout << "\nBrute    : ";
        for (int x : res1) cout << x << " ";
        cout << (res1 == expected ? "✅" : "❌");
        cout << "\nOptimal  : ";
        for (int x : res2) cout << x << " ";
        cout << (res2 == expected ? "✅" : "❌");
        cout << "\nExpected : ";
        for (int x : expected) cout << x << " ";
        cout << "\n\n";
    };

    // Test 1 — k positive
    run({5, 7, 1, 4}, 3, {12, 10, 16, 13});

    // Test 2 — k zero
    run({1, 2, 3, 4}, 0, {0, 0, 0, 0});

    // Test 3 — k negative
    run({2, 4, 9, 3}, -2, {12, 5, 6, 13});

    // Test 4 — single element
    run({1}, 1, {1});

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : circular array → two clean ways to handle:
 *                % modulo    → (i+j)%n for single access
 *                double array → append to itself, slide normally
 *
 * Why double?  : window of size k starting at different positions
 *                wraps around → doubling makes it linear → no %
 *
 * Start index  : k>0 → start=1     (next k elements of i=0)
 *                k<0 → start=n+k   (prev |k| elements of i=0)
 *
 * 3 cases      : k=0  → return zeros immediately
 *                k>0  → sum next k (forward)
 *                k<0  → sum prev |k| (backward)
 *
 * Mistakes made: [fill this yourself]
 */