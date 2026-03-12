# 🚀 DSA-PREP

> A structured C++ repository for mastering Data Structures & Algorithms

Each solution includes the **pattern used**, **approach explanation**, **time/space complexity**, and **test cases** — so anyone can learn from it, not just solve it.

---

## 📊 Progress

| Day | Topic | Pattern | Problems Solved |
|-----|-------|---------|----------------|
| Day 1 | Arrays — Two Pointers | Opposite Ends, Fill From Back | [9 problems →](./TWO_POINTERS/TwoPointers_OppositteEnds/) |
| Day 2 | Arrays — Fast Slow Pointers | Same Direction, Floyd's Cycle Detection | [6 problems →](./TWO_POINTERS/TwoPointers_FastSlow/) |

**Total Problems: 15 &nbsp;·&nbsp; Days Completed: 2 &nbsp;·&nbsp; Streak: 2 days 🔥**

---

## 📁 Structure

```
DSA-PREP/
│
├── TWO_POINTERS/
│   ├── TwoPointers_Day1/        # Opposite ends, 3Sum, Trapping Rain Water
│   └── TwoPointers_FastSlow/    # Floyd's cycle detection, Find Duplicate
│
├── SLIDING_WINDOW/              # coming soon
├── LINKED_LIST/                 # coming soon
├── STACK/                       # coming soon
├── TREES/                       # coming soon
├── GRAPHS/                      # coming soon
└── DP/                          # coming soon
```

---

## 🧠 Patterns Covered

### Two Pointers — Opposite Ends
**When to use:** sorted array + pair/triplet sum, palindrome check, container problems
```
left = 0, right = n-1
while (left < right) {
    if condition → move left++
    else         → move right--
}
```
**Problems:** Two Sum II, 3Sum, 4Sum, Container With Most Water, Trapping Rain Water

---

### Two Pointers — Same Direction
**When to use:** remove duplicates, move zeroes, filter elements in-place
```
slow = 0  ← write pointer
for fast = 0 to n:
    if condition → write at slow, slow++
```
**Problems:** Remove Duplicates, Move Zeroes

---

### Fast-Slow Pointers (Floyd's Cycle Detection)
**When to use:** detect cycle, find middle, find cycle entry point
```
slow = slow->next
fast = fast->next->next
if slow == fast → cycle exists
```
**Problems:** Middle of Linked List, Linked List Cycle I & II, Find Duplicate Number

---

## 📌 How to Use This Repo

Every `.cpp` file follows this structure:
```
Header     → problem name, pattern, approach, time/space complexity
Solution   → clean C++ code inside class Solution
Tests      → 4-5 test cases covering edge cases
Notes      → key insight, edge cases, mistakes made
```

To run any file locally:
```bash
g++ filename.cpp -o solution
./solution
```

---

## 🔗 Resources

- [NeetCode YouTube](https://www.youtube.com/@NeetCode) — best pattern explanations
- [LeetCode](https://leetcode.com) — primary problem platform
- [cp-algorithms.com](https://cp-algorithms.com) — algorithm theory

---

*Consistency beats intensity. One problem at a time.*
