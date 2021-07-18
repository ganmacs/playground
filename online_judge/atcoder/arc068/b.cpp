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
  int N, a;
  cin >> N;
  map<int, int> M;
  for (int i = 0; i < N; i++) {
    cin >> a;
    M[a]++;
  }

  int aa = M.size();
  int bb = 0;

  for (auto& vi: M) {
    if (vi.second != 1) {
      bb += vi.second;
      bb--;
    }
  }

  if (M.size() == 1) {
    cout << 1 << endl;
  } else {
    cout << aa - (bb % 2) << endl;
  }

  return 0;
}
