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
  vector<int> C(N), S(N), F(N);
  N--;
  for (int i = 0; i < N; i++) {
    cin >> C[i] >> S[i] >> F[i];
  }

  for (int i = 0; i < N; i++) {
    int t = S[i] + C[i];

    for (int j = i + 1; j < N; j++) {
      int tt = t - S[j];
      if (tt >= 0) {
        if (tt % F[j] != 0) {
          t += C[j] + (F[j] - (tt % F[j]));
        } else {
          t += C[j];
        }
      } else {
        t = C[j] + S[j];
      }
    }
    cout << t << endl;
  }

  cout << 0 << endl;
  return 0;
}
