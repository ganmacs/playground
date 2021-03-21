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
#include <iomanip>

using namespace std;

int main()
{
  int N, K;
  cin >> N >> K;

  int v;
  vector<double> V2(N + 1);


  V2[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> v;
    double k = 0;

    for (int i = 1; i <= v; i++) {
      k += ((1.0*i)/v);
    }

    V2[i + 1] = k + V2[i];
  };

  // cout << std::setprecision(10);
  // for (int i = 1; i <= N; i++) {
  //   cout << V2[i] << " ";
  // }
  // puts("");

  double ans = 0.0;

  for (int i = K; i < N + 1; i++) {
    ans = max(V2[i]-V2[i-K], ans);
  }

  printf("%0.12f\n", ans);

  return 0;
}
