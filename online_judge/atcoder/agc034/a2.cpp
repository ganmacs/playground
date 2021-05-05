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

string S;


bool a1(int l, int r) {
  for (int i = l; i < r; i++) {
    if (S[i] == '#' &&  S[i + 1] == '#') {
      return false;
    }
  }
  return true;
}

int main()
{
  int N, A, B, C, D;
  cin >> N >> A >> B >> C >> D;
  cin >> S;

  if (!a1(B, D) || !a1(A, C)) {
    cout << "No" << endl;
    return 0;
  }

  if (D > C) {
    cout << "Yes" << endl;
    return 0;
  }

  bool ok = false;
  for (int i = max(A-1, B-2); i < (D-1); i++) {
    if (S[i] == '.' &&  S[i + 1] == '.' && S[i + 2] == '.') {
      ok = true;
      break;
    }
  }

  if (ok) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  return 0;
}
