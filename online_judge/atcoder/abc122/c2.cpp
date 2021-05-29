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
  int N, Q, l, r;
  string S;
  cin >> N >> Q >> S;
  vector<int> V(N, 0);

  for (int i = 0; i < N - 1; i++) {
    if (S[i] == 'A' && S[i + 1] == 'C') {
      V[i + 1] = V[i] + 1;
    } else {
      V[i + 1] = V[i];
    }
  }

  for (int i = 0; i < Q; i++) {
    cin >> l >> r;
    l--;r--;
    if (l-1 >= 0) {
      if (S[l-1] == 'A' && S[l] == 'C') {
        cout << (V[r]-V[l-1]-1) << endl;;
      } else {
        cout << (V[r]-V[l-1]) << endl;;
      }
    } else {
      cout << (V[r]-V[l]) << endl;;
    }
  }

  return 0;
}
