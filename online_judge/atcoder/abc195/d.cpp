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

int W[100], V[100], X[100];

int main()
{
  int N, M, Q, r, l;
  cin >> N >> M >> Q;

  for (int i = 0; i < N; i++) {
    cin >> W[i] >> V[i];
  }

  for (int i = 0; i < M; i++) {
    cin >> X[i];
  }

  for (int i = 0; i < Q; i++) {
    puts("\n===================================== start print");
    puts("===================================== finish print\n");
    long long int ans = 0;
    cin >> l >> r;
    cout << l << "  " << r << endl;
    vector<int> v;
    for (int j = 0; j < M; j++) {
      if ((l-1) <= j && (r-1) >= j) {
        continue;
      }
      v.push_back(X[j]);
    }

    for (const auto& vi: v) {
      cout << vi << " ";
    }
    puts("");


    do {
      long long int ta = 0;
      for (int j = 0; j < N && j < v.size(); j++) {
        if (v[j] >= W[i]) {
          ta += V[i];
        }
      }

      ans = max(ta, ans);
    } while (std::next_permutation(v.begin(), v.end()));

    cout << ans << endl;
  }

  return 0;
}
