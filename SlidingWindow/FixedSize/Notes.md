# 🪟 Sliding Window — Fixed Size

> Window size = k, never changes. Slide by adding right, removing left.

---

## 🧠 Core Idea

```
Brute force recalculates from scratch every window → O(n*k)
Sliding window reuses previous result             → O(n)

add incoming (right) → remove outgoing (left) → update answer
```

---

## 📐 Template 1 — Sum / Count / Average

```cpp
// build first window
for (int i = 0; i < k; i++)
    windowSum += nums[i];

double result = windowSum / k;

// slide
for (int i = k; i < n; i++) {
    windowSum += nums[i];
    windowSum -= nums[i - k];
    result = max(result, windowSum / k);
}
```

**When:** max/min average, count of elements, sum in fixed window

**Tricks:**

- avoid division → use `sum >= threshold * k` instead of `avg >= threshold`
- use `long long` when n and values both large → overflow risk

---

## 📐 Template 2 — Frequency Map

```cpp
vector<int> freq1(26, 0);  // target
vector<int> freq2(26, 0);  // current window

for (char c : p)             freq1[c-'a']++;
for (int i = 0; i < k; i++) freq2[s[i]-'a']++;

if (freq1 == freq2) // match

for (int i = k; i < n; i++) {
    freq2[s[i]-'a']++;
    freq2[s[i-k]-'a']--;
    if (freq1 == freq2) // match
}
```

**When:** permutation check, anagram finding, character matching

**Optimization — matches counter (O(1) per slide):**

```cpp
// adding 'in':
if (freq2[in] == freq1[in]) matches--;
freq2[in]++;
if (freq2[in] == freq1[in]) matches++;

// removing 'out':
if (freq2[out] == freq1[out]) matches--;
freq2[out]--;
if (freq2[out] == freq1[out]) matches++;

if (matches == 26) // all chars match
```

---

## 📐 Template 3 — Monotonic Deque

```cpp
deque<int> dq;  // stores INDICES, not values

for (int i = 0; i < n; i++) {
    // remove from FRONT if outside window
    if (!dq.empty() && dq.front() < i - k + 1)
        dq.pop_front();

    // MAX → remove SMALLER from back
    while (!dq.empty() && nums[dq.back()] < nums[i])
        dq.pop_back();
    // MIN → remove LARGER from back
    // while (!dq.empty() && nums[dq.back()] > nums[i])

    dq.push_back(i);

    if (i >= k - 1)
        result.push_back(nums[dq.front()]);
}
```

**When:** maximum or minimum in every window of size k

**Why indices not values:**

- values can't tell if element left the window
- index tells position → check `dq.front() < i-k+1`

**Why O(n):**

- each element pushed once + popped once = 2n total ops
- amortized O(1) per element despite while loop inside for loop

**MAX vs MIN — one character:**

```
MAX → nums[dq.back()] < nums[i]   remove smaller
MIN → nums[dq.back()] > nums[i]   remove larger
```

---

## 📐 Template 4 — Two Heaps (Median)

```cpp
// when answer depends on sorted order → heaps required
priority_queue<int> maxH;                              // lower half
priority_queue<int, vector<int>, greater<int>> minH;   // upper half
unordered_map<int, int> toDelete;                      // lazy deletion

// balance rule: maxH.size() >= minH.size() always
// median: maxH.top() (odd k) or avg of both tops (even k)
```

**When:** median, kth element in window — anything order-dependent

**Why normal sliding fails for median:**

```
sum   → add/subtract formula exists  → O(1) slide
median → no formula → middle position shifts unpredictably
       → must maintain sorted order → heaps
```

**Revisit:** after Day 31 (Heaps chapter)

---

## 🔄 Circular Array Handling

**Option A — Modulo:**

```cpp
next element → arr[(i + 1) % n]
prev element → arr[(i - 1 + n) % n]   // +n avoids negative
```

**Option B — Double the Array:**

```cpp
vector<int> doubled(arr.begin(), arr.end());
doubled.insert(doubled.end(), arr.begin(), arr.end());
// slide window normally — no wrapping needed
```

**When to use which:**

```
single element access   → % modulo
sliding window          → double the array
```

---

## 💡 Thinking Patterns

**Base + Bonus thinking (LC1052):**

```
base  = what you always get (no power used)
bonus = best gain from using power in optimal window
answer = base + max bonus
```

**Reverse thinking (LC1423):**

```
picking k from ends = leaving n-k in middle
max score = total - min(window of size n-k)
find min instead of max
```

