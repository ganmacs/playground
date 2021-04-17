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

using namespace std;

int main()
{
  int N;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
    vi = -vi;
  };
  sort(V.begin(), V.end());

  vector<unsigned long long int> K;

  for (int i = 0; i < (N-1);) {
    if (V[i] == V[i + 1]) {
      K.push_back(V[i]);
      if (K.size() == 2) break;
      i += 2;
    } else {
      i++;
    }
  }

  if (K.size() == 2) {
    cout << K[0]*K[1] << endl;
  } else {
    cout << 0 << endl;
  }

  return 0;
}
