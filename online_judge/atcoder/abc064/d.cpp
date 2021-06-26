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
int N;

string rr(int i, int s, string t) {
  if (i == N) {
    if (s != 0) {
      for (int i = 0; i < s; i++) {
        t += ")";
      }
    }

    return t;
  }

  if (S[i] == '(') {
    return rr(i + 1, s + 1, t + "(");
  } else {
    if (s == 0) {
      return rr(i + 1,  s, "(" + t + ")");
    } else {
      return rr(i + 1, s-1, t + ")");
    }
  }

  return t;
}


int main()
{
  cin >> N >> S;
  cout << rr(0, 0, "") << endl;

  return 0;
}
