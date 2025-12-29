#include "../../template.h"

void partA() {
  string s; cin >> s;
  vector<string> words(1);
  for (size_t i = 6; i < s.size(); ++i) {
    if (s[i] == ',') words.push_back("");
    else words.back() += s[i];
  }

  cin.ignore(100, '\n');
  cin.ignore(100, '\n');
  getline(cin, s);
  int res = 0;
  for (string &w : words) {
    for (size_t i = 0; i+w.size() <= s.size(); ++i) {
      res += s.substr(i, w.size()) == w;
    }
  }
  cout << res << endl;
}

void partB() {
  string s; cin >> s;
  vector<string> words(1);
  for (size_t i = 6; i < s.size(); ++i) {
    if (s[i] == ',') words.push_back("");
    else words.back() += s[i];
  }
  
  cin.ignore(100, '\n');
  cin.ignore(100, '\n');
  int res = 0;
  while (getline(cin, s)) {
    int n = s.size();
    vector<bool> v(n);
    for (string &w : words) {
      string rw = w;
      reverse(all(rw));
      for (size_t i = 0; i+w.size() <= s.size(); ++i) {
        string seg = s.substr(i, w.size());
        if (seg == w || seg == rw) {
          for (int j = 0; j < w.size(); ++j) {
            v[i+j] = 1;
          }
        }
      }
    }
    res += accumulate(all(v), 0);
  }
  cout << res << endl;
}

void partC() {
  string s; cin >> s;
  vector<string> words(1);
  for (size_t i = 6; i < s.size(); ++i) {
    if (s[i] == ',') words.push_back("");
    else words.back() += s[i];
  }
  
  cin.ignore(100, '\n');
  cin.ignore(100, '\n');
  vector<string> grid(1);
  while (getline(cin, grid.back())) grid.push_back("");
  grid.pop_back();

  int rows = grid.size();
  int cols = grid[0].size();

  vector<vector<bool>> v(rows, vector<bool>(cols * 2));
  for (int r = 0; r < rows; ++r) {
    grid[r] = grid[r] + grid[r];
    for (string &w : words) {
      string rw = w;
      reverse(all(rw));
      for (int c = 0; c < cols; ++c) {
        string seg = grid[r].substr(c, w.size());
        if (seg != w && seg != rw) continue;

        for (size_t i = 0; i < w.size(); ++i) {
          v[r][c+i] = true;
        }
      }

      if (rows-r < w.size()) continue;

      string seg = w;
      for (int c = 0; c < cols; ++c) {
        for (int i = 0; i < w.size(); ++i) {
          seg[i] = grid[r+i][c];
        }
        if (seg != w && seg != rw) continue;

        for (size_t i = 0; i < w.size(); ++i) {
          v[r+i][c] = true;
        }
      }
    }

    for (int c = 0; c < cols; ++c) v[r][c] = v[r][c] | v[r][c+cols];
    v[r].resize(cols);
  }
  int res = 0;
  for (auto &r : v) res += accumulate(r.begin(), r.end(), 0);
  cout << res << endl;
}

