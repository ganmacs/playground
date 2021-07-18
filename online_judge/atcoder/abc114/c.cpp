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

long long ans = 0;
long long N;

void rec(long long n, int used) {
  if (n > N) return;
  if (used == 0b111) ans++;

  rec(n*10 + 3, used | 0b100);
  rec(n*10 + 5, used | 0b010);
  rec(n*10 + 7, used | 0b001);
}


int main()
{
  cin >> N;
  rec(0, 0);
  cout << ans << endl;
  return 0;
}
