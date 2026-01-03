#include "../../template.h"

vector<string> solvePath() {

  unordered_map<string,vector<string>> adj;
  unordered_map<string,string> parent;
  string s;
  while (cin >> s) {
    s += ',';
    size_t del = s.find(':');
    string src = s.substr(0, del);
    string dst = "";
    for (size_t i = del+1; i < s.size(); ++i) {
      if (s[i] == ',') {
        adj[src].push_back(dst);
        parent[dst] = src;
        dst = "";
      } else {
        dst += s[i];
      }
    }
  }
  queue<string> q;
  q.push("RR");
  string lastLeaf = "";
  while (lastLeaf.empty() || lastLeaf == ",") {
    lastLeaf = "";
    for (int qi = q.size(); qi > 0; --qi) {
      string curr = q.front();
      q.pop();
      for (auto &next : adj[curr]) {
        if (next == "@") {
          lastLeaf = lastLeaf.empty() ? curr : ",";
        } else {
          q.push(next);
        }
      }
    }
  }
  vector<string> path;
  path.push_back("@");
  path.push_back(lastLeaf);
  while (lastLeaf != "RR") {
    lastLeaf = parent[lastLeaf];
    path.push_back(lastLeaf);
  }
  reverse(all(path));
  return path;
}

void partA() {
  auto path = solvePath();
  for (auto &s : path) cout << s;
  cout << endl;
}

void partB() {
  auto path = solvePath();
  for (auto &s : path) cout << s[0];
  cout << endl;
}

void partC() {
  partB();
}

