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

bool aaa(int l, int r) {
  for (int i = l; i <= r; i++) {
    if (S[i] == '#' &&  S[i + 1] == '#') {
      return false;
    }
  }
  return true;
}

bool bbb(int l, int r) {
  for (int i = l; i <= r; i++) {
    if (S[i-1] == '.' && S[i] == '.' &&  S[i + 1] == '.') {
      return true;
    }
  }

  return false;
}

int main()
{
  int A, B, C, D, N;
  cin >> N >> A >> B >> C >> D;
  cin >> S;
  S = '#' + S + '#';

  if (!aaa(A, C) || !aaa(B, D)) {
    cout << "No" << endl;
    return 0;
  }

  if (C > D) {
    if (!bbb(B, D)) {
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;
  return 0;
}
