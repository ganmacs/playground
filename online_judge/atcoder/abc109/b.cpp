#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

map<string, bool> M;

int main(int argc, char *argv[])
{
  int N;
  string W, W1;

  cin >> N;
  cin >> W1;
  bool ans = false;

  M[W1] = true;

  for (int i = 1; i < N; i++) {
    cin >> W;
    if (M.find(W) != M.end()) {
      ans = true;
    }

    if (W1[W1.length()-1] != W[0]) {
      ans = true;
    }

    M[W] = true;
    W1 = W;
  }


  cout << (ans ? "No" : "Yes") << endl;
  return 0;
}
