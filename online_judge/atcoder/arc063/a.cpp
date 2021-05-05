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


  int ans = 0;
  for (int i = 0; i < S.size();) {
    int j = i;
    while (j < S.size() && S[i] == S[j]) j++;
    ans++;
    i = j;
  }

  cout << (ans-1) << endl;

  return 0;
}
