#include "../../template.h"

void partA() {
  vector<int> arr(1);
  while (cin >> arr.back()) arr.push_back(0);
  arr.pop_back();
  cout << accumulate(all(arr), 0LL) - (ll)*min_element(all(arr)) * (ll)arr.size() << endl;
}

void partB() {
  partA();
}

void partC() {
  // guaranteed the optimal height is one of the nail heights
  // can iterate over them by using running sum of needed nails and updating in O(1) per nail
  vector<int> arr(1);
  while (cin >> arr.back()) arr.push_back(0);
  arr.pop_back();
  sort(all(arr));
  ll p = 0;
  ll sum = accumulate(all(arr), 0LL);
  ll best = LLONG_MAX;
  for (size_t i = 0; i < arr.size(); ++i) {
    ll d = arr[i] - p;
    p = arr[i];
    sum += (ll)i * d - (ll)(arr.size() - i) * d;
    best = min(best, sum);
  }
  cout << best << endl;
}

