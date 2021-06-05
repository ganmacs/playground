#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  map<char, map<char, int>> M1, M2;
  string S, T;
  cin >> S >> T;

  for (int i = 0; i < T.size(); i++) {
    M1[T[i]][S[i]]++;
    M2[S[i]][T[i]]++;

    if (M1[T[i]].size() >= 2 || M2[S[i]].size() >= 2) {
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;
  return 0;
}
