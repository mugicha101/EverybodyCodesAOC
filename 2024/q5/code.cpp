#include "../../template.h"

array<deque<int>, 4> input() {
  array<deque<int>, 4> cols;
  while (true) {
    int x;
    if (!(cin >> x)) break;

    cols[0].push_back(x);
    for (int i = 1; i < 4; ++i) {
      cin >> x;
      cols[i].push_back(x);
    }
  }
  return cols;
}

void round(array<deque<int>, 4> &cols, int r) {
  int c = r & 0b11;
  int x = cols[c].front();
  cols[c].pop_front();
  c = (c + 1) & 0b11;
  // k = num of people in target column
  // m = { _, 0, 1, 2, 3, ..., k, k-1, k-2, ..., 0, 1, ... }
  // insert at m[x]
  // can use formula to get o = m[x] (messed around in desmos to get it)
  int k = cols[c].size();
  int o = abs(((x + k - 1) % (2 * k)) - k);
  cols[c].push_front(x);
  for (int i = 0; i < o; ++i) {
    swap(cols[c][i], cols[c][i+1]);
  }
}

ll getNum(array<deque<int>, 4> &cols) {
  ll num = 0;
  for (auto &c : cols) {
    int x = c.front();
    int m = 1;
    while (m <= x) m *= 10;
    num = (num * m) + x;
  }
  return num;
}

void partA() {
  auto cols = input();
  for (int r = 0; r < 10; ++r) round(cols, r);
  cout << getNum(cols) << endl;
}

void partB() {
  auto cols = input();
  unordered_map<ll,int> cnt;
  int r = 0;
  while (true) {
    round(cols, r++);
    ll num = getNum(cols);
    if (++cnt[num] == 2024) {
      cout << num * r << endl;
      return;
    }
  }
}

void partC() {
  // number of possible states <= num ways to distribute elements into 4 buckets <= ways to map elements to buckets * ways to order elements = 4^n * n!
  // if this number was reasonable, could repeat up to this amount, cycle guaranteed to be less than this
  // however, this number is very large, so must use caching to detect repeat state
  // could use a trie to save space but eh
  auto cols = input();
  unordered_set<string> seen;
  int r = 0;
  auto getState = [&]() {
    string s;
    for (auto &c : cols) {
      for (auto &x : c) {
        s += '0';
        s += to_string(x);
      }
      s += '|';
    }
    s.pop_back();
    return s;
  };
  seen.insert(getState());
  ll maxNum = getNum(cols);
  while (true) {
    round(cols, r++);
    size_t ps = seen.size();
    seen.insert(getState());
    if (ps == seen.size()) break;

    maxNum = max(maxNum, getNum(cols));
  }
  cout << maxNum << endl;
}

