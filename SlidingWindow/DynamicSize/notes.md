# 🪟 Sliding Window — Dynamic Size

> Window size changes based on condition. Expand right, shrink left when invalid.

---

## 🧠 Core Idea

```
Fixed window  → size k never changes
Dynamic window → expand until condition breaks → shrink until valid again

Two types:
Type 1 — LONGEST valid window  → result = max(result, right-left+1)
Type 2 — SHORTEST valid window → result = min(result, right-left+1)
```

---

## 📐 Core Template

```cpp
int left = 0;
int result = 0;

for (int right = 0; right < n; right++) {
    // expand — add nums[right] to window state

    // shrink — while condition violated
    while (condition violated) {
        // remove nums[left] from window state
        left++;
    }

    // update answer — window is valid here
    result = max(result, right - left + 1);  // Type 1 — longest
    // result = min(result, right - left + 1); // Type 2 — shortest
}
```

**Window size formula:** `right - left + 1`

---

## 📐 Template 1 — HashSet (unique chars/elements)

```cpp
unordered_set<char> seen;
int left = 0;

for (int right = 0; right < n; right++) {
    while (seen.count(s[right]))  {
        seen.erase(s[left]);
        left++;
    }
    seen.insert(s[right]);
    result = max(result, right - left + 1);
}
```

**When:** longest substring with all unique characters (LC3)

---

## 📐 Template 2 — Frequency Array (char replacement)

```cpp
int freq[26] = {0};
int maxFreq = 0;
int left = 0;

for (int right = 0; right < n; right++) {
    freq[s[right] - 'A']++;
    maxFreq = max(maxFreq, freq[s[right] - 'A']);

    while ((right - left + 1) - maxFreq > k) {
        freq[s[left] - 'A']--;
        left++;
    }
    result = max(result, right - left + 1);
}
```

**When:** longest window where replacements needed <= k (LC424, LC1004)

**The maxFreq trick:**

```
maxFreq never decreases when shrinking
Only care about windows longer than current best
If maxFreq drops → window shrinks → not useful → skip recalculation
```

---

## 📐 Template 3 — HashMap (at most k distinct)

```cpp
unordered_map<int, int> freq;
int left = 0;

for (int right = 0; right < n; right++) {
    freq[nums[right]]++;

    while (freq.size() > k) {
        freq[nums[left]]--;
        if (freq[nums[left]] == 0)
            freq.erase(nums[left]);  // only erase when fully gone
        left++;
    }
    result = max(result, right - left + 1);
}
```

**When:** at most k distinct values/types (LC904 k=2, LC340 any k)

**Why HashMap not HashSet:**

```
Set removes type completely on erase
Map tracks frequency → only remove type when freq hits 0
type might still exist elsewhere in window
```

---

## 📐 Template 4 — have/need Counter (minimum window)

```cpp
unordered_map<char,int> freqt, freqs;
int have = 0, need = freqt.size();
int left = 0, result = INT_MAX;

for (int right = 0; right < n; right++) {
    freqs[s[right]]++;
    if (freqt.count(s[right]) && freqs[s[right]] == freqt[s[right]])
        have++;

    while (have == need) {           // Type 2 — shrink while valid
        result = min(result, right - left + 1);
        if (freqt.count(s[left]) && freqs[s[left]] == freqt[s[left]])
            have--;
        freqs[s[left]]--;
        left++;
    }
}
```

**When:** minimum window containing all target characters (LC76)

**have/need logic:**

```
need = number of unique chars in t to satisfy
have++ only when freqs[c] exactly reaches freqt[c]
have-- only when freqs[c] drops below freqt[c] on shrink
valid when have == need → O(1) check per step
```

---

## 💡 Problem Connection Map

```
LC3    → hashset, shrink while duplicate
LC424  → freq array, window - maxFreq <= k
LC1004 → same as LC424, window - count <= k  (zeros = window - ones)
LC904  → hashmap, at most 2 distinct (k=2 case of LC340)
LC76   → have/need counter, Type 2 shortest window
```

---

## 💡 Thinking Framework — How to Approach Any Dynamic Window

```
Step 1 — Reframe the problem
  "find longest subarray where..." → dynamic window

Step 2 — Define window validity
  what condition makes window valid?
  what condition makes it invalid?

Step 3 — Choose data structure
  unique elements only    → HashSet
  char frequency          → int freq[26]
  any type frequency      → HashMap
  need all of target      → have/need counter

Step 4 — Which type?
  find LONGEST  → Type 1 (shrink when invalid, update after shrink)
  find SHORTEST → Type 2 (shrink while valid, update inside shrink)

Step 5 — Code the template
```

---

## 🚨 Common Mistakes

```
❌ HashSet for frequency → removes type even if still in window
❌ Recalculating maxFreq on shrink → unnecessary, maxFreq only goes up
❌ Updating result before shrinking in Type 2 → gives wrong answer
❌ Forgetting to erase from map when freq == 0
❌ containsMap() scanning whole map → O(n*t) → use have/need → O(n)
❌ int vs unsigned for size() → store as int n = s.size()
```

---

## 🎯 Pattern Recognition

