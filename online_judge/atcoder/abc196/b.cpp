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

int main()
{
  string S;
  cin >> S;

  for (int i = 0; i < S.length(); i++) {
    if (S[i] == '.') {
      break;
    }
    cout << S[i];
  }

  puts("");

  return 0;
}
