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
}

void partC() {

}

