#include "../../template.h"

void partA() {
  // f(x) = sum(i=0, x-1, i*2+1) = x+2sum(i=1,x-1,i) = x+(x-1)x = x^2
  ll t; cin >> t;
  ll x = 1;
  while (x*x < t) ++x;
  cout << (x*x-t) * (x*2-1) << endl;
}

void partB() {
  ll total = 1;
  ll width = 1;
  ll thick = 1;
  ll target = 20240000;
  ll mult; cin >> mult;
  while (total < target) {
    width += 2;
    thick = (thick * mult) % 1111;
    total += width * thick;
  }
  cout << (total-target) * width << endl;
}

void partC() {
  ll target = 202400000;
  auto calc = [&](ll layers) {
    ll total = 1;
    ll thick = 1;
    ll mult; cin >> mult;
    ll mod = 10;
    vector<int> cols(layers);
    for (int i = 0; i < layers; ++i) {
      cols[i] = thick;
      thick = ((thick * mult) % mod) + mod;
    }
    for (int i = layers-2; i >= 0; --i) cols[i] += cols[i+1];
    for (int i = 0; i < layers-1; ++i) cols[i] -= mult * (layers*2-1) * cols[i] % mod;
    return accumulate(all(cols), 0LL) * 2 - cols[0];
  };
  ll lo = 1;
  ll hi = 1;
  while (calc(hi) < target) hi <<= 1;
  while (lo != hi) {
    ll layers = (lo + hi) >> 1;
    if (calc(layers) >= target) {
      hi = layers;
    } else {
      lo = layers+1;
    }
  }
  ll res = calc(lo);
  cout << res-target << endl;
}