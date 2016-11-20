#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
static const double EPS = 1e-8;
static const int INF = (1 << 30);
static const int MAX = 100001;

int n;
int in[MAX + 1];
int ans[MAX + 1];
int L[MAX + 1];

int lis()
{
  int maxi = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (in[j] < in[i]) {
        ans[i] = max(ans[i], ans[j] + 1);
      }
    }
    maxi = max(maxi, ans[i]);
  }
  return maxi;
}

int lis2()
{
  int v = 1;
  L[0] = in[0];

  for (int i = 1; i < n; i++) {
    if(L[v-1] < in[i]) {
      L[v++] = in[i];
    } else {
      *lower_bound(L, L + v, in[i]) = in[i];
    }
  }

  return v;
}

int main(){
  cin >> n;

  for (int i = 0; i < n; i++) {
    ans[i] = 1;
    L[i] = 0;
    cin >> in[i];
  }

  // cout << lis() << endl;
  cout << lis2() << endl;
}
