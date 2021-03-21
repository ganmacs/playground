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
  unsigned long long int N;
  unsigned long long int nnn = 10;
  long long int ans = 0;
  cin >> N;

  for (unsigned long long int i = 1; i <= N; i++) {
    if (nnn <= i) {
      nnn *= 10;
    }

    if(i*nnn + i > N) {
      break;
    }

    ans++;
  }

  cout << ans << endl;
  return 0;
}
