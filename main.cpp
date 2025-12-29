#include "template.h"

extern void partA();
extern void partB();
extern void partC();

void runPart(char c) {
  using namespace chrono;
  cout << "running part " << c << endl;
  auto start = high_resolution_clock::now();
  string inputPath = "./input" + string(1, toupper(c)) + ".txt";
  freopen(inputPath.c_str(), "r", stdin);
  switch (c) {
    case 'a': partA(); break;
    case 'b': partB(); break;
    case 'c': partC(); break;
    default: exit(-1);
  }
  auto end = high_resolution_clock::now();
  cout << "part " << c << ": " << duration_cast<microseconds>(end - start).count() << "us" << endl;
}

int main(int argc, char **argv) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(12);
  cout << setprecision(12);
  if (argc < 2) {
    runPart('a');
    runPart('b');
    runPart('c');
  } else {
    if (strlen(argv[1]) != 1 || tolower(argv[1][0]) < 'a' || tolower(argv[1][1]) > 'c') {
      cerr << "Unknown part " << argv[1] << endl;
      return 0;
    }
    runPart(tolower(argv[1][0]));
  }
}