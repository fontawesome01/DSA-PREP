# 📊 Prefix Sum + Kadane's Algorithm

> Precompute cumulative sums for O(1) range queries. Kadane's finds max subarray in O(n).

---

## 🧠 Core Idea

```
Brute force range sum [l,r] → O(n) per query
Prefix sum → precompute once O(n), query O(1)

prefix[i] = sum of nums[0] to nums[i-1]
prefix[0] = 0 (empty prefix — no elements)

Range sum [l, r] = prefix[r+1] - prefix[l]
```

---

## 📐 Template 1 — Pure Prefix Sum (LC 303)

```cpp
// Build
vector<int> prefix(n + 1, 0);
for (int i = 0; i < n; i++)
    prefix[i + 1] = prefix[i] + nums[i];

// Query sum from l to r (inclusive, 0-indexed)
int rangeSum = prefix[r + 1] - prefix[l];
```

**Why size n+1 with prefix[0] = 0?**

```
avoids if-else for left == 0 edge case
sum(0, r) = prefix[r+1] - prefix[0] = prefix[r+1] - 0 ✅
```

**Visual:**

```
nums   = [1,  2,  3,  4,  5]
prefix = [0,  1,  3,  6, 10, 15]
          ↑
          always starts with 0

sum(1,3) = prefix[4] - prefix[1] = 10 - 1 = 9
           (2 + 3 + 4 = 9) ✅
```

---

## 📐 Template 2 — Prefix Sum + HashMap (LC 560)

```cpp
unordered_map<int, int> prefixCount;
prefixCount[0] = 1;       // empty prefix
int currentSum = 0;
int count = 0;

for (int i = 0; i < n; i++) {
    currentSum += nums[i];

    // how many earlier prefixes give subarray sum == k?
    if (prefixCount.count(currentSum - k))
        count += prefixCount[currentSum - k];

    prefixCount[currentSum]++;   // insert AFTER check
}
```

**Why prefixCount[0] = 1?**

```
if currentSum == k exactly
→ currentSum - k = 0
→ need 0 in map with count 1
→ represents empty prefix (subarray from index 0)
```

**Why check BEFORE insert?**

```
if we insert first, currentSum - k might match itself
→ would count a zero-length subarray (invalid)
```

**Why not sliding window for sum == k?**

```
array has NEGATIVE numbers
→ expanding window can decrease sum
→ shrinking can increase sum
→ sliding window monotonicity breaks
→ must use prefix sum + hashmap
```

---

## 📐 Template 3 — Prefix Sum + Modular Arithmetic (LC 974)

```cpp
unordered_map<int, int> remainderCount;
remainderCount[0] = 1;    // empty prefix has remainder 0
int currentSum = 0;
int count = 0;

for (int i = 0; i < n; i++) {
    currentSum += nums[i];
    int rem = ((currentSum % k) + k) % k;   // handle negative

    if (remainderCount.count(rem))
        count += remainderCount[rem];

    remainderCount[rem]++;
}
```

**Key math insight:**

```
(prefix[j] - prefix[i]) % k == 0
→ prefix[j] % k == prefix[i] % k
→ same remainder = difference divisible by k

DON'T subtract k like LC 560
just look up same remainder
```

**C++ negative mod trap:**

```
C++:    -1 % 5 = -1  (wrong for our purposes)
Python: -1 % 5 =  4  (correct)

Fix in C++: ((x % k) + k) % k
→ always gives positive remainder in range [0, k-1]
```

**LC 560 vs LC 974:**

```
LC 560: exact difference == k     → look up (currentSum - k) in map
LC 974: difference divisible by k → look up same remainder in map
```

---

## 📐 Template 4 — Kadane's Algorithm (LC 53)

```cpp
int maxSum = nums[0];
int currentSum = nums[0];

for (int i = 1; i < n; i++) {
    currentSum = max(nums[i], currentSum + nums[i]);
    maxSum = max(maxSum, currentSum);
}
```

