#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <numeric>

using namespace std;


int main()
{
  deque<char> D;
  string S;
  cin >> S;
  int N = S.size();

  int r = false;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'R') {
      r = !r;
    } else {
      if (r) {
        D.push_front(S[i]);
      } else {
        D.push_back(S[i]);
      }
    }
  }

  if (r) {
    reverse(D.begin(), D.end());
  }

  vector<char> V;
  for (auto& vi: D) {
    if (V.size() >= 1) {
      if (V[V.size()-1] == vi) {
        V.pop_back();
        continue;
      }
    }

    V.push_back(vi);
  };

  for (auto& vi: V) {
    cout << vi;
  };
  cout << endl;


  return 0;
}
