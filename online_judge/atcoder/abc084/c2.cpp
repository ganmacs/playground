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
  N--;
  vector<int> C(N), F(N), S(N), ans;
  for (int i = 0; i < N; i++) {
    cin >> C[i] >> S[i] >> F[i];
  }

  for (int k = 0; k < N; k++) {
    int t = 0;

    for (int i = k; i < N; i++) {
      t = max(t, S[i]);
      int tt = t - S[i];
      if ((tt % F[i]) != 0) {
        t += (F[i] - (tt % F[i]));
      }
      t += C[i];
    }

    ans.push_back(t);
  }
  ans.push_back(0);

  for (auto& vi: ans) {
    cout << vi << endl;
  }
  return 0;
}