**Distinctness tracking (LC2461):**

```
don't scan window → O(k) per slide
track distinctCount with freq map → O(1) per slide
freq==1 → unique, freq==2 → duplicate
```

---

## 🚨 Common Mistakes

```
❌ dq.back() instead of dq.front() for window bound check
❌ > instead of < in deque → computes min not max
❌ result update inside if block due to missing {}
❌ integer division → use sum >= threshold * k
❌ int instead of long long for large sums
❌ i < s.size() with int i → store as int n = s.size()
❌ missing early return when k > n
❌ forgetting +n in circular prev: (i-j+n) % n
```

---

## 🎯 Pattern Recognition

```
Problem signal                          → Template
────────────────────────────────────────────────────────
Max/min/avg in fixed window             → Template 1
Count subarrays meeting condition       → Template 1
Permutation exists in string            → Template 2
All anagram positions                   → Template 2
Max/min of every window                 → Template 3 (deque)
Median of every window                  → Template 4 (heaps)
Circular array + window                 → double the array
"best bonus from one-time power"        → base + bonus
"picking from both ends"                → reverse → find min middle
```

---

## ✅ Problems Checklist

### Core — Solved

- [x] LC643 — Maximum Average Subarray I
- [x] LC1343 — Number of Subarrays Size K >= Threshold
- [x] LC567 — Permutation in String
- [x] LC438 — Find All Anagrams in a String
- [x] LC239 — Sliding Window Maximum
- [x] LC1456 — Maximum Vowels in Substring
- [x] LC1652 — Defuse the Bomb
- [x] LC2090 — K Radius Subarray Averages
- [x] LC1052 — Grumpy Bookstore Owner
- [x] LC1423 — Maximum Points You Can Obtain
- [x] LC2461 — Maximum Sum of Distinct Subarrays
- [ ] LC480 — Sliding Window Median _(revisit Day 31)_
- [ ] LC995 — Min K Consecutive Bit Flips _(revisit Day 57)_

### More Medium Practice — LeetCode

- [ ] LC1876 — Substrings of Size Three with Distinct Characters
- [ ] LC2379 — Minimum Recolors to Get K Consecutive Black Blocks
- [ ] LC1888 — Minimum Number of Flips to Make Binary String Alternating
- [ ] LC2134 — Minimum Swaps to Group All 1s Together II
- [ ] LC1297 — Maximum Number of Occurrences of a Substring

### Codeforces Problems

- [ ] CF 701C — They Are Everywhere (1700) — sliding window + map
      https://codeforces.com/problemset/problem/701/C
- [ ] CF 380C — Sereja and Brackets (1700) — segment tree + window
      https://codeforces.com/problemset/problem/380/C
- [ ] CF 676C — Vasya and String (1700) — fixed window on string
      https://codeforces.com/problemset/problem/676/C

### AtCoder Problems

- [ ] ABC 130D — Enough Array — fixed window count
      https://atcoder.jp/contests/abc130/tasks/abc130_d
- [ ] ABC 098C — Container on a Conveyor Belt
      https://atcoder.jp/contests/abc098/tasks/arc098_a

---

## 🔗 Key Insight Per Problem

| Problem | The Trick                                    |
| ------- | -------------------------------------------- |
| LC643   | divide sum by k for average                  |
| LC1343  | sum >= threshold×k — avoid division          |
| LC567   | freq arrays equal = permutation found        |
| LC438   | same as LC567 — collect ALL indices          |
| LC239   | deque stores indices, front = max            |
| LC1456  | lambda isVowel() — avoid repeating 5 checks  |
| LC1652  | double array, 3 cases: k>0, k=0, k<0         |
| LC2090  | window size = 2k+1, long long for sum        |
| LC1052  | base + bonus — only count grumpy in window   |
| LC1423  | reverse — total minus min middle window      |
| LC2461  | distinctCount with freq map — O(1) per slide |
| LC480   | two heaps + lazy deletion — O(n log k)       |

---

## 📚 Resources

- [NeetCode LC239](https://www.youtube.com/watch?v=DfljaUwZsOk) — deque explanation
- [NeetCode LC567](https://www.youtube.com/watch?v=UbyhOgBN834) — frequency map
- [NeetCode LC480](https://www.youtube.com/watch?v=1LkOrc-Le-Y) — two heaps
- [cp-algorithms — Sliding Window](https://cp-algorithms.com/sequences/rmq.html)

---

_Fixed window = size never changes. If size changes with condition → Dynamic Window (Day 4)_
