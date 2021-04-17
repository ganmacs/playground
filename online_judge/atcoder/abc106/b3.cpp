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

int aaa(int v) {
  int a = 0;
  for (int i = 1; i <= N; i++) {
    if (v % i == 0) a++;
  }

  return (8 == a);
}

int main(int argc, char *argv[]) {
  int ans = 0;
  cin >> N;

  for (int i = 1; i <= N; i += 2) {
    ans += aaa(i);
  }

  cout << ans << endl;
  return 0;
}
