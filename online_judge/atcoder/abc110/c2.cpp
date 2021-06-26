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
  string S, T;
  cin >> S >> T;
  map<char, map<char, int>> ss, tt;

  for (int i = 0; i < S.size(); i++) {
    ss[S[i]][T[i]]++;
    tt[T[i]][S[i]]++;

    if (ss[S[i]].size() == 2 || tt[T[i]].size() == 2) {
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;
  return 0;
}
