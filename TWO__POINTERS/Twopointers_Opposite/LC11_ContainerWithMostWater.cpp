/*
 * Problem   : LC11 — Container With Most Water
 * Topic     : Arrays
 * Pattern   : Two Pointers — Opposite Ends
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/container-with-most-water/
 *
 * Approach  :
 * - area = min(height[left], height[right]) * (right - left)
 * - always move the shorter side inward
 * - moving taller side can only decrease width, never increase area
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int maxarea = 0;

        while (left < right) {
            int h    = min(height[left], height[right]);
            int w    = right - left;
            int area = h * w;
            maxarea  = max(maxarea, area);

            if (height[left] > height[right]) right--;
            else                              left++;
        }
        return maxarea;
    }
};

int main() {
    Solution sol;

    auto run = [&](vector<int> h, int expected) {
        int res = sol.maxArea(h);
        cout << "Input    : ";
        for (int x : h) cout << x << " ";
        cout << "\nOutput   : " << res
             << " | Expected: " << expected
             << (res == expected ? " ✅" : " ❌") << "\n\n";
    };

    run({1, 8, 6, 2, 5, 4, 8, 3, 7}, 49);
    run({1, 1},                        1);
    run({4, 3, 2, 1, 4},              16);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : move shorter side — only way to possibly increase area
 *                width decreases every step so height must increase
 *
 * Edge cases   : two elements, all same height
 * Mistakes made: tried sorting array — destroys index = width relationship
 */
