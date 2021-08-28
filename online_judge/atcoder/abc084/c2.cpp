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

int main()
{
  int N;
  cin >> N;
  vector<long long> C(N), S(N), F(N);
  N--;
  for (int i = 0; i < N; i++) {
    cin >> C[i] >> S[i] >> F[i];
  }

  for (int j = 0; j < N; j++) {
    long long t = 0;
    for (int i = j; i < N; i++) {
      auto tt = t - S[i];
      if (tt <= 0) {
        t = S[i];
      } else {
        auto rest = tt % F[i];
        if (rest != 0) {
          t += (F[i]-rest);
        }
      }

      t += C[i];
    }
    printf("%lld\n", t);
  }

  printf("%d\n", 0);
  return 0;
}
