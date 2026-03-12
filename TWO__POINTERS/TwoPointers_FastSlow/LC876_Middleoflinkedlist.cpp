/*
 * Problem   : LC876 — Middle of Linked List
 * Topic     : Linked List
 * Pattern   : Fast-Slow Pointers
 * Difficulty: Easy
 * Link      : https://leetcode.com/problems/middle-of-the-linked-list/
 *
 * Approach  :
 * - fast moves 2 steps, slow moves 1 step
 * - when fast hits null → slow is exactly at middle
 * - even length → returns second middle (fast hits null one step early)
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
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// ─── Helper — build list from vector ─────────────────
ListNode* buildList(vector<int> vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* curr = head;
    for (int i = 1; i < vals.size(); i++) {
        curr->next = new ListNode(vals[i]);
        curr = curr->next;
    }
    return head;
}

// ─── Solution ────────────────────────────────────────
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        return slow;
    }
};

// ─── Test ────────────────────────────────────────────
int main() {
    Solution sol;

    auto run = [&](vector<int> vals, int expected) {
        ListNode* head = buildList(vals);
        ListNode* result = sol.middleNode(head);
        cout << "Input    : ";
        for (int x : vals) cout << x << " ";
        cout << "\nMiddle   : " << result->val
             << " | Expected: " << expected
             << (result->val == expected ? " ✅" : " ❌")
             << "\n\n";
    };

    run({1, 2, 5, 5, 5}, 3);

    
    run({1, 2, 3, 4, 5, 6}, 4);

    // Test 3 — single node
    run({1}, 1);

    // Test 4 — two nodes → second node
    run({1, 2}, 2);

    return 0;
}

/*
 * ─── Notes ───────────────────────────────────────────
 * Key insight  : fast moves 2x speed → when fast done, slow at middle
 *                even list → fast->next hits null → slow at second middle
 *
 * Edge cases   : single node → fast->next = null → loop never runs → return head
 *                two nodes   → fast moves to null → slow at node 2
 *
 * Mistakes made:  not make any learned this concept deeply ,but i am gaining knowledge how can i build my test cases for hese questions 
 * 
 */