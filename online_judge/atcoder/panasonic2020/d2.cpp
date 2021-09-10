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
int N;

void dfs(string s) {
  if (s.size() == N) {
    M[s]++;
    return;
  }

  char t = 'a';
  for (auto& vi: s) t = max(t, vi);
  for (char i = 'a'; i <= (t + 1); i++) {
    dfs(s + i);
  }
}

int main()
{
  cin >> N;
  dfs("a");

  for (auto& vi: M) {
    cout << vi.first << endl;
  }

  return 0;
}
