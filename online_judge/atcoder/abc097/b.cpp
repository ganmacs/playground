#include <algorithm>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  long long N;
  cin >> N;

  int ans = 1, k;
  for (int i = 2; i <= N; i++) {
    for (int j = 2; j <= N; j++) {
      k = pow(i, j);

      if(k <= N) {
        ans = max(ans, k);
      } else {
        break;
      }
    }
  }

  cout << ans << endl;

  return 0;
}