**Core idea:**

```
at each index, only 2 choices:
  (a) extend previous subarray → currentSum + nums[i]
  (b) start fresh from here    → nums[i]
pick whichever is larger

if currentSum < 0 → adding it hurts → start fresh
if currentSum >= 0 → extending helps → keep going
```

**Visual:**

```
nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

i=0: curr=-2  max=-2
i=1: curr= 1  max= 1  (fresh, -2 was hurting)
i=2: curr=-2  max= 1
i=3: curr= 4  max= 4  (fresh start)
i=4: curr= 3  max= 4
i=5: curr= 5  max= 5
i=6: curr= 6  max= 6  ← answer
i=7: curr= 1  max= 6
i=8: curr= 5  max= 6

Answer = 6 → subarray [4, -1, 2, 1]
```

**Init trap:**

```
❌ maxSum = 0           → fails on all-negative arrays like [-3, -2, -1]
❌ maxSum = INT_MIN     → INT_MIN + negative = overflow (undefined behavior in C++)
✅ maxSum = nums[0]     → safe, clean, loop from i = 1
```

**DP connection:**

```
Kadane's is compressed 1D DP
dp[i] = max subarray ending at index i
dp[i] = max(nums[i], dp[i-1] + nums[i])
we just compress dp[] into a single variable currentSum
```

---

## 📐 Template 5 — Prefix Sum + Monotonic Deque (LC 862)

```cpp
int n = nums.size();
vector<long long> prefix(n + 1, 0);
for (int i = 0; i < n; i++)
    prefix[i + 1] = prefix[i] + nums[i];

deque<int> dq;
int ans = n + 1;

for (int j = 0; j <= n; j++) {
    // front: consume valid answers (shortest first)
    while (!dq.empty() && prefix[j] - prefix[dq.front()] >= k) {
        ans = min(ans, j - dq.front());
        dq.pop_front();     // used up, won't give shorter answer later
    }

    // back: remove useless larger prefix sums
    while (!dq.empty() && prefix[dq.back()] >= prefix[j]) {
        dq.pop_back();      // worse starting point
    }

    dq.push_back(j);
}

return ans == n + 1 ? -1 : ans;
```

**Key observations:**

```
sum(i, j) = prefix[j] - prefix[i]
we want: prefix[j] - prefix[i] >= k, minimize (j - i)

Remove from FRONT:
  prefix[j] - prefix[dq.front()] >= k → valid answer found
  pop front → any later j gives longer subarray with same i
  → this i is used up

Remove from BACK:
  prefix[dq.back()] >= prefix[j]
  → dq.back() is earlier AND has bigger prefix sum
  → j is a better starting point in every way
  → dq.back() is useless, remove it

Deque maintains: INCREASING order of prefix sums
```

**Why long long?**

```
values up to 10^5 elements × 10^5 each = 10^10
int max = ~2.1 × 10^9 → overflows
```

**vs LC 239:**

```
LC 239: decreasing deque → track max in fixed window
LC 862: increasing deque → track best starting point for variable window
same tool, different purpose
```

---

## 💡 Problem Connection Map

```
LC 303  → pure prefix sum, O(1) range query
LC 560  → prefix sum + hashmap (sum == k)
LC 974  → prefix sum + hashmap (sum % k == 0, mod arithmetic)
LC 53   → Kadane's algorithm (max subarray, no prefix needed)
LC 862  → prefix sum + monotonic deque (shortest subarray sum >= k)
```

---

## 💡 Thinking Framework — How to Approach Prefix Sum Problems

