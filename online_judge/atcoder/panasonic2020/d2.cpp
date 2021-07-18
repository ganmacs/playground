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

map<string, int> M;

void dfs(int n, string s) {
  if (n == 1) {
    M[s]++;
    return;
  }

  char c = 'a';
  for (auto& vi: s) {
    c = max(c, vi);
  }


  for (char i = 'a'; i <= (c + 1); i++) {
    dfs(n-1, s + i);
  }
}

int main()
{
  int N;
  cin >> N;

  dfs(N, "a");

  for (auto& vi: M) {
    cout << vi.first << endl;
  }

  return 0;
}
