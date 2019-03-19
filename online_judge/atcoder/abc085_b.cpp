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
  int N, a[1000], t = -1, ans = 0;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];
  sort(a, a + N);


  for (int i = 0; i < N; i++) {
    if (t != a[i]) {
      ans++;
      t = a[i];
    }
  }

  printf("%d\n", ans);
}
