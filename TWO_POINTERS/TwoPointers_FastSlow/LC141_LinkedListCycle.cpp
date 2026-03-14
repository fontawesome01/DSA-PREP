/*
 * Problem   : LC141 — Linked List Cycle
 * Topic     : Linked List
 * Pattern   : Fast-Slow Pointers (Floyd's Cycle Detection)
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/linked-list-cycle/
 *
 * Approach  :
 * - slow moves 1 step, fast moves 2 steps
 * - if they ever meet → cycle exists
 * - if fast hits null → no cycle
 *
 * Time      : O(n)
 * Space     : O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// ─── Node ────────────────────────────────────────────
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }

        return false;
    }
}; 

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    // Test 1 — cycle exists: 3→2→0→-4→back to 2
    ListNode* n1 = new ListNode(3);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(0);
    ListNode* n4 = new ListNode(-4);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n2;   // cycle here
    cout << "Test 1 (cycle)    : " << (sol.hasCycle(n1) ? "true" : "false")
         << " | Expected: true  " << (sol.hasCycle(n1) ? "✅" : "❌") << "\n";

    // Test 2 — no cycle: 1→2
    ListNode* m1 = new ListNode(1);
    ListNode* m2 = new ListNode(2);
    m1->next = m2;
    cout << "Test 2 (no cycle) : " << (sol.hasCycle(m1) ? "true" : "false")
         << " | Expected: false " << (!sol.hasCycle(m1) ? "✅" : "❌") << "\n";

    // Test 3 — single node, no cycle
    ListNode* s1 = new ListNode(1);
    cout << "Test 3 (single)   : " << (sol.hasCycle(s1) ? "true" : "false")
         << " | Expected: false " << (!sol.hasCycle(s1) ? "✅" : "❌") << "\n";

    // Test 4 — single node with self cycle
    ListNode* s2 = new ListNode(1);
    s2->next = s2;
    cout << "Test 4 (self loop): " << (sol.hasCycle(s2) ? "true" : "false")
         << " | Expected: true  " << (sol.hasCycle(s2) ? "✅" : "❌") << "\n";

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : two runners on a circular track always meet
 *                fast gains 1 step per iteration on slow
 *
 * Edge cases   : empty list    → fast=null → return false
 *                single node   → fast->next=null → return false
 *                self loop     → fast==slow on first iteration
 *
 * Mistakes made: as i learned this concept earlier also so nno mistake in it while building 
 */