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
  map<char, map<char, int>> M, M2;
  for (int i = 0; i < T.size(); i++) {
    M[T[i]][S[i]]++;
    M2[S[i]][T[i]]++;
    if (M[T[i]].size() >= 2 || M2[S[i]].size() >= 2) {
      puts("No");
      return 0;
    }
  }

  puts("Yes");
  return 0;
}
