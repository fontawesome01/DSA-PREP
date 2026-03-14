/*
 * Problem   : LC1423 — Maximum Points You Can Obtain from Cards
 * Topic     : Arrays
 * Pattern   : Sliding Window — Fixed Size (Reverse Thinking)
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/
 *
 * Approach  :
 * - picking k cards from either end = leaving n-k cards in middle
 * - find minimum subarray of size n-k
 * - answer = total sum - min subarray sum
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int total = accumulate(cardPoints.begin(), cardPoints.end(), 0);

        if (n == k) return total;

        int m = n - k;
        int windowSum = 0;

        for (int i = 0; i < m; i++)
            windowSum += cardPoints[i];

        int minWin = windowSum;

        for (int i = m; i < n; i++) {
            windowSum += cardPoints[i];
            windowSum -= cardPoints[i - m];
            minWin = min(minWin, windowSum);
        }

        return total - minWin;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> cards, int k, int expected) {
        int res = sol.maxScore(cards, k);
        cout << "Input    : k=" << k << " → ";
        for (int x : cards) cout << x << " ";
        cout << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({1,2,3,4,5,6,1}, 3, 12);
    run({2,2,2},          2, 4);
    run({9,7,7,9,7,7,9}, 7, 55);
    run({1,1000,1},       1, 1);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : picking k from ends = leaving n-k in middle
 *                max score = total - min(middle window of size n-k)
 *                reverse thinking — find min instead of max
 *
 * Recommendation:
 * - k==1 check unnecessary — general logic handles it
 * - accumulate() is clean STL — good use
 *
 * Mistakes made: [fill this yourself]
 */