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

const int INF = 1e9;

bool r[200000];
int  a[200];

int main(int argc, char *argv[])
{
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  for (int i = 0; i <= 100000; i++) r[i] = false;
  r[0] = true;

  for (int i = 0; i < N; i++) {
    for (int j = 100000; j >= a[i]; j--) {
      if (r[j-a[i]]) r[j] = true;
    }
  }

  int ans = 0;
  for (int i = 0; i <= 100000; i++) {
    if (r[i]) ans++;
  }

  cout << ans << endl;
}