```
Problem signal                              → Template
──────────────────────────────────────────────────────────────
Longest substring all unique chars          → HashSet shrink
Longest window with at most k replacements  → freq array + maxFreq
Longest window with at most k zeros flipped → freq array + count
At most 2 distinct fruit types              → HashMap erase on 0
At most k distinct values                   → HashMap erase on 0
Minimum window containing all of t         → have/need counter
```

---

## ✅ Problems Checklist

### Core — Solved

- [x] LC3 — Longest Substring Without Repeating Characters
- [x] LC424 — Longest Repeating Character Replacement
- [x] LC1004 — Max Consecutive Ones III
- [x] LC904 — Fruit Into Baskets
- [x] LC76 — Minimum Window Substring _(Hard)_

### Extra Practice — Do on Day 25

- [ ] LC2269 — Find the K-Beauty of a Number _(Easy)_
- [ ] LC1876 — Substrings of Size Three With Distinct Chars _(Easy)_
- [ ] LC1100 — Find K-Length Substrings No Repeated Chars _(Easy)_
- [ ] LC1493 — Longest Subarray of 1s After Deleting One Element _(Medium)_
- [ ] LC2024 — Maximize the Confusion of an Exam _(Medium)_
- [ ] LC1208 — Get Equal Substrings Within Budget _(Medium)_
- [ ] LC159 — Longest Substring At Most Two Distinct _(Medium)_
- [ ] LC340 — Longest Substring At Most K Distinct _(Medium)_
- [ ] LC992 — Subarrays with K Different Integers _(Hard)_
- [ ] LC30 — Substring With Concatenation of All Words _(Hard)_

---

## 🏆 Multi-Platform Practice Problems

### Codeforces

| Problem                          | Link                                             | Rating | Why                                    |
| -------------------------------- | ------------------------------------------------ | ------ | -------------------------------------- |
| CF 701C — They Are Everywhere    | https://codeforces.com/problemset/problem/701/C  | 1600   | at most k distinct — LC904 generalized |
| CF 616D — Longest k-Good Segment | https://codeforces.com/contest/616/problem/D     | 1600   | dynamic window + distinct count        |
| CF 676C — Vasya and String       | https://codeforces.com/problemset/problem/676/C  | 1700   | window on binary string                |
| CF 1033B — Creating the Contest  | https://codeforces.com/problemset/problem/1033/B | 1500   | greedy + window                        |
| CF 660F — Bear and Bowling       | https://codeforces.com/problemset/problem/660/F  | 2500   | hard window variant                    |

### CSES (must do — best quality problems)

| Problem                              | Link                                 | Difficulty | Why                   |
| ------------------------------------ | ------------------------------------ | ---------- | --------------------- |
| CSES 1620 — Two Sets                 | https://cses.fi/problemset/task/1620 | Easy       | window basics         |
| CSES 2428 — Subarray Distinct Values | https://cses.fi/problemset/task/2428 | Medium     | exactly LC904 pattern |
| CSES 1644 — Maximum Subarray Sum     | https://cses.fi/problemset/task/1644 | Medium     | Kadane's + window     |
| CSES 1076 — Sliding Window Median    | https://cses.fi/problemset/task/1076 | Hard       | two heaps             |
| CSES 1077 — Sliding Window Cost      | https://cses.fi/problemset/task/1077 | Hard       | two multisets         |

### AtCoder

| Problem                               | Link                                              | Difficulty | Why                    |
| ------------------------------------- | ------------------------------------------------- | ---------- | ---------------------- |
| ABC 130D — Enough Array               | https://atcoder.jp/contests/abc130/tasks/abc130_d | Medium     | classic dynamic window |
| ABC 098C — Container on Conveyor Belt | https://atcoder.jp/contests/abc098/tasks/arc098_a | Medium     | window with condition  |
| ABC 229D — Longest Subarray           | https://atcoder.jp/contests/abc229/tasks/abc229_d | Medium     | at most k distinct     |

### USACO

| Problem                  | Link                                                      | Difficulty | Why                      |
| ------------------------ | --------------------------------------------------------- | ---------- | ------------------------ |
| USACO — Haybale Stacking | http://www.usaco.org/index.php?page=viewproblem2&cpid=104 | Silver     | sliding window on ranges |
| USACO — Rental Service   | http://www.usaco.org/index.php?page=viewproblem2&cpid=787 | Gold       | window + sorting         |

---

## 🔗 Key Insight Per Problem

| Problem | The Trick                                                   |
| ------- | ----------------------------------------------------------- |
| LC3     | shrink while duplicate — hashset O(1) per op                |
| LC424   | window - maxFreq <= k — maxFreq never recalculated downward |
| LC1004  | zeros = window - count of ones — same as LC424              |
| LC904   | hashmap not hashset — erase only when freq == 0             |
| LC76    | have/need counter — O(1) validity check vs O(t) scan        |

---

## 📚 Resources

- [NeetCode LC3](https://www.youtube.com/watch?v=wiGpZahaKaM)
- [NeetCode LC424](https://www.youtube.com/watch?v=gqXU1UyA8pk)
- [NeetCode LC76](https://www.youtube.com/watch?v=jSto0O4AJbM)
- [USACO Guide — Sliding Window](https://usaco.guide/gold/sliding-window)
- [CSES Problem Set](https://cses.fi/problemset/)

---

_Dynamic window = size changes with condition. If size is fixed → Fixed Window (Day 3)_
