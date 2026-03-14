/*
 * Problem   : LC287 — Find The Duplicate Number
 * Topic     : Arrays
 * Pattern   : Fast-Slow Pointers (Floyd's Cycle Detection)
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/find-the-duplicate-number/
 *
 * Approach  :
 * - treat array indices as a linked list: index → nums[index]
 * - duplicate value = cycle entry point
 * - Phase 1: detect cycle using fast (moves 2) and slow (moves 1)
 * - Phase 2: reset one pointer to nums[0], both move 1 step
 *            where they meet = duplicate number
 *
 * Why do-while:
 * - both slow and fast start at nums[0]
 * - if we use while(slow!=fast) they'd exit immediately
 * - do-while ensures at least one move before checking
 *
 * Time      : O(n)
 * Space     : O(1)


 alternative Solution
 this is also use  : Time      : O(n)
                     Space     : O(1)
  but it modifies the array 

    int findDuplicate(vector<int>& nums) {

        int i = 0;

        while(nums[i] != -1){
            int next = nums[i];   // store next
            nums[i] = -1;         // mark visited
            i = next;
        }

        return i;
    }
*/



#include <bits/stdc++.h>
using namespace std;

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;


        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

      
        int entry = 0;
        while (slow != entry) {
            slow  = nums[slow];
            entry = nums[entry];
        }

        return entry;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> nums, int expected) {
        vector<int> original = nums;
        int ans = sol.findDuplicate(nums);
        cout << "Input    : ";
        for (int x : original) cout << x << " ";
        cout << "\nAnswer   : " << ans
             << " | Expected: " << expected
             << (ans == expected ? " ✅" : " ❌")
             << "\n\n";
    };

    run({4, 1, 2, 3, 3}, 3);
    run({1, 2, 1}, 1);
    run({1, 2, 3, 1}, 1);
    run({1, 1}, 1);
    run({3, 3, 3, 3}, 3);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : array indices behave like linked list next pointers
 *                duplicate = two indices point to same value = cycle entry
 *
 * Why do-while : slow == fast at start (both = nums[0])
 *                regular while would exit immediately
 *                do-while moves first, then checks
 *
 * Edge cases   : duplicate at index 0 side — handled by nums[0] start
 *                duplicate appears 3+ times — Floyd's still works
 *
 * Mistakes made: also check the test cases you chooose 
 *                i intoalize slow = num[0] & fast = nums[0] which causes segemntation fault 
 *                Index 0 is always valid — safe starting point
                  nums[0] as start → immediately jumps to some value
                  → that value used as index → might be huge → segfault
 */