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

int N, A, B, C, D;
string S;

bool c1(int l, int r)
{
  for (int i = l; i < r-1; i++) {
    if (S[i] == '#' && S[i + 1] == '#') {
      return false;
    }
  }

  return true;
}

int main()
{
  cin >> N >> A >> B >> C >> D;
  cin >> S;

  if (!c1(A, C) || !c1(B, D)) {
    cout << "No" << endl;
    return 0;
  }

  if (C > D) {                  // ABDC
    for (int i = max(B-1, A+1); i < D; i++) {
      if (S[i-1] == '.' && S[i] == '.' && S[i + 1] == '.') {
        cout << "Yes" << endl;
        return 0;
      }
    }
    cout << "No" << endl;
  } else {
    cout << "Yes" << endl;
  }

  return 0;
}
