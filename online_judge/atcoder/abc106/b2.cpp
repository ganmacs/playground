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

int N;

bool aaa(int n) {
  int nm = 0;
  for (int i = 1; (i*i) <= n; i += 2) {
    if (n % i == 0) nm += 2;
  }

  return nm == 8;
}

int main(int argc, char *argv[]) {
  cin >> N;

  if (105 > N) {
    cout << 0 << endl;
  } else {
    int ans = 0;
    for (int i = 105; i <= N; i += 2) {
      if (aaa(i)) ans++;
    }

    cout << ans << endl;
  }

  return 0;
}
