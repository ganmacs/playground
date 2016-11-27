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
static const int MAX = 1000000;
int n;

int main(){
  int d, n, m;
  int store[MAX];
  cin >> d >> n >> m;

  while (d != 0) {
    int j;
    store[0] = 0;
    for (j = 1; j < n; j++) cin >> store[j];
    store[j++] = d;
    sort(store, store + j);

    int ans = 0, t;
    for (int i = 0; i < m; i++) {
      cin >> t;
      int *v = lower_bound(store, store + j, t);
      int *k = v - 1;
      ans += min(abs(*v-t), abs(*k-t));
    }
    cout << ans << endl;
    cin >> d >> n >> m;
  }

}
