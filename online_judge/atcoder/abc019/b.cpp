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
#include <numeric>

using namespace std;

int main()
{
  string S;
  cin >> S;

  for (int i = 0; i < S.length();) {
    int j = i;
    while (j < S.length() && S[j] == S[i]) j++;
    cout << S[i] << j-i;
    i = j;
  }
  puts("");
  return 0;
}
