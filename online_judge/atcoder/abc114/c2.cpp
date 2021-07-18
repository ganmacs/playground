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

long long N;
long long c = 0;

void dfs(long long n,int t) {
  if (n > N) return;
  if (t == 0b111) c++;

  dfs(n*10 + 3, t | 0b100);
  dfs(n*10 + 5, t | 0b010);
  dfs(n*10 + 7, t | 0b001);
}

int main()
{
  cin >> N;
  dfs(0, 0);
  cout << c << endl;
  return 0;
}
