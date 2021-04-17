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
#include <numeric>
#include <deque>

using namespace std;

int main()
{
  int N;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };

  deque<int> d;

  for (int i = 0; i < N; i++) {
    if (i % 2 == 0) {
      d.push_back(V[i]);
    } else {
      d.push_front(V[i]);
    }
  }

  if (N % 2 == 1) {
    reverse(d.begin(), d.end());
  }

  for (auto& vi: d) {
    cout << vi << " ";
  };
  puts("");

  return 0;
}