```
Step 1 — Does the problem involve subarray sums?
  yes → prefix sum is likely involved

Step 2 — What's the query type?
  single range sum query          → pure prefix sum (Template 1)
  count subarrays with sum == k   → prefix sum + hashmap (Template 2)
  count subarrays with sum % k    → prefix sum + mod + hashmap (Template 3)
  max contiguous subarray sum     → Kadane's (Template 4)
  shortest subarray with sum >= k → prefix sum + deque (Template 5)

Step 3 — Are there negative numbers?
  no negatives → sliding window might work (simpler)
  has negatives → sliding window breaks → use prefix sum + hashmap/deque

Step 4 — What data structure to pair with prefix sum?
  exact match    → HashMap (look up complement)
  mod match      → HashMap (look up same remainder)
  range min/max  → Monotonic Deque
  multiple queries on static array → Prefix Array
```

---

## 🚨 Common Mistakes

```
❌ maxSum = 0 in Kadane's           → fails on all-negative arrays
❌ INT_MIN + negative               → undefined behavior in C++ (overflow)
❌ (currentSum - k) % k for LC 974  → wrong pattern, just look up same remainder
❌ Forgetting prefixCount[0] = 1    → misses subarrays starting from index 0
❌ Insert before check in hashmap   → counts zero-length subarrays
❌ Using int for prefix in LC 862   → overflow with large inputs
❌ Applying LC 239 template to 862  → different deque logic (increasing vs decreasing)
❌ Using sliding window with negatives → monotonicity breaks
❌ Negative mod in C++              → -1 % 5 = -1, fix: ((x%k)+k)%k
❌ nums.size() comparison with int  → unsigned mismatch warning
```

---

## 🎯 Pattern Recognition

```
Problem signal                                → Template
───────────────────────────────────────────────────────────────
O(1) range sum on static array                → Pure Prefix Sum
Count subarrays with exact sum k              → Prefix Sum + HashMap
Count subarrays divisible by k                → Prefix Sum + Mod + HashMap
Maximum contiguous subarray sum               → Kadane's Algorithm
Shortest subarray with sum >= k (negatives)   → Prefix Sum + Monotonic Deque
Maximum/minimum in sliding window             → Monotonic Deque (LC 239)
2D range sum queries                          → 2D Prefix Sum
Product of array except self                  → Prefix Product (left × right)
```

---

## ✅ Problems Checklist

### Core — Solved

- [x] LC 303 — Range Sum Query Immutable _(Easy)_
- [x] LC 53 — Maximum Subarray _(Medium)_
- [x] LC 560 — Subarray Sum Equals K _(Medium)_
- [x] LC 974 — Subarray Sums Divisible by K _(Medium)_
- [x] LC 862 — Shortest Subarray with Sum at Least K _(Hard)_

### Extra Practice — Priority (do these 5 first)

- [ ] LC 525 — Contiguous Array _(Medium)_ — convert 0→-1, then sum == 0
- [ ] LC 523 — Continuous Subarray Sum _(Medium)_ — mod k + length >= 2
- [ ] LC 152 — Maximum Product Subarray _(Medium)_ — track min AND max
- [ ] LC 918 — Maximum Sum Circular Subarray _(Medium)_ — Kadane's + total sum trick
- [ ] LC 304 — Range Sum Query 2D _(Medium)_ — extend prefix sum to 2D

### Extra Practice — More

- [ ] LC 238 — Product of Array Except Self _(Medium)_ — prefix product variant
- [ ] LC 1314 — Matrix Block Sum _(Medium)_ — 2D prefix sum + boundaries
- [ ] LC 930 — Binary Subarrays With Sum _(Medium)_ — prefix sum + count
- [ ] LC 1590 — Make Sum Divisible by P _(Medium)_ — remove shortest subarray, mod
- [ ] LC 1749 — Maximum Absolute Sum of Any Subarray _(Medium)_ — Kadane's for max AND min
- [ ] LC 209 — Minimum Size Subarray Sum _(Medium)_ — positive only, sliding window works
- [ ] LC 1425 — Constrained Subsequence Sum _(Hard)_ — deque + DP
- [ ] LC 1499 — Max Value of Equation _(Hard)_ — deque on pairs

