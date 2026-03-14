/*
 * Problem   : LC142 — Linked List Cycle II
 * Topic     : Linked List
 * Pattern   : Fast-Slow Pointers (Floyd's Cycle Detection)
 * Difficulty: Medium
 * Link      : https://leetcode.com/problems/linked-list-cycle-ii/
 *
 * Approach  :
 * Phase 1 — Detect cycle
 * - slow moves 1 step, fast moves 2 steps
 * - if they meet → cycle exists, break
 *
 * Phase 2 — Find entry point
 * - reset one pointer to head
 * - both move 1 step at a time
 * - where they meet = cycle entry node
 *
 * Math proof:
 * - F = distance from head to cycle entry
 * - C = cycle length, a = distance from entry to meeting point
 * - when slow & fast meet: F = C - a
 * - so resetting one to head and moving both 1 step → meet at entry
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
    ListNode* detectCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
         bool hascycle = false;
        while(fast!=nullptr && fast->next!=nullptr){
            slow= slow->next;
            fast = fast->next->next;

            if(slow==fast){
                hascycle=true;
                break;
             
            }
        }

        if(hascycle){
           ListNode* entry = head;
                while(slow!=entry){
                    slow=slow->next;
                    entry = entry->next;
                }

            return entry;

        }


        return NULL;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    // Test 1 — cycle at index 1: 3→2→0→-4→back to 2
    ListNode* n1 = new ListNode(3);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(0);
    ListNode* n4 = new ListNode(-4);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n2;   // cycle at node with val=2
    ListNode* r1 = sol.detectCycle(n1);
    cout << "Test 1 — cycle entry: " << (r1 ? to_string(r1->val) : "null")
         << " | Expected: 2 " << (r1 && r1->val == 2 ? "✅" : "❌") << "\n";

    // Test 2 — cycle at index 0 (head): 1→2→back to 1
    ListNode* m1 = new ListNode(1);
    ListNode* m2 = new ListNode(2);
    m1->next = m2;
    m2->next = m1;   // cycle at head
    ListNode* r2 = sol.detectCycle(m1);
    cout << "Test 2 — cycle entry: " << (r2 ? to_string(r2->val) : "null")
         << " | Expected: 1 " << (r2 && r2->val == 1 ? "✅" : "❌") << "\n";

    // Test 3 — no cycle
    ListNode* p1 = new ListNode(1);
    ListNode* p2 = new ListNode(2);
    p1->next = p2;
    ListNode* r3 = sol.detectCycle(p1);
    cout << "Test 3 — no cycle  : " << (r3 ? to_string(r3->val) : "null")
         << " | Expected: null " << (!r3 ? "✅" : "❌") << "\n";

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : after meeting point reset one pointer to head
 *                both move 1 step → guaranteed to meet at cycle entry
 *
 * Why it works : F = C - a (mathematical proof)
 *                head→entry = meeting_point→entry (same distance)
 *
 * Edge cases   : no cycle     → fast hits null → return nullptr
 *                cycle at head → entry = head node itself
 *
 * Mistakes made: [fill this yourself]
 */