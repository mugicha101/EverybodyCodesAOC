#include "../../template.h"

void partA() {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.push_back("");
  grid.pop_back();
  int rows = grid.size();
  int cols = grid[0].size();

  vector<vector<int>> dist(rows, vector<int>(cols));
  for (int r = 1; r+1 < rows; ++r) {
    for (int c = 1; c+1 < cols; ++c) {
      dist[r][c] = grid[r][c] == '#' ? min(dist[r-1][c], dist[r][c-1]) + 1 : 0;
    }
  }
  for (int r = rows-2; r >= 1; --r) {
    for (int c = cols-2; c >= 1; --c) {
      dist[r][c] = min({dist[r][c], dist[r+1][c] + 1, dist[r][c+1] + 1});
    }
  }
  int res = 0;
  for (auto &r : dist) res += accumulate(all(r), 0);
  cout << res << endl;
}

void partB() {
  partA();
}

void partC() {
  vector<string> grid(2);
  while (cin >> grid.back()) {
    grid.back() = "." + grid.back() + ".";
    grid.push_back("");
  }
  int rows = grid.size();
  int cols = grid[1].size();
  grid[0].resize(cols, '.');
  grid[rows-1].resize(cols, '.');

  vector<vector<int>> dist(rows, vector<int>(cols));
  for (int r = 1; r+1 < rows; ++r) {
    for (int c = 1; c+1 < cols; ++c) {
      dist[r][c] = grid[r][c] == '#' ? min({dist[r-1][c], dist[r][c-1], dist[r-1][c-1], dist[r-1][c+1]}) + 1 : 0;
    }
  }
  for (int r = rows-2; r >= 1; --r) {
    for (int c = cols-2; c >= 1; --c) {
      dist[r][c] = min({dist[r][c], dist[r+1][c] + 1, dist[r][c+1] + 1, dist[r+1][c-1] + 1, dist[r+1][c+1] + 1});
    }
  }
  int res = 0;
  for (auto &r : dist) res += accumulate(all(r), 0);
  cout << res << endl;
}