---

## 🏆 Multi-Platform Practice Problems

### Codeforces

| Problem                                  | Link                                             | Rating | Why                                     |
| ---------------------------------------- | ------------------------------------------------ | ------ | --------------------------------------- |
| CF 466C — Number of Ways                 | https://codeforces.com/problemset/problem/466/C  | 1700   | prefix sum partition into 3 equal parts |
| CF 1398C — Good Subarrays                | https://codeforces.com/problemset/problem/1398/C | 1600   | prefix sum + counting (sum == length)   |
| CF 1527C — Sequence Pair Weight          | https://codeforces.com/problemset/problem/1527/C | 1600   | prefix counting pairs                   |
| CF 1516C — Baby Ehab Partitions          | https://codeforces.com/problemset/problem/1516/C | 1700   | prefix sum + knapsack                   |
| CF 1191C — Tokitsukaze and Discard Items | https://codeforces.com/problemset/problem/1191/C | 1500   | prefix sum simulation                   |

### CSES

| Problem                              | Link                                 | Difficulty | Why                                  |
| ------------------------------------ | ------------------------------------ | ---------- | ------------------------------------ |
| CSES 1646 — Static Range Sum Queries | https://cses.fi/problemset/task/1646 | Easy       | pure prefix sum                      |
| CSES 1661 — Subarray Sums II         | https://cses.fi/problemset/task/1661 | Medium     | exactly LC 560 (with negatives)      |
| CSES 1662 — Subarray Divisibility    | https://cses.fi/problemset/task/1662 | Medium     | exactly LC 974                       |
| CSES 1643 — Maximum Subarray Sum     | https://cses.fi/problemset/task/1643 | Easy       | exactly Kadane's                     |
| CSES 1644 — Maximum Subarray Sum II  | https://cses.fi/problemset/task/1644 | Hard       | Kadane's + deque (length constraint) |

### AtCoder

| Problem                      | Link                                              | Difficulty | Why                                    |
| ---------------------------- | ------------------------------------------------- | ---------- | -------------------------------------- |
| ABC 125C — GCD on Blackboard | https://atcoder.jp/contests/abc125/tasks/abc125_c | Medium     | prefix/suffix GCD (prefix idea on GCD) |
| ABC 098C — Attention         | https://atcoder.jp/contests/abc098/tasks/arc098_a | Medium     | prefix count East/West                 |
| ABC 122C — GeT AC            | https://atcoder.jp/contests/abc122/tasks/abc122_c | Easy       | prefix count of "AC" substrings        |

---

## 🔗 Key Insight Per Problem

| Problem | The Trick                                                                       |
| ------- | ------------------------------------------------------------------------------- |
| LC 303  | prefix[0] = 0 eliminates left == 0 edge case                                    |
| LC 53   | init to nums[0] not 0, max(extend, fresh) at each step                          |
| LC 560  | prefix sum + hashmap, check THEN insert, prefixCount[0] = 1                     |
| LC 974  | same remainder = divisible, ((x%k)+k)%k for negative mod                        |
| LC 862  | increasing deque on prefix sums, pop front = consume, pop back = remove useless |

---

## 📚 Resources

- [NeetCode LC 53](https://www.youtube.com/watch?v=5WZl3MMT0Eg)
- [NeetCode LC 560](https://www.youtube.com/watch?v=fFVZt-6sgyo)
- [NeetCode LC 862](https://www.youtube.com/watch?v=K0NgGYEAkA4)
- [USACO Guide — Prefix Sums](https://usaco.guide/silver/prefix-sums)
- [cp-algorithms — Prefix Sum](https://cp-algorithms.com/others/prefix-sums.html)
- [CSES Problem Set](https://cses.fi/problemset/)

---

_Prefix Sum = precompute once, query O(1). Kadane's = compressed DP for max subarray. Deque = when you need shortest/longest with a sum constraint and negatives exist._
