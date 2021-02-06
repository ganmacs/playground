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

int main(int argc, char *argv[]) {
  int N;
  cin >> N;
  if (N == 0) {
    cout << 0 << endl;
    return 0;
  }

  string ans = "";
  while (N != 0) {
    if (N % 2 != 0) {
      N--;
      ans = "1" + ans;
    } else {
      ans = "0" + ans;
    }

    N /= -2;
  }

  cout << ans << endl;
  return 0;
}
