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
  int N = S.size();
  map<char, map<char,int>> S1, T1;

  for (int i = 0; i < N; i++) {
    S1[S[i]][T[i]]++;
    T1[T[i]][S[i]]++;

    if (T1[T[i]].size() > 1 || S1[S[i]].size() > 1) {
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;
  return 0;
}
