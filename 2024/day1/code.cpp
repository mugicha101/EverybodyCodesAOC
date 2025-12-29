#include "../../template.h"

void partA() {
  string s; cin >> s;
  int res = 0;
  for (char c : s) {
    res += (1 << (c - 'A')) - 1;
  }
  cout << res << endl;
}

void partB() {
  string s; cin >> s;
  int8_t cost[256] = {};
  cost['B'] = 1;
  cost['C'] = 3;
  cost['D'] = 5;
  int res = 0;
  for (int i = 0; i+1 < s.size(); i += 2) {
    res += cost[s[i]] + cost[s[i+1]] + (s[i] == 'x' || s[i+1] == 'x' ? 0 : 2);
  }
  cout << res << endl;
}

void partC() {
  string s; cin >> s;
  int8_t cost[256] = {};
  cost['B'] = 1;
  cost['C'] = 3;
  cost['D'] = 5;
  int8_t mcost[] = {0, 0, 2, 6};
  int res = 0;
  for (int i = 0; i+2 < s.size(); i += 3) {
    int m = (int)(s[i] != 'x') + (int)(s[i+1] != 'x') + (int)(s[i+2] != 'x');
    res += cost[s[i]] + cost[s[i+1]] + cost[s[i+2]] + mcost[m];
  }
  cout << res << endl;
}

