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
#include <numeric>

using namespace std;

bool d[11234567];

vector<long long> aaa(long long v) {
  vector<long long> V;
  for (long long i = 2; i*i <= v; i++) {
    if (v % i != 0) continue;
    while (v % i == 0) v /= i;
    V.push_back(i);
  }
  if (v != 1) V.push_back(v);

  return V;
}

int main()
{
  long long A, B;
  cin >> A >> B;

  auto a = aaa(A);
  auto b = aaa(B);

  int i = 0, j = 0, ans = 1;
  while (i < a.size() && j < b.size()) {
    if (a[i] == b[j]) {
      ans++;
      j++;
    } else if (a[i] < b[j]) {
      i++;
    } else{
      j++;
    }
  }

  cout << ans << endl;
  return 0;
}
