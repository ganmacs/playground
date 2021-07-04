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

bool c(int l, int r) {
  for (int i = l; i < r; i++) {
    if (S[i] == '#' && S[i + 1] == '#') {
      return false;
    }
  }

  return true;
}

int main()
{
  int N, A, B, C, D;
  cin >> N >> A >> B >> C >> D >> S;
  A--;B--;C--;D--;

  if (!c(A, C) || !c(B, D)) {
    puts("No");
    return 0;
  }

  if (D < C) {
    for (int i = B; i <= D; i++) {
      if (S[i-1] == '.' && S[i] == '.' && S[i + 1] == '.') {
        puts("Yes");
        return 0;
      }
    }
  } else {
    puts("Yes");
    return 0;
  }

  puts("No");
  return 0;
}
