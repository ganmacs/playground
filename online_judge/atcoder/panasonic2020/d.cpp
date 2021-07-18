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

string buf = "a";

void dfs(int N)
{
  if (N == 1) {
    cout << buf << endl;
    return;
  }

  char c = 'a';
  for (auto& vi: buf) {
    if (vi > c) c = vi;
  }

  for (char i = 'a'; i <= (c + 1); i++) {
    buf.push_back(i);
    dfs(N-1);
    buf.pop_back();
  }
}

int main()
{
  int N;
  cin >> N;
  dfs(N);

  return 0;
}
