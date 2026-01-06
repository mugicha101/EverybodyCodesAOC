#include "../../template.h"

void partA() {
  // seems greedable
  int x;
  int total = 0;
  while (cin >> x) {
    total += x / 10;
    x %= 10;
    total += x / 5;
    x %= 5;
    total += x / 3;
    x %= 3;
    total += x;
  }
  cout << total << endl;
}

void partB() {
  // doesn't seem greedible
  // use dp in O(N*k)
  vector<int> input(1);
  while (cin >> input.back()) input.push_back(0);
  input.pop_back();
  int cap = *max_element(all(input));
  vector<int> dp(cap+1); // dp[d][x] = min coins to produce x with first d denominations (compress d out via time)
  iota(all(dp), 0);
  const int den[] = { 3, 5, 10, 15, 16, 20, 24, 25, 30 };
  for (int d : den) {
    for (int x = 0; x <= cap - d; ++x) {
      dp[x+d] = min(dp[x+d], dp[x]+1);
    }
  }
  int res = 0;
  for (int x : input) {
    cout << x << ": " << dp[x] << endl;
    res += dp[x];
  }
  cout << res << endl;
}

void partC() {
  // same as part B but brute force all 50 possible splits
  vector<int> input(1);
  while (cin >> input.back()) input.push_back(0);
  input.pop_back();
  int cap = *max_element(all(input));
  cap = cap / 2 + 51; // since splitting, only need half + 50
  vector<int> dp(cap+1); // dp[d][x] = min coins to produce x with first d denominations (compress d out via time)
  iota(all(dp), 0);
  const int den[] = { 1, 3, 5, 10, 15, 16, 20, 24, 25, 30, 37, 38, 49, 50, 74, 75, 100, 101 };
  for (int d : den) {
    for (int x = 0; x <= cap - d; ++x) {
      dp[x+d] = min(dp[x+d], dp[x]+1);
    }
  }
  int res = 0;
  for (int x : input) {
    // b - a <= 100
    // a + b = x
    // a <= b

    // b - (x - b) <= 100
    // 2b <= x + 100
    // b <= (x + 100) / 2

    // (x - a) - a <= 100
    // x - 2a <= 100
    // -2a <= 100 - x
    // 2a >= x - 100
    // a >= (x - 100) / 2

    // a <= x - a
    // 2a <= x
    // a <= x/2

    // (x - 100) / 2 <= a <= x / 2

    int best = INT_MAX;
    for (int a = (x - 99) / 2; a <= x / 2; ++a) {
      best = min(best, dp[a] + dp[x-a]);
    }
    res += best;
  }
  cout << res << endl;
}