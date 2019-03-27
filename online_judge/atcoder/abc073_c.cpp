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

int main(int argc, char *argv[])
{

  int N, a;
  map<int, int> M;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a;
    M[a]++;
  };

  int ans = 0;
  for(auto x : M) {
    if (x.second % 2 == 1) ans++;
  }

  printf("%d\n", ans);
}
