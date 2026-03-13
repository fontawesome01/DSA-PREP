# Two Pointers — Opposite Ends

## Pattern

```
left = 0, right = n-1
while (left < right) {
    if condition met       → record answer, move both
    if sum/value too big   → right--
    if sum/value too small → left++
}
```

## When to Use

- Sorted array + find pair/triplet with target sum
- Palindrome check
- Container / area problems (index = width)
- Merge from back (fill from end)

## Key Rules

```
1. Always sort first if problem involves sums
2. Skip duplicates BEHIND — compare with i-1, not i+1
3. Never sort when index = width (LC 11)
4. Use long long when sum can overflow int
5. j boundary in 4Sum is i+1 not 0
```

## Time/Space

```
Two Pointers scan  : O(n)
With outer loop    : O(n²) for 3Sum, O(n³) for 4Sum
Space              : O(1) always
```

---

## Problems Solved

| #     | Problem                   | Difficulty | Score  | Key Trick                     |
| ----- | ------------------------- | ---------- | ------ | ----------------------------- |
| LC167 | Two Sum II                | Medium     | 7/10   | sorted → opposite ends        |
| LC125 | Valid Palindrome          | Easy       | 9.5/10 | isalnum + tolower             |
| LC11  | Container With Most Water | Medium     | 9/10   | move shorter side             |
| LC15  | 3Sum                      | Medium     | 10/10  | sort + skip duplicates behind |
| LC88  | Merge Sorted Array        | Easy       | 8/10   | fill from back                |
| LC977 | Squares of Sorted Array   | Easy       | 7.5/10 | largest squares at ends       |
| LC16  | 3Sum Closest              | Medium     | 9.5/10 | track mindiff                 |
| LC18  | 4Sum                      | Medium     | 10/10  | long long + j>i+1             |

---

## Mistakes to Never Repeat

```
❌ == instead of = (assignment bug)
❌ Sorting array when index matters (LC 11)
❌ Duplicate skip: nums[left+1] instead of nums[left-1]
❌ j>0 instead of j>i+1 in 4Sum
❌ Forgetting long long cast in 4Sum
```

---

## Hard Problems — Try These Next

### LeetCode Hard

| Problem                                     | Why Hard                                    | Hint                                |
| ------------------------------------------- | ------------------------------------------- | ----------------------------------- |
| LC42 — Trapping Rain Water                  | Two pointers + max tracking from both sides | precompute leftMax, rightMax arrays |
| LC11 variant — LC407 Trapping Rain Water II | 3D version using min-heap                   | BFS + heap                          |

### Codeforces Problems

| Problem                            | Link                                             | Rating | Why                                |
| ---------------------------------- | ------------------------------------------------ | ------ | ---------------------------------- |
| CF 1359C — Mixing Water            | https://codeforces.com/problemset/problem/1359/C | 1700   | Binary search + two pointers combo |
| CF 381C — Sereja and Two Sequences | https://codeforces.com/problemset/problem/381/C  | 1900   | Two pointers on two arrays         |
| CF 1033C — Permutation Game        | https://codeforces.com/problemset/problem/1033/C | 1900   | Two pointers + greedy              |

### LeetCode Hard (Extension)

| Problem                                      | Why                                          |
| -------------------------------------------- | -------------------------------------------- |
| LC 992 — Subarrays with K Different Integers | Two pointers + sliding window combo          |
| LC 825 — Friends of Appropriate Ages         | Two pointers on sorted array with conditions |

---

## Pattern Recognition Signal

```
See this in problem          → Think this
─────────────────────────────────────────
Sorted array + pair sum      → Two Pointers Opposite Ends
Find triplet/quadruplet      → Sort + fix outer + two pointers
Palindrome / symmetry check  → Left right shrink
Merge two sorted arrays      → Fill from back
Squares of sorted array      → Largest at ends → fill from back
```
