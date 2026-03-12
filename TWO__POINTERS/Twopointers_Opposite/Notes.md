# Fast-Slow Pointers (Floyd's Cycle Detection)

## Pattern

```cpp
// Same Direction — Filter/Remove
int slow = 0;
for (int fast = 0; fast < n; fast++) {
    if (condition) nums[slow++] = nums[fast];
}

// Fast-Slow on Linked List
ListNode* slow = head;
ListNode* fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) // cycle detected
}

// On Array (LC287)
int slow = 0, fast = 0;
do {
    slow = nums[slow];
    fast = nums[nums[fast]];
} while (slow != fast);
```

## When to Use

- Detect if cycle exists in linked list
- Find middle of linked list
- Find entry point of cycle
- Find duplicate in array (treat as linked list)
- Remove duplicates / move elements in-place

## Key Rules

```
1. Fast moves 2 steps, slow moves 1 step
2. Check AFTER moving, not before
3. Null guard: fast != null && fast->next != null
4. For arrays: use do-while (both start at 0, while would exit immediately)
5. Phase 2: reset one pointer to head/0, both move 1 step → meet at entry
6. Array values must be 1 to n for LC287 (otherwise segfault)
```

## Time/Space

```
All patterns : O(n) time
              O(1) space — no extra memory
```

## Why do-while for LC287

```
slow = 0, fast = 0 → both equal at start
while (slow != fast) → exits immediately → WRONG
do { move } while (slow != fast) → moves first, then checks → CORRECT
```

---

## Problems Solved

| #     | Problem               | Difficulty | Score  | Key Trick                                   |
| ----- | --------------------- | ---------- | ------ | ------------------------------------------- |
| LC26  | Remove Duplicates     | Easy       | 8/10   | slow=write pointer, compare with nums[slow] |
| LC283 | Move Zeroes           | Easy       | 9.5/10 | swap non-zero with left pointer             |
| LC876 | Middle of Linked List | Easy       | 10/10  | fast done → slow at middle                  |
| LC141 | Linked List Cycle     | Easy       | 9/10   | fast==slow → cycle exists                   |
| LC142 | Linked List Cycle II  | Medium     | 9.5/10 | reset to head → meet at entry               |
| LC287 | Find Duplicate Number | Medium     | 8.5/10 | array as linked list, do-while              |

---

## Floyd's Cycle Detection — Math Proof

```
F = distance from head to cycle entry
C = cycle length
a = distance from entry to meeting point

When slow & fast meet:
  slow traveled: F + a
  fast traveled: F + a + C (one full extra loop)
  fast = 2 * slow → F + a + C = 2(F + a)
  → C = F + a
  → F = C - a

So: distance from head to entry = distance from meeting point to entry
Reset one pointer to head, move both 1 step → meet at entry ✅
```

---

## Mistakes to Never Repeat

```
❌ break after return — unreachable code
❌ slow = nums[0] as start in LC287 — segfault (use index 0)
❌ Invalid test cases for LC287 — values must be 1 to n strictly
❌ while instead of do-while when both pointers start equal
❌ Missing null guard fast->next — causes null dereference
```

---

## Hard Problems — Try These Next

### LeetCode Hard

| Problem                     | Why Hard                                               | Hint                        |
| --------------------------- | ------------------------------------------------------ | --------------------------- |
| LC457 — Circular Array Loop | Cycle in circular array, all-same-direction constraint | Fast-slow + direction check |
| LC202 — Happy Number        | Cycle detection on number sequence                     | Fast-slow on digit sum      |

### Codeforces Problems

| Problem                         | Link                                             | Rating | Why                            |
| ------------------------------- | ------------------------------------------------ | ------ | ------------------------------ |
| CF 771C — Bear and Tree Jumps   | https://codeforces.com/problemset/problem/771/C  | 1900   | Fast-slow pointer idea on tree |
| CF 1033B — Creating the Contest | https://codeforces.com/problemset/problem/1033/B | 1500   | Two pointer same direction     |
| CF 580C — Kefa and Park         | https://codeforces.com/problemset/problem/580/C  | 1500   | Pointer traversal on tree      |

### LeetCode Extension

| Problem                         | Why                                            |
| ------------------------------- | ---------------------------------------------- |
| LC 234 — Palindrome Linked List | Fast-slow to find middle + reverse second half |
| LC 143 — Reorder List           | Fast-slow + reverse + merge                    |

---

## Pattern Recognition Signal

```
See this in problem               → Think this
──────────────────────────────────────────────────
Remove/filter elements in-place   → Same Direction (slow=write)
Find middle of linked list        → Fast-Slow (fast moves 2x)
Detect cycle                      → Fast-Slow (meet = cycle)
Find where cycle starts           → Phase 2 reset to head
Find duplicate, no extra space    → LC287 array as linked list
```
