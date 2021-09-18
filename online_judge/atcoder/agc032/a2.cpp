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
  vector<int> B(N), ans;
  for (auto& vi: B) cin >> vi;

  for (int k = 0; k < 100; k++) {
    for (int i = B.size()-1; i >= 0; i--) {
      if (B[i] == i + 1) {
        ans.push_back(B[i]);
        B.erase(B.begin() + i);
        break;
      }
    }

    if (B.empty()) {
      break;
    }
  }

  if (!B.empty()) {
    printf("%d\n", -1);
    return 0;
  }

  reverse(ans.begin(), ans.end());
  for (auto& vi: ans) {
    printf("%d\n", vi);
  }

  return 0;
}
