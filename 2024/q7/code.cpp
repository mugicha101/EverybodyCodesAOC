#include "../../template.h"

vector<pair<string,string>> getInput() {
  vector<pair<string,string>> input;
  string s;
  while (cin >> s) {
    int del = s.find(':');
    string seg;
    for (int i = del+1; i < s.size(); i += 2) seg += s[i];
    input.emplace_back(s.substr(0, del), seg);
  }
  return input;
}

// returns (rank, index)
vector<pair<ll,int>> calcOrder(const vector<pair<string,string>> &input, function<ll(const string &)> rankFunc) {
  vector<pair<ll,int>> order(input.size());
  for (int i = 0; i < input.size(); ++i) order[i] = {rankFunc(input[i].second), i};
  return order;
}

void partA() {
  auto input = getInput();
  auto order = calcOrder(input, [](const string &seg) -> ll {
    int curr = 0;
    ll sum = 0;
    for (int i = 0; i < 10; ++i) {
      char op = seg[i % seg.size()];
      curr += op == '+' ? 1 : op == '-' ? -1 : 0;
      sum += curr;
    }
    return sum;
  });
  sort(all(order), greater<pair<int,int>>());
  for (auto [r, i] : order) cout << input[i].first;
  cout << endl;
}

string parseTrack(const string &track) {
  vector<string> grid(1);
  for (char c : track) {
    if (c == '\n') grid.push_back(" ");
    else grid.back().push_back(c);
  }

  int rows = grid.size();
  int cols = 0;
  for (string &row : grid) cols = max(cols, (int)row.size()+1);
  for (string &row : grid) row.resize(cols, ' ');

  int sr = -1, sc = -1;
  for (int r = 0; sr == -1 && r < rows; ++r) {
    for (int c = 0; sr == -1 && c < cols; ++c) {
      if (grid[r][c] == 'S') {
        sr = r;
        sc = c;
      }
    }
  }

  string seq = "";
  int r = sr;
  int c = sc + 1;
  int pr = sr;
  int pc = sc;
  while (!(r == sr && c == sc)) {
    seq += grid[r][c];
    auto check = [&](int dr, int dc) -> bool {
      if ((pr == r + dr && pc == c + dc) || grid[r+dr][c+dc] == ' ') return false;
      pr = r;
      pc = c;
      r += dr;
      c += dc;
      return true;
    };
    check(0, 1) || check(1, 0) || check(0, -1) || check(-1, 0);
  }
  seq += '=';
  return seq;
}

vector<pair<ll,int>> calcTrackOrder(const string &track, const vector<pair<string,string>> &input, int loops) {
  string seq = parseTrack(track);

  // assume all entries same length
  // can calculate how much each position is triggered based on track and how many are forced -/+
  // since dealing with prefix sums, multiply effect by remaining positions
  int n = input[0].second.size();
  int k = loops * seq.size();
  ll offset = 10LL * k;
  vector<int> triggers(n);
  int j = -1;
  int m = k+1;
  for (int i = 0; i < loops; ++i) {
    for (char c : seq) {
      j = j+1 == n ? 0 : j+1;
      --m;
      if (c == '=') triggers[j] += m;
      else if (c == '+') offset += m;
      else offset -= m;
    }
  }
  return calcOrder(input, [&](const string &seg) -> ll {
    ll sum = offset;
    for (int i = 0; i < n; ++i) {
      char c = seg[i];
      if (c == '+') sum += triggers[i];
      else if (c == '-') sum -= triggers[i];
    }
    return sum;
  });
}

void partB() {
  const string track = R"(
S-=++=-==++=++=-=+=-=+=+=--=-=++=-==++=-+=-=+=-=+=+=++=-+==++=++=-=-=--
-                                                                     -
=                                                                     =
+                                                                     +
=                                                                     +
+                                                                     =
=                                                                     =
-                                                                     -
--==++++==+=+++-=+=-=+=-+-=+-=+-=+=-=+=--=+++=++=+++==++==--=+=++==+++-
)";

  auto input = getInput();
  auto order = calcTrackOrder(track, input, 10);
  sort(all(order), greater<pair<int,int>>());
  for (auto [r, i] : order) cout << input[i].first;
  cout << endl;
}

void partC() {
  const string track = R"(
S+= +=-== +=++=     =+=+=--=    =-= ++=     +=-  =+=++=-+==+ =++=-=-=--
- + +   + =   =     =      =   == = - -     - =  =         =-=        -
= + + +-- =-= ==-==-= --++ +  == == = +     - =  =    ==++=    =++=-=++
+ + + =     +         =  + + == == ++ =     = =  ==   =   = =++=
= = + + +== +==     =++ == =+=  =  +  +==-=++ =   =++ --= + =
+ ==- = + =   = =+= =   =       ++--          +     =   = = =--= ==++==
=     ==- ==+-- = = = ++= +=--      ==+ ==--= +--+=-= ==- ==   =+=    =
-               = = = =   +  +  ==+ = = +   =        ++    =          -
-               = + + =   +  -  = + = = +   =        +     =          -
--==++++==+=+++-= =-= =-+-=  =+-= =-= =--   +=++=+++==     -=+=++==+++-
)";

  // index 0 = rival's sequence
  // come up with all possible other sequences
  // brute force to come up with order using past parts
  // could be optimized a lot by mapping index in seq -> triggers in loop

  auto input = getInput();
  string rival = input[0].second;
  string perm = rival;
  next_permutation(all(perm));
  while (perm != rival) {
    input.emplace_back("", perm);
    next_permutation(all(perm));
  }
  
  auto order = calcTrackOrder(track, input, 2024);
  int res = 0;
  for (int i = 1; i < order.size(); ++i) {
    res += order[i].first > order[0].first;
  }
  cout << res << endl;
}

