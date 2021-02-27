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

int main(int argc, char *argv[])
{

  long long int N, A, P, X;
  long long int ans = 1123456789123456788L;

  cin >> N;


  for (int i = 0; i < N; i++) {
    cin >> A >> P >> X;

    if (X-A > 0) {
      ans = min(ans, P);
    }
  }

  if (ans == 1123456789123456788L) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}
